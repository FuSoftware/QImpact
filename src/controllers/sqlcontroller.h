#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QSqlDriver>
#include <QSqlDriverPlugin>

class SqlController : public QObject
{
    Q_OBJECT
public:
    SqlController(QString file_path, QObject *parent = nullptr);
    bool open();
    void close();

    QStringList driverList();

    QSqlQuery runQuery(const QString& sql);
    QSqlError getLastError();

    QSqlTableModel *getTable(const QString &table, QVector<QString> headers);
    QSqlTableModel *getTable(const QString &table);

signals:

public slots:

private:
    void initDb(QString file_path);

    QString m_file_path;
    QSqlDatabase m_db;
};

#endif // SQLCONTROLLER_H
