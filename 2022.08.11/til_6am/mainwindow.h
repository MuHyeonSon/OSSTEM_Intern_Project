#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#include "ui_mainwindow.h" // ui access하기위해

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow //class mainwindow 선언
{
    Q_OBJECT

//~~~~~~~~~~~~~~~DataBase connect 멤버 함수 구현

public:
    QSqlDatabase mydb;

    void connClose() // DB
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen() // DB open하고 정상적으로 open 되었는지 여부 체크 함수
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db");

        if(!mydb.open()){
            qDebug()<<("Failed to open the database");
            ui->label->setText("Failed to open the database");
            return false;
        }
        else{
            qDebug()<<("Connected...");
            ui->label->setText("Connected...");
            return true;
        }
    };



public:
    MainWindow(QWidget *parent = nullptr); // MainWindow 클래스의 생성자선언
    ~MainWindow(); // MainWindow 클래스의 소멸자선언

private slots:

    void on_pushButton_save_clicked();

    void on_pushButton_Edit_clicked();

private:
    Ui::MainWindow *ui;
}; // 여기까지 MainWindow class 구현부

#endif // MAINWINDOW_H
