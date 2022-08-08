#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> //QMainWindow 헤더 include
#include <QDebug> // 디버깅을 위한 헤더
#include <QtSql/QSqlQuery> // QSqlQuery class는 SQL문을 실행하고 manipulating하는 방법을 제공

QT_BEGIN_NAMESPACE //
namespace Ui { class MainWindow; } //
QT_END_NAMESPACE //

class MainWindow : public QMainWindow //
{
    Q_OBJECT //

public:
    MainWindow(QWidget *parent = nullptr); //
    ~MainWindow(); //

private:
    Ui::MainWindow *ui; //
};
#endif // MAINWINDOW_H


/*
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> //QMainWindow 헤더 include
#include <QtSql/QSqlQuery> // QSqlQuery class는 SQL문을 실행하고 manipulating하는 방법을 제공
#include <QDebug>
#include <QFileInfo>

#include <QtDebug> // 디버깅을 위한 헤더
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE //
namespace Ui { class MainWindow; } //
QT_END_NAMESPACE //

class MainWindow : public QMainWindow //
{
    Q_OBJECT //

public:
    MainWindow(QWidget *parent = nullptr); //
    ~MainWindow(); //


};

//class db_manager{
//public:
//    db_manager(const QString& path);
//private:
//    QSqlDatabase my_db;
//};
//
//db_manager::db_manager(const QString& path){
//    my_db = QSqlDatabase::addDatabase("QSQLITE");
//   my_db.setDatabaseName(path);
//
//    if(my_db.open()){
//        qDebug() << "success DB connection.\n";
//    }
//    else{
//        qDebug() << "fail DB connection.\n";
//    }
//}

#endif // MAINWINDOW_H
*/
