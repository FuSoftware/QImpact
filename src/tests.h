#ifndef TESTS_H
#define TESTS_H

#include <QString>
#include <QVector>

class Tests
{
public:
    Tests();

    static void testSql(QString path, QVector<QString> schema_queries, QVector<QString> use_queries);
    static void testDbTable(QString path);
    static void testProductTable();

private:
    static QString DB_PATH;
};

#endif // TESTS_H
