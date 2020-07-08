#ifndef DBOBJ_H
#define DBOBJ_H

#include <QSqlDatabase>
#include <QString>

class DBObj
{
public:
    DBObj();
    ~DBObj();

    // Various direct database access / setup functions
    bool db_init(QString driver="QSQLITE");
    void db_setpath(QString path);
    int db_getpatid(QString rxr, QString nhs="NULL");

    // Validate data for database
    bool valid_rxr(QString rxr);
    bool valid_nhs(QString nhs);

private:
    QSqlDatabase db;
    QString db_path;

    QString clean_rxr(QString rxr);

#ifdef TESTING
// Expose clean_nhs() for testing
public:
#endif // TESTING
    QString clean_nhs(QString nhs);
};

#ifndef MAIN_CPP
extern DBObj *ClinicalDB;
#endif // MAIN_CPP

#endif // DBOBJ_H
