#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //QSqlTableModel * modal=new QSqlTableModel();
    QApplication a(argc, argv);
    MainWindow w; //MainWindow의 객체 선언
    w.show();
    return a.exec();

}
