#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./PATIENT_INFO.db"); //영상에서는 확장자 sqlite
    /*
    if(!db.open())
    {
        qDebug() << "problem opening database";
    }
    QString query = "CREATE TABLE tesstable ("
                    "ID integer,"
                    "FirstName VARCHAR(20),"
                    "LastName VARCHAR(20),"
                    "Birthdate DATETIME,"
                    "Weight double)";
    QSqlQuery qry;

    if(!qry.exec(query))
    {
        qDebug() << "error creating table";
    }



    AddValues(1, "Bob", "Fredrickson", "01-23-1992", 156.5);

    db.close();

    qDebug() << "end";
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    db.open();
    QSqlQuery q;
    QString data = "";
    q.exec("select * FROM TB_PATIENT_INFO");

    while(q.next()) {
        data += q.value(0).toString() + " =:= ";
        data += q.value(1).toString() + "\n";
    }

    // let's just add our string as text pf textfeild
    ui->textEdit->setText(data);

    q.clear();
    db.close();


}
