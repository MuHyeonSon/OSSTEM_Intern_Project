#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QString sql = "QSQLITE";
    QString dbName = "PATIENT_INFO.db";
           QSqlDatabase m_LocalDB;
           m_LocalDB = QSqlDatabase::addDatabase(sql,dbName);
           m_LocalDB.setDatabaseName("./PATIENT_INFO.db");
           if(!m_LocalDB.open())
           {
               qDebug()<<"local Database Setting Open failed!";
               //QSqlDatabase::removeDatabase("LocalDB");
           }

           if(m_LocalDB.isValid())
           {
               qDebug()<<"Database is valid";
           }
           else
           {
               qDebug()<<"Database is not valid";
           }
           QSqlQuery query(m_LocalDB); //
           //query.exec("select resi_no from 'TB_PATIENT_INFO'");
           //int fieldNo = query.record().indexof("resi_no");

           query.exec("create tabel realestate"
                      "(id integer primary key, "
                      "buildingname varchar primary key, "
                      "streetarea integer, "
                      "streetarea2 integer, "
                      "note varchar(300))");
           query.exec("select * from realestate");
           qDebug()<<"program";
           while (query.next())
           {
                qDebug() << query.value(0).toInt() << query.value(1).toInt() << query.value(2).toInt() << query.value(3).toInt();
           }

           qDebug()<<"program exit";



           while (query.next())
           {
               QString resi_no = query.value(0).toString();
               //doSomething(resi_no);
               //qDebug() << query.value(0).toInt() << query.value(1).toString();
               qDebug() <<resi_no;
           }
           //qDebug() <<"resi_no colmn 정보 불러오기!!";
           //QString resi_no = query.value(0).toString();
           //qDebug() <<resi_no;


           //QSqlQueryModel* modal = new QSqlQueryModel();
           //QSqlQuery *qry = new QSqlQuery(m_LocalDB);

           //qry->prepare("Select * FROM TB_PATIENT_INFO");
           //qry->exec();
           m_LocalDB.close(); // 데이터를 모두 가져왔으면 데이터베이스 종료
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //table view에  QSqlModel Sqlite 띄우는 기능 찾아볼 것
}
