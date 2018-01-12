#include "tests.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include "models/sql/sqltablelist.h"
#include "models/sql/sqltable.h"

#include "controllers/sqlcontroller.h"

#include "view/database/qproducttablewidget.h"

QString Tests::DB_PATH = "/tmp/qimpact/db_test.db";

void Tests::testSql(QString path, QVector<QString> schema_queries, QVector<QString> use_queries)
{
    SqlController *c = new SqlController(path);
    bool ok = c->open();

    if(!ok)
        return;

    for(int i=0;i<schema_queries.size();i++)
        c->runQuery(schema_queries[i]);

    for(int i=0;i<use_queries.size();i++)
    {
        QSqlQuery q = c->runQuery(use_queries[i]);

        if(q.isSelect())
        {
            QString out = "";
            while(q.next())
            {
                QSqlRecord rec = q.record();
                for(int i=0;i<rec.count();i++)
                    out += rec.value(i).toString() + ", ";
            }
            qDebug() << out;
        }
    }

    c->close();
}

void Tests::testDbTable(QString path)
{
    QVector<QString> schema_queries;
    QVector<QString> use_queries;

    //Delete possible existing table
    schema_queries.append(QString("DROP TABLE db_test;"));

    //Re-create the test table
    schema_queries.append(QString("CREATE TABLE db_test (id INTEGER, name TEXT, age REAL);"));

    //Add records
    schema_queries.append(QString("INSERT INTO db_test (id, name, age) "
                                  "VALUES"
                                  "(0, 'Jean', 40.5),"
                                  "(1, 'Marc', 25.1),"
                                  "(2, 'Luc', 30.6),"
                                  "(3, 'Michel', 21.9)"));

    //Read the records
    use_queries.append(QString("SELECT * FROM db_test WHERE id = 3;"));
    use_queries.append(QString("SELECT * FROM db_test WHERE name LIKE 'Marc';"));
    use_queries.append(QString("SELECT * FROM db_test WHERE age > 30.1;"));
    testSql(path, schema_queries, use_queries);
}

void Tests::testProductTable()
{
    SqlController *c = new SqlController(Tests::DB_PATH);
    bool ok = c->open();

    if(!ok)
        return;

    SqlTable *t = SQL_TABLE_LIST::SQL_TABLE_PRODUCTS;
    //c->runQuery(t->drop());
    //c->runQuery(t->create());
    //c->runQuery(QString("INSERT INTO %1 (%2) VALUES(%3)").arg(t->getName(), "ID, LABEL, QUANTITY, WEIGHT", "'PA', 'Produit A', 95, 0.8"));

    QSqlTableModel *m = c->getTable(t->getName());
    QProductTableWidget *w = new QProductTableWidget();
    w->setTable(m);
    w->show();
}
