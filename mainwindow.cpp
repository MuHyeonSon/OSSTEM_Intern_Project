#include "mainwindow.h"     // mainwindow.h 메인 윈도우 헤더파일 include
#include "ui_mainwindow.h" //??

MainWindow::MainWindow(QWidget *parent) // constructor(생성자)
    : QMainWindow(parent) //
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this); //
}

MainWindow::~MainWindow() //
{
    delete ui; //
}



/*

#include "mainwindow.h"     // mainwindow.h 메인 윈도우 헤더파일 include
#include "ui_mainwindow.h" //??

MainWindow::MainWindow(QWidget *parent) // constructor(생성자)
    : QMainWindow(parent) //
    , ui(new Ui::MainWindow) //
{
    ui->setupUi(this); //

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./PATIENT_INFO.db"); // 상대경로(Mainwindow소스파일과 db파일이 같은 경로에 존재해야됨)

    if (!mydb.open())
        ui -> label -> setText("Failed to open the database (데이테베이스를 여는데 실패하였습니다.");
    else
        ui -> label -> setText("Connected!! (연결됨!!)");
}
MainWindow::~MainWindow() //
{
    delete ui; //
}

*/
