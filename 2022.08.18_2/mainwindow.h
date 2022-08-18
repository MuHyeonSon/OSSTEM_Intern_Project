#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "ui_mainwindow.h" // ui access하기 위해

#include <QRegExp> //테이블 검색 filtering에 사용
#include <QSortFilterProxyModel>
#include <QApplication>

// 함수 선언은 헤더에 구현은 cpp에?

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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void Load_Table()
    {
        //~~~~~~~~~~~~~~~~~연동한 DB의 table load하기
        QSqlQueryModel * modal=new QSqlQueryModel();
        connOpen();//DB 연결
        QSqlQuery * qry=new QSqlQuery(mydb);
        qry->prepare("SELECT * from TB_PATIENT_INFO_2");
        //qry->prepare("SELECT * from TB_TEST");
        qry->exec();
        //256row limit 문제해결방안(FetchMore)
        modal->setQuery(*qry); // query를 모델에 set
        while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
           modal->fetchMore();
        ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set

        connClose(); //DB연결 닫기
        qDebug() <<"the number of rows : "<<(modal->rowCount());
        qDebug() <<"the number of columns : "<<(modal->columnCount());
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }




public:
    MainWindow(QWidget *parent = nullptr); // MainWindow 클래스의 생성자선언
    ~MainWindow(); // MainWindow 클래스의 소멸자선언

private slots:

    void on_pushButton_save_clicked();

    void on_pushButton_Edit_clicked();

    void on_pushButton_delete_clicked();

    void on_tableView_clicked(const QModelIndex &index);



    void on_pushButton_newpatient_clicked();

    void on_lineEdit_search_returnPressed();


    void on_pushButton_search_clicked();

    void on_pushButton_exportCSV_clicked();

private:

    Ui::MainWindow *ui;

    QString regxpattern ;





}; // 여기까지 MainWindow class 구현부

#endif // MAINWINDOW_H
