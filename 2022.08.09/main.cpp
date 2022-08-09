
#include "mainwindow.h"

#include "mainwindow.ui"

#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE","DB");
    DB.setDatabaseName("./PATIENT_INFO.db");

    if(!DB.open())
    {
        //QMessageBox::critical(this,"Error","DB Open Failed")
        qDebug() << "DB Open Failed";
        QSqlDatabase::removeDatabase("DB");
        return 0;
    }

    QSqlQueryModel * Model = new QSqlQueryModel; //Heap 동적할당
    Model->setQuery("SELECT*FROM TB_PATIENT_INFO",DB);
    Model->setHeaderData(0,Qt::Horizontal,QObject::tr("UserID")); //컬럼1 이름
    Model->setHeaderData(1,Qt::Horizontal,QObject::tr("Password")); //컬럼2 이름

    ui->tableView->setModel(Model);
    ui->tableView->show();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
