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

// 함수 선언은 헤더에 구현은 cpp에? ㄴㄴㄴ -> 클래스 선언부와 구현부

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow //class mainwindow 선언
{
    Q_OBJECT

//~~~~~~~~~~~~~~~DataBase connect 멤버 함수 구현

public:
    QSqlDatabase mydb;

    void connClose() // DB 연결 해제 (멤버함수1)
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(QString path) // DB open(연결)하고 정상적으로 open 되었는지 여부 체크 함수 (멤버함수2)
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE"); // DB를 저장할 변수 선언 및 DBMS 설정! (Adds a database to the list of database connections)
        mydb.setDatabaseName(path); // db파일 경로설정
        //mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db"); //db파일 경로설정

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
    void Load_Table() //아예 여기에 인수로 쿼리문을 받게 할까?? 그렇게 하려면 QSqlQuery 형식의 qry객체를 보내야됨 근데 QsqlModel은 qry 받지 않음
    {
        //~~~~~~~~~~~~~~~~~연동한 DB의 table load (지금 현재 이 함수는 불러온 DB파일에서 미리 (개발자가)설정한 table의 전체 데이터를 table view에 셋팅하는 기능을 함
        modal->setTable("TB_PATIENT_INFO_2");
        modal->select();
        while (modal->canFetchMore()) // 256row limit 문제해결방안(FetchMore)
           modal->fetchMore();
        ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
        ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
        ui->tableView->setSortingEnabled(true);

        connClose(); //DB연결 닫기
        qDebug() <<"the number of rows : "<<(modal->rowCount());
        qDebug() <<"the number of columns : "<<(modal->columnCount());
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

    QSqlTableModel * modal=new QSqlTableModel(); //클래스 MainWindow의 멤버변수





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

    void on_pushButton_Load_DB_clicked();

private:

    Ui::MainWindow *ui;

    QString regxpattern ;






}; // 여기까지 MainWindow class 구현부

#endif // MAINWINDOW_H