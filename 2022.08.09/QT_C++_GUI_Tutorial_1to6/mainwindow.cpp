#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); //UI시작할 때 setup
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int))
            ,ui->progressBar,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui; //프로그램 닫을 때 UI삭제
}


void MainWindow::on_pushButton_clicked() //OK
{
    ui->label->setText("Hi");
}


void MainWindow::on_pushButton_2_clicked() //Show Message
{
    QMessageBox::critical(this,tr("THE TITLE"),tr("This is a message"));//매개변수3개
}


void MainWindow::on_pushButton_3_clicked()
{
    //SecDialog secdialog; // secdilog class의 object 생성
    //secdialog.setModal(true);
    //secdialog.exec(); // 위 3 line과 두번째 dialog나 window열기위한
                        // 같은 접근은 model approch 라고 함
    secdialog = new SecDialog(this);
    secdialog->show();
}

