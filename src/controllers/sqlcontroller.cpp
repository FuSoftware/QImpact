#include "sqlcontroller.h"

#include <QDebug>
#include <QtSql/QSqlError>
#include <QFileInfo>
#include <QDir>

SqlController::SqlController(QString file_path, QObject *parent) : QObject(parent)
{
    this->m_file_path = file_path;
    initDb(file_path);
}

QStringList SqlController::driverList()
{
    return this->m_db.drivers();
}

bool SqlController::open()
{
    bool ok = this->m_db.open();

    if(!ok)
    {
        qDebug() << "Error while opening database :" << this->m_db.lastError().databaseText();
        qDebug() << "Driver" << this->m_db.driverName() << "available ?" << this->m_db.isDriverAvailable(this->m_db.driverName());
        qDebug() << "Available drivers :" << driverList();
    }

    return ok;
}

void SqlController::close()
{
    this->m_db.close();
}

void SqlController::initDb(QString file_path)
{
    //Make path
    QFileInfo f = QFileInfo(file_path);
    QDir dir(f.absolutePath());
    if (!dir.exists())
      dir.mkpath(".");

    this->m_db = QSqlDatabase::addDatabase("QSQLITE");

    this->m_db.setHostName("localhost");
    this->m_db.setDatabaseName(file_path);
}

QSqlError SqlController::getLastError()
{
    return this->m_db.lastError();
}

QSqlQuery SqlController::runQuery(const QString& sql)
{
    QSqlQuery query(sql, this->m_db);
    query.exec();
    return query;
}

QSqlTableModel *SqlController::getTable(const QString &table)
{
    return this->getTable(table, QVector<QString>());
}

QSqlTableModel *SqlController::getTable(const QString &table, QVector<QString> headers)
{
    QSqlTableModel *model = new QSqlTableModel(this, this->m_db);
    model->setTable(table);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    //Headers
    for(int i=0;i<headers.size();i++)
        model->setHeaderData(i, Qt::Horizontal, headers[i]);

    return model;

}
