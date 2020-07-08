#include "dbobj.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QRegularExpression>

DBObj::DBObj()
{

}

DBObj::~DBObj()
{
    if(db.isOpen()) db.close();
}

bool DBObj::db_init(QString driver)
{
    if(!QSqlDatabase::isDriverAvailable(driver)) {
        QMessageBox msg;

        msg.setWindowTitle("Error");
        msg.setText("Database driver unavailable");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();

        return false;
    }

    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(db_path);

    if(!db.open()) {
        QMessageBox msg;

        msg.setWindowTitle("Error");
        msg.setText("Can't open database");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();

        return false;
    }

    return true;
}

void DBObj::db_setpath(QString path)
{
    db_path = path;
}


// Look for rxr in database
// If exists then return patient id
// If it doesn't exist create and return id
// Update nhs number if not already in database
// Return negative number if something goes wrong
int DBObj::db_getpatid(QString rxr, QString nhs)
{
    QSqlQuery q1, q2;

    if (!valid_rxr(rxr)) return -1;
    else rxr = clean_rxr(rxr);

    if (!valid_nhs(nhs)) nhs = "NULL";
    else nhs = clean_nhs(nhs);

    //debug
    QMessageBox msg;
    msg.setWindowTitle("NHS");
    msg.setText(nhs);
    msg.setIcon(QMessageBox::Information);
    msg.exec();

    q1.prepare("SELECT id, nhs FROM pats WHERE rxr = ?");
    q1.addBindValue(rxr);
    q1.exec();

    if(q1.first()) {
        if((nhs != "NULL") && (q1.value(1).toString() == "NULL")) {
            q2.prepare("UPDATE pats SET nhs = ? WHERE id = ?");
            q2.addBindValue(nhs);
            q2.addBindValue(q1.value(0).toInt());
            q2.exec();
        }
        return q1.value(0).toInt();
    }

    q2.prepare("INSERT INTO pats (rxr, nhs) VALUES (?, ?)");
    q2.addBindValue(rxr);
    q2.addBindValue(nhs);
    q2.exec();

    q1.exec();
    if(q1.first()) return q1.value(0).toInt();

    return -1;
}

bool DBObj::valid_rxr(QString rxr)
{
    QRegularExpression re("\\d{7}");

    rxr = rxr.trimmed();

    if(rxr.length() != 10) return false;
    if(!rxr.startsWith("rxr", Qt::CaseInsensitive)) return false;
    if(re.match(rxr.right(7)).hasMatch()) return true;

    return false;
}

bool DBObj::valid_nhs(QString nhs)
{
    QRegularExpression re("^\\d{3}\\s*\\d{3}\\s*\\d{4}$");

    if(re.match(nhs.trimmed()).hasMatch()) return true;

    return false;
}

QString DBObj::clean_rxr(QString rxr)
{
    return rxr.trimmed().toUpper();
}

QString DBObj::clean_nhs(QString nhs)
{
    QRegularExpression re("(\\d{3})\\s*(\\d{3})\\s*(\\d{4})");
    QRegularExpressionMatch match;

    match = re.match(nhs.trimmed());
    if(match.hasMatch()) {
        return (match.captured(1) + " " + match.captured(2) + " " + match.captured(3));
    }

    return "NULL";
}
