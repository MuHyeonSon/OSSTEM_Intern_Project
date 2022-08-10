#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

// 저장 클릭할 경우 수행하는 일 정의
void MainWindow::on_pushButton_save_clicked()
{
    QString pntuid, pntname, birthdate, age, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
    pntuid=ui->lineEdit_pntuid->text();
    pntname=ui->lineEdit_pntname->text();
    birthdate=ui->lineEdit_birthdate->text();
    //age=ui->lineEdit_pntuid->text();
    adrr=ui->lineEdit_adrr->text();
    hpno=ui->lineEdit_hpno->text();
    hometel=ui->lineEdit_hometel->text();
    FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
    LastVisitDate=ui->lineEdit_LastVisitDate->text();

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db");

    //----------------
    //영상에서 connOpen 부분
    // connOpen() connection database
    // --------------

    QSqlQuery qry;
    //qry.prepare("insert into TB_PATIENT_INFO (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntuid+"','"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
    qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES ('"+pntuid+"','"+pntname+"')");
    //qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES (1231231,'손무현')");
    //qry.bindValue();

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

