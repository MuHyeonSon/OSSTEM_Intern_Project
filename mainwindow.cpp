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

