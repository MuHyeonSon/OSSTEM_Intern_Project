#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE","DB");
DB.setDatabaseName("./PATIENT_INFO.db");

if(!DB.open())
{
    QMessageBox::critical(this,"Error","DB Open Failed")
    QSqlDatabase::removeDatabase("DB");
    return;
}

QSqlQueryModel * Model = new QSqlQueryModel; //Heap 동적할당
Model->setQuery("SELECT*FROM TB_PATIENT_INFO",DB);
Model->setHeaderData(0,Qt::Horizontal,tr("UserID")); //컬럼1 이름
Model->setHeaderData(1,Qt::Horizontal,tr("Password")) //컬럼2 이름

ui->tableView->setModel(Model);
ui->tableView->show();
*/
