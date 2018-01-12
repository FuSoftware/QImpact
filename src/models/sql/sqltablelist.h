#ifndef SQLTABLELIST_H
#define SQLTABLELIST_H

#include "sqltable.h"
#include <QVector>

namespace SQL_TABLE_LIST
{
    SqlTable *SQL_TABLE_PRODUCTS = new SqlTable("products"
                                               ,{
                                                   SqlColumn("ID","TEXT"),
                                                   SqlColumn("LABEL", "TEXT"),
                                                   SqlColumn("QUANTITY","INT"),
                                                   SqlColumn("WEIGHT","REAL"),
                                               });


}

#endif // SQLTABLELIST_H
