#include "mainwindow.h"
#include "qfiledialog.h"
#include "ui_mainwindow.h"
#include <time.h> // 나이 계산하기 위해
#include <stdio.h>
#include <string>
#include <iostream>
#include <QApplication>

// QSqlTableModel *modal;

// QSqlTableModel *modal = new QSqlTableModel;

// QSqlTableModel(const QSqlDatabase &db = QSqlDatabase())

//~~~~~~~~~~~~~~Mainwindow생성자함수 구현
MainWindow::MainWindow(QWidget *parent) // 생성자
    : QMainWindow(parent) // 위임생성자(중복된 초기화 코드 간소화)
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this);
    setWindowTitle(tr("Patient_Management_Program"));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statusbar->showMessage("Status");

    //title bar 색깔 조정
    //status bar 만들어서 connection 추가
    /*
    QString path = "C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db";

    connOpen(path); // DB 연결
    QSqlTableModel *modal = new QSqlTableModel;
    modal->setTable("TB_PATIENT_INFO_2");
    modal->select();
    while (modal->canFetchMore()) // 256row limit 문제해결방안(FetchMore)
       modal->fetchMore();
    ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    ui->tableView->setSortingEnabled(true);
    //ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set

    //connClose(); //DB연결 닫기
    qDebug() <<"the number of rows : "<<(modal->rowCount());
    qDebug() <<"the number of columns : "<<(modal->columnCount());
    */

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~Mainwindow 소멸자함수 구현
MainWindow::~MainWindow()
{
    delete ui;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Tilte bar에 'X'표시를 클릭하여 종료할 때 정말로 종료할건지 묻고 종료하는 멤버함수 정의 (모든 입력란 초기화)
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("프로그램 종료"),
                                                                tr("프로그램을 종료하시겠습니까?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

// 신환 클릭할 경우 수행하는 멤버함수 정의 (모든 입력란 초기화)
void MainWindow::on_pushButton_newpatient_clicked()
{
    if(!mydb.open()){
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        ui->lineEdit_pntuid->clear();
        ui->lineEdit_pntname->clear();
        ui->lineEdit_birthdate->clear();
        ui->textEdit_adrr->clear();
        ui->lineEdit_hpno->clear();
        ui->lineEdit_hometel->clear();
        ui->lineEdit_FirstVisitDate->clear();
        ui->lineEdit_LastVisitDate->clear();
        ui->lineEdit_age->clear();
    }
    //로우 선택 되어 있는 것 선택 해제 -> 해결됨
    //ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
    //ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    //ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    //ui->tableView->setSortingEnabled(true);


}


// 저장 클릭할 경우 수행하는 멤버함수 정의 ~~~~~~~~~~~~~~~~~~~-> 여기서 pnt_uid 중복 검사하지말고 그냥 신환을 자동으로 생성하자.
void MainWindow::on_pushButton_save_clicked()
{
    //요구사항 정의서에는 신환 클릭 후 입력란이 모두 초기화되고
    //정보입력 후 다시 신환을 클릭하게 되면 새로운 환자 데이터가 추가되는 것으로 정의했음
    //따라서 이기능을 구현하기 위한 알고리즘으로
    //우선 입력란에 무슨 정보가 있던 지 간에 입력창 전부 초기화
    //그다음 조건문을 통해 입력란에 입력되어있는patient code와 같은 환자가 존재한다면
    //Qmessagebox써서 이미 존재하는 환자라는 것을 알리고
    //그렇지 않다면
    //-> 저장 버튼 따로 만드는 것으로 결정

        if(!mydb.open()){ //DB 연결되어 있지 않다면 알림 출력
            QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
        }
        else{ //DB 연결되어 있다면 함수의 기능 수행
            QString  pntname, birthdate, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
            int ipntuid;
            ipntuid=ui->lineEdit_pntuid->text().toInt();// pntuid(환자번호)에 입력되어 있는 Qstring 값을 변수에 저장
            QString Qpntuid = QVariant(ipntuid).toString();

            pntname=ui->lineEdit_pntname->text();
            birthdate=ui->lineEdit_birthdate->text();
            adrr=ui->textEdit_adrr->toPlainText();
            hpno=ui->lineEdit_hpno->text();
            hometel=ui->lineEdit_hometel->text();
            FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
            LastVisitDate=ui->lineEdit_LastVisitDate->text();


            // 만약 해당 ipntuid가 이미 존재한다면? -> QMessagebox("이미 존재하는 환자정보입니다.");
            QSqlQuery exist;
            exist.prepare("select exists (select * from TB_PATIENT_INFO_2 where pnt_uid = :ipntuid)");
            exist.bindValue(":ipntuid", ipntuid);
            exist.exec();
            if(exist.next()){
                qDebug()<<"exist.value : "<< exist.value(0).toInt();
                if(exist.value(0).toInt()){
                    QMessageBox::warning(this,tr("오류"),tr("이미 존재하는 환자입니다. 신규환자 등록은 '신환' 버튼을 클릭한 후, 정보를 입력한 후에 저장을 버튼을 클릭하여 등록하시오.")); // 경고문 메시지 박스 다이어로그 띄우기
                }
                else{
                    QSqlQuery qry;
                    qry.prepare("insert into TB_PATIENT_INFO_2 (pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
                    if(qry.exec()){ // 쿼리문에 오류가 없다면
                        QMessageBox::information(this,tr("Save"),tr("신규환자로 등록 되었습니다.")); // 정상적으로 등록되었다는 알림창 띄우기
                            // QSqlTableModel *modal = new QSqlTableModel;
                            // modal->setTable("TB_PATIENT_INFO_2");
                            // modal->select();
                            // while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
                            // modal->fetchMore();
                        modal->select();
                        ui->tableView->setModel(modal); // -> 이 모델을 table view에 set; // table load를 위한 쿼리(신환후 바로 업데이트 된 table 띄우기 위함)
                            // connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
                    }
                    else // 쿼리문에서 오류발생할 경우 (발견하지 못한 에러)
                    {
                            QMessageBox::critical(this,tr("error::"),qry.lastError().text()); // 쿼리문 에러 출력 (영어)
                    }
                    }
            }

        //bool alreadyExist = false;
        //int exists = 0; // 환자 존재 여부 확인해주는 쿼리문의 return 값을 받은 변수 선언
        //qry.prepare("select exists (select * from TB_PATIENT_INFO_2 where pnt_uid = '"+pntuid+"')");
        //qry.prepare("select * from TB_PATIENT_INFO_2 where pnt_uid ='"+pntuid+"'");
        //qry.prepare("select * from MyTable where pnt_uid=:rowID");
        //qry.bindValue(":rowID",pntuid);
        //qry.prepare("SELECT COUNT (*) FROM TB_PATIENT_INFO_2 ");
        //qry.exec();
        //int rows= 0;
        //if (qry.next()) {
        //rows= qry.value(0).toInt();
        //}
        //int number_Exist = qry.prepare("SELECT COUNT(*) FROM TB_PATIENT_INFO_2");
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //qDebug()<< "환자이미 존재(1) 존재x(0) (qry.prepare) : " << qry.prepare("SELECT COUNT(*) FROM TB_PATIENT_INFO_2 where pnt_uid = '"+ipntuid+"'");
        //qDebug()<< "환자이미 존재(1) 존재x(0) (number_Exist) : " << number_Exist;
        //if(alreadyExist){ // 이미 차트번호가 존재한다면 (즉 저장하려는 환자가 이미 table에 존재한다면)

        //    QMessageBox::critical(this,tr("오류"),tr("이미 존재하는 환자입니다. 차트번호를 확인하고 다시 시도하십시오.")); // 알림 출력

        //}
        //else // 입력한 차트번호가 table에 존재하지 않는다면 (즉 저장하려는 환자가 table에 존재하지 않는다면)
        //{

            // 데이터 추가 Qeury문 작성 입력란에 기재된 정보를 모두 읽어와서 해당 정보들을 하나의 환자데이터로 저장
            //qry.prepare("insert into TB_PATIENT_INFO_2 (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values (:ipntuid,'"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
            //qry.bindValue(":ipntuid", ipntuid);

            //qDebug()<< "ipntuid : " << ipntuid;

            // qry.prepare("insert into TB_TEST (pnt_uid,pnt_name,birth_date,home_addr,hp_no,home_tel,registration_date,lastvisit_date) values ('"+pntuid+"','"+pntname+"','"+birthdate+"','"+adrr+"','"+hpno+"','"+hometel+"','"+FirstVisitDate+"','"+LastVisitDate+"')");
            // qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES ('"+pntuid+"','"+pntname+"')");
            // qry.prepare("INSERT INTO TB_PATIENT_INFO (pnt_uid,pnt_name) VALUES (3212333222333,'손손손')");
        }

        //ui->tableView->setModel(modal); //
}



// 수정 클릭할 경우 수행하는 멤버함수 정의
void MainWindow::on_pushButton_Edit_clicked()
{
    if(!mydb.open()){ // DB 연결되어 있지 않다면 알림 출력
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        QString  pntname, birthdate, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
        int ipntuid;
        ipntuid=ui->lineEdit_pntuid->text().toInt();// pntuid(환자번호)에 입력되어 있는 값을 변수에 저장
        pntname=ui->lineEdit_pntname->text();
        birthdate=ui->lineEdit_birthdate->text();
        adrr=ui->textEdit_adrr->toPlainText();
        hpno=ui->lineEdit_hpno->text();
        hometel=ui->lineEdit_hometel->text();
        FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
        LastVisitDate=ui->lineEdit_LastVisitDate->text();

        QSqlQuery qry;
        qry.prepare("UPDATE TB_PATIENT_INFO_2 SET pnt_name='"+pntname+"',birth_date='"+birthdate+"',home_addr='"+adrr+"',hp_no='"+hpno+"',home_tel='"+hometel+"',registration_date='"+FirstVisitDate+"',lastvisit_date='"+LastVisitDate+"' where pnt_uid=:ipntuid");
        qry.bindValue(":ipntuid", ipntuid);
        if(qry.exec())
        {
            QMessageBox::information(this,tr("수정"),tr("정상적으로 수정이 완료되었습니다.")); // 정상적으로 수정되었다는 알림창 띄우기
            //QSqlTableModel *modal = new QSqlTableModel;
            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) // 256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->select();
            ui->tableView->setModel(modal);
            //connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
        }
        else
        {
            QMessageBox::critical(this,tr("에러"),qry.lastError().text()); //??
        }
    }
}

// 삭제 클릭할 경우 수행하는 멤버함수 정의
void MainWindow::on_pushButton_delete_clicked()
{
    if(!mydb.open()){ //DB 연결되어 있지 않다면 알림 출력
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        QString  pntname, birthdate, adrr, hpno, hometel, FirstVisitDate, LastVisitDate;
        int ipntuid;
        ipntuid=ui->lineEdit_pntuid->text().toInt();// pntuid(환자번호)에 입력되어 있는 값을 변수에 저장
        pntname=ui->lineEdit_pntname->text();
        birthdate=ui->lineEdit_birthdate->text();
        adrr=ui->textEdit_adrr->toPlainText();
        hpno=ui->lineEdit_hpno->text();
        hometel=ui->lineEdit_hometel->text();
        FirstVisitDate=ui->lineEdit_FirstVisitDate->text();
        LastVisitDate=ui->lineEdit_LastVisitDate->text();

        QSqlQuery qry; // 어떤 column에 기반해서 삭제할 건지 쿼리문을 통해 설정 가능
        qry.prepare("DELETE FROM TB_PATIENT_INFO_2 where pnt_uid=:ipntuid"); // 입력으로 들어온 차트번호에 해당하는 환자정보 삭제시키는 쿼리문
        qry.bindValue(":ipntuid", ipntuid);
        QMessageBox::StandardButton reply; // 유저로 부터 응답받는 메세지 박스 reply 정의
        reply = QMessageBox::question(this, "삭제", "해당 환자 정보를 삭제하시겠습니까?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) { // 유저가 '예' 클릭 시
          qDebug() << "Yes was clicked";
          if(qry.exec()) // 쿼리문이 정상적으로 수행된다면
          {
              QMessageBox::information(this,tr("삭제"),tr("정상적으로 삭제가 완료되었습니다.")); // 정상적으로 삭제되었다는 알림창 띄우기
              //QSqlTableModel *modal = new QSqlTableModel;
              //modal->setTable("TB_PATIENT_INFO_2");
              //modal->select();
              //while (modal->canFetchMore()) // 256row limit 문제해결방안(FetchMore)
              //   modal->fetchMore();
              modal->select();
              ui->tableView->setModel(modal);
              //connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
          }
          else // 쿼리문이 수행되지 않는다면
          {
              QMessageBox::critical(this,tr("error::"),qry.lastError().text()); //에러 출력
          }

        }
        else { // 유저가 '아니오' 클릭 시
          qDebug() << "Yes was *not* clicked";
        }
    }
}



// 환자 목록 클릭시 입력란에 해당 환자정보 띄우기 위한 멤버함수 정의 ( 쿼리문이 아니라 Q~mapped 사용 가능.) %%%%%%%%%-> table record하나 클릭할 시 뭐가 들어오는지
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    //~~~~~~~~~현재 날짜 구하기 (만나이 계산 위해)
    struct tm* localtime(const time_t* timer);
    struct tm
    {
        int tm_sec; // seconds after the minute [0,60]
        int tm_min; // minutes after the hour [0,59]
        int tm_hour; // hours since midnight [0,23]
        int tm_mday; // day of the month [1,31]
        int tm_mon; // months since January [0,11] (현재 날짜 구하려면 1 더해줄 것)
        int tm_year; // years since 1900 (현재날짜 구하려면 tm_year에 1900 더할 것)
        int tm_wday; // days since Sunday [0,6]
        int tm_yday; // days since January [0.365]
        int tm_isdst; // daylight savings time flag
    };

    struct tm *t;
    time_t tnow;
    time(&tnow);
    t = (struct tm*) localtime(&tnow);
    QString Qcurrentdate;

    if (t->tm_mon + 1 < 10 && t-> tm_mday < 10){
        Qcurrentdate = QString::number(t->tm_year + 1900) + '0' + QString::number(t->tm_mon + 1) + '0' + QString::number(t->tm_mday);
    }
    else if (t->tm_mon + 1 < 10){
       Qcurrentdate = QString::number(t->tm_year + 1900) + '0' + QString::number(t->tm_mon + 1) + QString::number(t->tm_mday);
    }
    else if (t->tm_mday < 10){
       Qcurrentdate = QString::number(t->tm_year + 1900) + QString::number(t->tm_mon + 1) + '0' + QString::number(t->tm_mday);
    }
    else{
       Qcurrentdate = QString::number(t->tm_year + 1900) + QString::number(t->tm_mon + 1) + QString::number(t->tm_mday);
    }

    //qDebug() << "Qcurrentdate : "<< Qcurrentdate;
    int icurrentdate = Qcurrentdate.toInt();
    qDebug() << "icurrentdate : "<< icurrentdate;
    //~~~~~~~~~~~~~~~~~~~ 여기까지 나이 계산

    //
    int rowidx = index.row();
    QString val=ui->tableView->model()->index(rowidx,0).data().toString(); // tableview에서 user가 선택한 인덱스를 취해서 이 인덱스를 변환하고 값을 취해서 Qstring 변수로 옮김
    qDebug()<<"index : "<< index;
    qDebug()<<"roidx(index.row()) : "<< rowidx;
    qDebug()<<""<<"val (data(rowidx,0).toString())"<<val;

    ui->lineEdit_pntuid->setText(ui->tableView->model()->index(rowidx,0).data().toString());
    ui->lineEdit_pntname->setText(ui->tableView->model()->index(rowidx,1).data().toString());
    ui->lineEdit_birthdate->setText(ui->tableView->model()->index(rowidx,2).data().toString());
    ui->textEdit_adrr->setPlainText(ui->tableView->model()->index(rowidx,3).data().toString());
    ui->lineEdit_hpno->setText(ui->tableView->model()->index(rowidx,4).data().toString());
    ui->lineEdit_hometel->setText(ui->tableView->model()->index(rowidx,5).data().toString());
    ui->lineEdit_FirstVisitDate->setText(ui->tableView->model()->index(rowidx,6).data().toString());
    ui->lineEdit_LastVisitDate->setText(ui->tableView->model()->index(rowidx,7).data().toString());

    QString Qbirthdate = ui->tableView->model()->index(rowidx,2).data().toString(); //birth_date 값 Qbirthdate에 저장
    Qbirthdate = Qbirthdate.remove('-'); //Qbirthdate에서 '-'문자 제거
    qDebug()<<"Qbirthdate : "<<Qbirthdate;
    int ibirthdate = Qbirthdate.toInt();  // Qbirthdate를 int자료형으로 변환하여 ibirthdate에 저장
    int iage = (icurrentdate - ibirthdate)/10000; // 만 나이 계산 하여 iage에 저장
    QString Qage =  QVariant(iage).toString(); // lineEdit에 set하기 위해 QString으로 변환하여 Qage에 저장
    ui->lineEdit_age->setText(Qage); //birth_date colmun value로 부터 계산된 나이 출력

}

// search bar(검색창) Enter 입력시 수행하는 일 정의
void MainWindow::on_lineEdit_search_returnPressed()
{
    if(!mydb.open()){ // DB 연결되어 있지 않다면 알림 출력
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        qDebug()<< "combobox "<<ui->comboBox->currentText();
        QString qss = ui->comboBox->currentText();
        if (qss == "이름/차트번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "이름/차트번호맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_uid LIKE '%%1%' OR pnt_name LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "환자이름")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "환자이름 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_name LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "차트번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "차트번호 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_uid LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "휴대전화")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "휴대전화 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("hp_no LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "전화번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "전화번호 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("home_tel LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else
        {
            qDebug()<< "프로그램 오류";
        }
    }
}


// search bar(검색창) 검색 버튼 클릭할 경우 수행하는 일 정의
void MainWindow::on_pushButton_search_clicked()
{
    if(!mydb.open()){ // DB 연결되어 있지 않다면 알림 출력
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        qDebug()<< "combobox "<<ui->comboBox->currentText();
        QString qss = ui->comboBox->currentText();
        if (qss == "이름/차트번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "이름/차트번호맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_uid LIKE '%%1%' OR pnt_name LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "환자이름")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "환자이름 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_name LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "차트번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "차트번호 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("pnt_uid LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "휴대전화")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "휴대전화 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("hp_no LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else if(qss == "전화번호")
        {
            qDebug()<< "qss"<<qss;
            qDebug()<< "전화번호 맞네";
            regxpattern = "";
            // enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
            QString pattern;
            pattern = ui->lineEdit_search->text(); // lineEdit_search로부터 가져온 값 input_value에 저장
            // 입력값이 저장된 pattern에 따라 filtering 하여 결과를 table에 출력
            //QLineEdit * lineEdit_Search = new QLineEdit;
            //lineEdit_Search->setPlaceholderText("search");
            regxpattern = pattern;
            //QString filter = textEdit->text();
            //QSqlTableModel *modal = new QSqlTableModel;

            //modal->setTable("TB_PATIENT_INFO_2");
            //modal->select();
            //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
            //   modal->fetchMore();
            modal->setFilter(QString("home_tel LIKE '%%1%'").arg(regxpattern));
            modal->select();
            ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
        }
        else
        {
            qDebug()<< "프로그램 오류";
        }
    }
}

//comboBox 설정 바꾸면 placeholdertext문구 바꾸기
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "이름/차트번호")
    {
        ui->lineEdit_search->setPlaceholderText("환자 이름 또는 차트 번호로 검색");
    }
    else if(arg1 == "환자이름")
    {
        ui->lineEdit_search->setPlaceholderText("환자 이름으로 검색");
    }
    else if(arg1 == "차트번호")
    {
        ui->lineEdit_search->setPlaceholderText("차트 번호로 검색");
    }
    else if(arg1 == "휴대전화")
    {
        ui->lineEdit_search->setPlaceholderText("휴대전화로 검색");
    }
    else if(arg1 == "전화번호")
    {
        ui->lineEdit_search->setPlaceholderText("전화번호로 검색");
    }
    else
    {
        qDebug()<< "프로그램 오류";
    }
}



//csv파일 내보내기 버튼 클릭할 경우 수행하는 일 정의
void MainWindow::on_pushButton_exportCSV_clicked()
{
    // <- 현재 tableView에 보이는 데이터들만 저장하도록 구현해야됨 -> 결과는 ? : tableView에 보이는 데이터들만 저장됨

    if(!mydb.open()){ //DB 연결되어 있지 않다면 알림 출력
        QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오")); // 경고문 메시지 박스 다이어로그 띄우기
    }
    else{
        // 저장할 경로를 설정하기 위한 dailogue 설정
        QFileDialog dlg; // dialogue 설정
        QString strFilter = "csv file (*.csv) ;; text file (*.txt) ;; All files (*.*)"; //extention은 "표시할 내용 (*.확장자명)" 형태로 작성
        QString path = dlg.getSaveFileName(this,"CSV파일 저장","./",strFilter); // 유저로부터 선택된 파일이름 가져오기
        QFileInfo fi(path);
        if(path.isEmpty()) return;
        if(fi.exists()) {
           QMessageBox::StandardButton btn = QMessageBox::question(this,"File Exists","File exists!\r\nOverwrite the file?",QMessageBox::Yes | QMessageBox::No);
           if(btn == QMessageBox::Yes) on_pushButton_exportCSV_clicked();
           return;
        }
        // [Collect model data to QString]
        QString textData;
        int rows = modal->rowCount();
        int columns = modal->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += modal->data(modal->index(i,j)).toString();
                    textData += ", ";      // for .csv file format
            }
            textData += "\n";             // (optional: for new line segmentation)
        }

        // [Save to file] (header file <QFile> needed)
        // .csv 파일저장
        QFile csvFile(path);
        if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

            QTextStream out(&csvFile);
            out.QTextStream::setEncoding(QStringConverter::Utf32);
            out << textData; //text 데이터 파일에 내보내기


            csvFile.close();
        }

        // .txt 파일 저장
        QFile txtFile(path);
        if(txtFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

            QTextStream out(&txtFile);
            out << textData; //text 데이터 파일에 내보내기

            txtFile.close();
        }
    }
}


//DB 파일불러오기 버튼 클릭할 경우 수행하는 일 정의
void MainWindow::on_pushButton_Load_DB_clicked()
{
    QFileDialog dlg; // dialogue 설정
    QString strFilter = "DB file (*.db) ;; All files (*.*)"; //extention은 "표시할 내용 (*.확장자명)" 형태로 작성
    QString path = dlg.getOpenFileName(this,"DB파일 불러오기","./",strFilter); // 유저로부터 선택된 파일이름 가져오기
    qDebug() << "path : " << path ;
    qDebug() << "path.right(3) : " << path.right(3) ;

    if(path=="") // 입력된 DB파일의 경로가 없다면
    {
        //QMessageBox::information(this,tr("오류"),tr("연결된 DataBase가 존재하지 않습니다. DataBase를 로드하여 다시 시도하십시오"));
        //QString path = "C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db";
        //connClose();
    }
    else if(!(path.right(3) == ".db")) // 확장자가 .DB가 아니라면
    {
        QMessageBox::critical(this,tr("오류"),tr("형식에 맞지 않는 파일입니다."));
        //QString path = "C:/Users/Osstem/Documents/patient_management_program/PATIENT_INFO.db";
    }
    else{
    connOpen(path); // 유저가 선택한 DB 파일을 불러옴 (DB연결)
    modal = new QSqlTableModel(this); //QsqlTableModel 클래스 타입의 포인터 초기화
    Load_Table(); // User로부터 선택된 DB파일을 연결하고 그 DB 파일에 존재하는 Table을 TableView에 띄우기
    }

    //다른 기능들 테스트
}



