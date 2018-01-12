#include "mainwindow.h"
#include <QApplication>

#include "tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //Tests::testDbTable("/tmp/qimpact/db_test.db");
    Tests::testProductTable();

    return a.exec();
}
