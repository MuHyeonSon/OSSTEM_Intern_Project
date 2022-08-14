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
    //~~~~~~~~~~~~~~~~~연동한 DB의 table load하기

    /*
    QSqlQueryModel * modal=new QSqlQueryModel();
    connOpen();//DB 연결
    QSqlQuery * qry=new QSqlQuery(mydb);
    qry->prepare("SELECT * from TB_PATIENT_INFO_2");
    qry->exec();
    //256row limit 문제해결방안(FetchMore)
    modal->setQuery(*qry); // query를 모델에 set
    while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
       modal->fetchMore();
    */
    connOpen();//DB 연결
    QSqlTableModel *modal = new QSqlTableModel;
    modal->setTable("TB_PATIENT_INFO_2");
    modal->select();
    while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
       modal->fetchMore();
    ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set

    connClose(); //DB연결 닫기
    qDebug() <<"the number of rows : "<<(modal->rowCount());
    qDebug() <<"the number of columns : "<<(modal->columnCount());
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

    QString pntuid, pntname, birthdate, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
    pntuid=ui->lineEdit_pntuid->text(); //pntuid(환자번호)에 입력되어 있는 Qstring 값을 변수에 저장
    pntname=ui->lineEdit_pntname->text();
    birthdate=ui->lineEdit_birthdate->text();
    adrr=ui->textEdit_adrr->toPlainText();
    hpno=ui->lineEdit_hpno->text();
    hometel=ui->lineEdit_hometel->text();
    FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
    LastVisitDate=ui->lineEdit_LastVisitDate->text();

    connOpen(); // DB connect
    QSqlQuery qry;
    qry.prepare("insert into TB_PATIENT_INFO_2 (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntuid+"','"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
    //qry.prepare("insert into TB_TEST (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntuid+"','"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
    //qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES ('"+pntuid+"','"+pntname+"')");
    //qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES (3212333222333,'손손손')");
    //qry.bindValue();

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Save"),tr("Saved")); // 정상적으로 등록되었다는 알림창 띄우기
        QSqlTableModel *modal = new QSqlTableModel;
        modal->setTable("TB_PATIENT_INFO_2");
        modal->select();
        while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
           modal->fetchMore();
        ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set; // table load를 위한 쿼리(신환후 바로 업데이트 된 table 띄우기 위함)
        connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


// 수정 클릭할 경우 수행하는 멤버함수 정의
void MainWindow::on_pushButton_Edit_clicked()
{
    QString pntuid, pntname, birthdate, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
    pntuid=ui->lineEdit_pntuid->text(); //pntuid(환자번호)에 입력되어 있는 Qstring 값을 변수에 저장
    pntname=ui->lineEdit_pntname->text();
    birthdate=ui->lineEdit_birthdate->text();
    adrr=ui->textEdit_adrr->toPlainText();
    hpno=ui->lineEdit_hpno->text();
    hometel=ui->lineEdit_hometel->text();
    FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
    LastVisitDate=ui->lineEdit_LastVisitDate->text();
    connOpen();
    QSqlQuery qry;
    qry.prepare("UPDATE TB_PATIENT_INFO_2 SET pnt_uid='"+pntuid+"',pnt_name='"+pntname+"',birth_date='"+birthdate+"',home_addr='"+adrr+"',hp_no='"+hpno+"',home_tel='"+hometel+"',registration_date='"+FirstVisitDate+"',lastvisit_date='"+LastVisitDate+"' where pnt_uid='"+pntuid+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("수정"),tr("정상적으로 수정이 완료되었습니다.")); // 정상적으로 수정되었다는 알림창 띄우기
        QSqlTableModel *modal = new QSqlTableModel;
        modal->setTable("TB_PATIENT_INFO_2");
        modal->select();
        while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
           modal->fetchMore();
        ui->tableView->setModel(modal);
        connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

// 삭제 클릭할 경우 수행하는 멤버함수 정의
}

