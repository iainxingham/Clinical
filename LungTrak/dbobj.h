#ifndef DBOBJ_H
#define DBOBJ_H

#include <QSqlDatabase>
#include <QString>

class DBObj
{
public:
    DBObj();
    ~DBObj();

    bool db_init(QString driver="QSQLITE");
    void db_setpath(QString path);
    int db_getpatid(QString rxr, QString nhs="NULL");

private:
    QSqlDatabase db;
    QString db_path;
};

#ifndef MAIN_CPP
extern DBObj *ClinicalDB;
#endif // MAIN_CPP

#endif // DBOBJ_H
