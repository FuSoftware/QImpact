#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <QString>
#include <QVector>

class SqlColumn
{
public:
    SqlColumn(){}
    SqlColumn(QString name, QString type){this->name = name;this->type= type;}
    QString create(){return name + " " + type;}

private:
    QString type;
    QString name;
};

class SqlTable
{
public:
    SqlTable(QString name, QVector<SqlColumn> columns);

    QString create();
    QString drop();
    QString getName();

private:
    QString name;
    QVector<SqlColumn> columns;
};

#endif // SQLTABLE_H
