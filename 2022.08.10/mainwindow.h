#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow //class mainwindow 선언
{
    Q_OBJECT
/*
public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("./TB_PATIENT_INFO.db");

        if(!mydb.open()){
            qDebug()<<("Failed to open database");
            return false;
        }
        else{
            qDebug()<<("Connected...");
            return true;
        }
    */


public:
    MainWindow(QWidget *parent = nullptr); // 생성자선언
    ~MainWindow(); //소멸자

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
}; // 여기까지 MainWindow class 구현부

#endif // MAINWINDOW_H
