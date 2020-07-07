#include "dbobj.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>

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

    q1.prepare("SELECT id, nhs FROM pats WHERE rxr = ?");
    q1.addBindValue(rxr.toUpper());
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
    q2.addBindValue(rxr.toUpper());
    q2.addBindValue(nhs);
    q2.exec();

    q1.exec();
    if(q1.first()) return q1.value(0).toInt();

    return -1;
}
