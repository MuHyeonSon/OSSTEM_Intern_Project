#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

//~~~~~~~~~~~~~~Mainwindow생성자함수 구현
MainWindow::MainWindow(QWidget *parent) // 생성자
    : QMainWindow(parent) // 위임생성자(중복된 초기화 코드 간소화)
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this);
    /* DB 연동인데 헤더파일에 함수형태로 사용할 수 있도록 정의해놓음
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db");

    if(!mydb.open())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("Connected...");
    */
    QSqlQueryModel * modal=new QSqlQueryModel();
    connOpen();
    QSqlQuery * qry=new QSqlQuery(mydb);
    qry->prepare("SELECT * from TB_PATIENT_INFO");
    qry->exec();
    modal->setQuery(*qry); // query를 모델에 set -> 이 모델을 tabel view에 set
    ui->tableView->setModel(modal);

    connClose();
    qDebug() <<(modal->rowCount());


}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~Mainwindow 소멸자함수 구현
MainWindow::~MainWindow()
{
    delete ui;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// 신환 클릭할 경우 수행하는 멤버함수 정의
void MainWindow::on_pushButton_save_clicked()
{
    //요구사항 정의서에는 신환 클릭 후 입력란이 모두 초기화되고
    //정보입력 후 다시 신환을 클릭하게 되면 새로운 환자 데이터가 추가되는 것으로 정의했음
    //따라서 이기능을 구현하기 위한 알고리즘으로
    //우선 입력란에 무슨 정보가 있던 지 간에 입력창 전부 초기화
    //그다음 조건문을 통해 입력란에 입력되어있는patient code와 같은 환자가 존재한다면
    //Qmessagebox써서 이미 존재하는 환자라는 것을 알리고
    //그렇지 않다면

    QString pntuid, pntname, birthdate, age, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
    pntuid=ui->lineEdit_pntuid->text();
    pntname=ui->lineEdit_pntname->text();
    birthdate=ui->dateEdit_birthdate->text();
    //age=ui->lineEdit_pntuid->text();
    adrr=ui->textEdit_adrr->toPlainText();
    hpno=ui->lineEdit_hpno->text();
    hometel=ui->lineEdit_hometel->text();
    FirstVisitDate=ui->dateEdit_FirstVisitDate->text();
    LastVisitDate=ui->dateEdit_LastVisitDate->text();

    //QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    //mydb.setDatabaseName("C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db");

    //----------------
    //영상에서 connOpen 부분
    // connOpen() connection database
    // --------------

    connOpen(); // DB connect
    QSqlQuery qry;
    qry.prepare("insert into TB_PATIENT_INFO (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntuid+"','"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
    //qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES ('"+pntuid+"','"+pntname+"')");
    //qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES (3212333222333,'손손손')");
    //qry.bindValue();

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        connClose(); //위 쿼리 성공적으로 실행됐으면 DB연결 닫기
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void MainWindow::on_pushButton_Edit_clicked()
{

}

