#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "ui_mainwindow.h" // ui access하기 위해
#include <QMessageBox>

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

    QSqlDatabase mydb = QSqlDatabase();
    QSqlTableModel *modal;
    //QSqlDatabase *p_mydb = &mydb;

    //QSqlTableModel *modal = new QSqlTableModel(0, mydb);
    //QSqlTableModel *modal;

    void connClose() // DB 연결 해제 (멤버함수1)
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
        ui->label->setText("status");
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
            qDebug()<< " mydb : " << mydb;
            //qDebug()<< " modal의 DB : " << modal->database() ;
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
        ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->setColumnWidth(0, (this->width())*1/16); // 차트번호 column 너비
        ui->tableView->setColumnWidth(1, (this->width())*1/14); // 이름 column 너비
        ui->tableView->setColumnWidth(2, (this->width())*1/13); // 생년월일 column 너비
        ui->tableView->setColumnWidth(3, (this->width())*4/16); // 주소 column 너비
        ui->tableView->setColumnWidth(4, (this->width())*1/11); // 휴대전화 column 너비
        ui->tableView->setColumnWidth(5, (this->width())*1/11); // 전화번호 column 너비
        ui->tableView->setColumnWidth(6, (this->width())*1/13); // 최초내원 column 너비
        ui->tableView->setColumnWidth(7, (this->width())*1/13); // 최종내원 column 너비

        //ui->tableView->setTextAlignmen()
        //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //column간격 비율 똑같이 맞춰짐 -> 최대 글자로 맞추는 것으로 하려면??
        modal->setHeaderData(0,Qt::Horizontal, "차트번호");
        modal->setHeaderData(1,Qt::Horizontal, "이름");
        modal->setHeaderData(2,Qt::Horizontal, "생년월일");
        modal->setHeaderData(3,Qt::Horizontal, "주소");
        modal->setHeaderData(4,Qt::Horizontal, "휴대전화");
        modal->setHeaderData(5,Qt::Horizontal, "전화번호");
        modal->setHeaderData(6,Qt::Horizontal, "최초내원");
        modal->setHeaderData(7,Qt::Horizontal, "최종내원");


        qDebug() <<"the number of rows : "<<(modal->rowCount());
        qDebug() <<"the number of columns : "<<(modal->columnCount());
        if(modal->rowCount() == 0){
            connClose(); //DB연결 닫기
            QMessageBox::critical(this,tr("오류"),tr("불러온 DB 파일의 Table이 row의 개수가 0입니다. DB 파일에서 불러올 Table 이름이 'TB_PATIENT_INFO_2'가 맞는지, column 헤더의 형식이 맞는지 확인 후 다시 시도하시오."));

        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    };

    //QSqlTableModel * modal=new QSqlTableModel(); //클래스 MainWindow의 멤버변수





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
