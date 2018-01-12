#include "sqltable.h"

SqlTable::SqlTable(QString name, QVector<SqlColumn> columns)
{
    this->name = name;
    this->columns = columns;
}

QString SqlTable::create()
{
    QString out = "CREATE TABLE %1 (%2);";
    QString fields = "";
    for(int i=0;i<this->columns.size();i++)
    {
        fields += this->columns[i].create();
        if(i < this->columns.size()-1)
            fields += ", ";
    }
    out = out.arg(this->name, fields);
    return out;
}

QString SqlTable::getName()
{
    return this->name;
}

QString SqlTable::drop()
{
    return QString("DROP TABLE %1;").arg(this->name);
}
