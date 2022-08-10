#include "mainwindow.h"
#include "ui_mainwindow.h"

// 생성자함수 구현
MainWindow::MainWindow(QWidget *parent) // 생성자
    : QMainWindow(parent) // 위임생성자(중복된 초기화 코드 간소화)
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db");

    if(!mydb.open())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("Connected...");

}
//~생성자함수구현

MainWindow::~MainWindow()
{
    delete ui;
}

//connOpen();
//QSqlQuery qry;
//qry.prepare("select * from TB_PATIENT_INFO"); //ID와 password 정확하다면 로그인 되는 부분이었음

//if(qry.exec( ))
//{

//}

            //sqlite connect할 것

// 저장 클릭할 경우 수행하는 일 정의 (
void MainWindow::on_pushButton_save_clicked()
{
    //QString pntuid, pntname;
}

