#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <time.h> // 나이 계산하기 위해
#include <stdio.h>
#include <string>
#include <iostream>
#include <QApplication>
#include <QSortFilterProxyModel>



//~~~~~~~~~~~~~~Mainwindow생성자함수 구현
MainWindow::MainWindow(QWidget *parent) // 생성자
    : QMainWindow(parent) // 위임생성자(중복된 초기화 코드 간소화)
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this);
    connOpen();//DB 연결
    QSqlTableModel *modal = new QSqlTableModel;
    modal->setTable("TB_PATIENT_INFO_2");
    modal->select();
    while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
       modal->fetchMore();
    ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    ui->tableView->setSortingEnabled(true);
    //ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 se

    //connClose(); //DB연결 닫기
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

//신환 클릭할 경우 수행하는 멤버함수 정의 (모든 입력란 초기화)
void MainWindow::on_pushButton_newpatient_clicked()
{
    ui->lineEdit_pntuid->clear();
    ui->lineEdit_pntname->clear();
    ui->lineEdit_birthdate->clear();
    ui->textEdit_adrr->clear();
    ui->lineEdit_hpno->clear();
    ui->lineEdit_hometel->clear();
    ui->lineEdit_FirstVisitDate->clear();
    ui->lineEdit_LastVisitDate->clear();
    ui->lineEdit_age->clear();
    //로우 선택 되어 있는 것 선택 해제
    //ui->tableView->setModel(modal); // -> 이 모델을 tabel view에 set
    //ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    //ui->tableView->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    //ui->tableView->setSortingEnabled(true);


}

// 저장 클릭할 경우 수행하는 멤버함수 정의
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
}

// 삭제 클릭할 경우 수행하는 멤버함수 정의
void MainWindow::on_pushButton_delete_clicked()
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
    QSqlQuery qry; //어떤 column에 기반해서 삭제할 건지 쿼리문을 통해 설정 가능
    qry.prepare("DELETE FROM TB_PATIENT_INFO_2 where pnt_uid='"+pntuid+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("삭제"),tr("정상적으로 삭제가 완료되었습니다.")); // 정상적으로 삭제되었다는 알림창 띄우기
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

}

// 환자 목록 클릭시 입력란에 해당 환자정보 띄우기 위한 멤버함수 정의
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
    QString Qcurrentdate = QString::number(t->tm_year + 1900) + '0'+ QString::number(t->tm_mon + 1) + QString::number(t->tm_mday);
    //qDebug() << "Qcurrentdate : "<< Qcurrentdate;
    int icurrentdate = Qcurrentdate.toInt();


    //~~~~~~~~~~~~~~~~~~~

    QString val=ui->tableView->model()->data(index).toString(); // tableview에서 user가 선택한 인덱스를 취해서 이 인덱스를 변환하고 값을 취해서 Qstring 변수로 옮김
    connOpen();
    QSqlQuery qry;
    qDebug() << "value : "<< val;
    //여기서 val 값은 해당 row의 pnt_uid값이어야 한다.
    qry.prepare("SELECT * FROM TB_PATIENT_INFO_2 where pnt_uid='"+val+"' or pnt_name='"+val+"' or birth_date='"+val+"'or home_addr='"+val+"' or hp_no='"+val+"' or home_tel='"+val+"' or registration_date='"+val+"' or lastvisit_date='"+val+"'"); //
    if(qry.exec())
    {
        while(qry.next()) //위에 쿼리문이 실행될 경우 어떤 값이든지 값을 얻어 LineEdit에 넘겨줌
        {
            ui->lineEdit_pntuid->setText(qry.value(0).toString());
            ui->lineEdit_pntname->setText(qry.value(1).toString());
            ui->lineEdit_birthdate->setText(qry.value(2).toString());
            ui->textEdit_adrr->setPlainText(qry.value(3).toString());
            ui->lineEdit_hpno->setText(qry.value(4).toString());
            ui->lineEdit_hometel->setText(qry.value(5).toString());
            ui->lineEdit_FirstVisitDate->setText(qry.value(6).toString());
            ui->lineEdit_LastVisitDate->setText(qry.value(7).toString());
            //birth_date 값을 부터 나이 계산하여 lineEdit_age에 출력
            QString Qbirthdate = qry.value(2).toString();
            Qbirthdate = Qbirthdate.remove('-');
            int ibirthdate = Qbirthdate.toInt();
            int iage = (icurrentdate - ibirthdate)/10000;
            QString Qage =  QVariant(iage).toString();
            ui->lineEdit_age->setText(Qage); //birth_date colmun value로 부터 계산된 나이 출력
        }
        connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

//search bar(검색창) Enter 입력시 수행하는 일 정의
void MainWindow::on_lineEdit_search_returnPressed()
{
    regxpattern = "";
    //enter가 입력되면 lineEdit_search에 입력되어 있는 값을 가져옴
      QString pattern;
      pattern = ui->lineEdit_search->text(); // lineEdit_search로 부터 가져온 값 input_value에 저장
    // 입력값이 저장된 patttern에 따라 filtering 하여 결과를 table에 출력
    //QLineEdit * lineEdit_Search = new QLineEdit;
    //lineEdit_Search->setPlaceholderText("search");
    regxpattern = pattern;
    //QSortFilterProxyModel * FilterModel = new QSortFilterProxyModel;
    FilterProxyModel *FilterModel = new FilterProxyModel;
    QSqlTableModel *sourceModel = new QSqlTableModel(this);
    FilterModel->setSourceModel(sourceModel);
    FilterModel->setFilterRegularExpression(QRegularExpression("0", QRegularExpression::CaseInsensitiveOption));
    FilterModel->setFilterKeyColumn(0);

    //QModelIndex index = sourceModel()->index(source_row,filterKeyColumn(),source_parent);

    connOpen();
    //QSqlTableModel *modal = new QSqlTableModel;
    sourceModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    sourceModel->setTable("TB_PATIENT_INFO_2");
    sourceModel->select();
    while (sourceModel->canFetchMore()) //256row limit 문제해결방안(FetchMore)
       sourceModel->fetchMore();

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //FilterModel->setDynamicSortFilter(true);
    //FilterModel->setSourceModel(modal);
    ui->tableView->setModel(FilterModel);
    //FilterModel->setFilterKeyColumn(0);
    //FilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    //lineEditsearch.setPlaceholderText("search filter");
    //QObject::connect(ui->lineEdit_search, &QLineEdit::textChanged,
    //                     &FilterModel, &FilterProxyModel::setFilter);


    //modal->select();
    //while (modal->canFetchMore()) //256row limit 문제해결방안(FetchMore)
    //   modal->fetchMore();

    QObject::connect(ui->lineEdit_search, &QLineEdit::textChanged,
                         FilterModel, &FilterProxyModel::setFilter);

    //connClose(); // 위 쿼리 성공적으로 실행됐으면 DB연결 닫기


    //ui->tableView->setModel(&filter)

}

