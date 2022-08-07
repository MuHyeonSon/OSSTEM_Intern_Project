#include "mainwindow.h" // mainwindow 헤더 incldue

#include <QApplication> // QApplication 헤더 include
                        // QApplication class는 GUI application의 control flow와 main setting들을 관리한다.


int main(int argc, char *argv[]) // argc argv 어플리케이션 터미널에서 실행할 때 argc: 인자 개수 argv : 인자 문자열
{

    QSqlDatabase db; //SQL데이터베이스 인스턴스 생성
    db=QSqlDatabase::addDatabase("QSQLITE"); // 데이터베이스 종류설정
    db.setDatabaseName("PATIENT_INFO.db"); // 데이터베이스 파일이름설정 (상대경로로하고, 나중에 ui로 구현시 사용자로부터 db불러올 때 절대경로 path로 불러오게 하기)
    bool isOpenDB = db.open(); // QSqlDatabase의 멤버함수로 파일 열기에 성공했으면 True반환, 성공x False 반환
    qDebug() << "isOpenDB : " << isOpenDB; // 파일열기 성공했는지 여부 출력

    qDebug() << QSqlDatabase::drivers(); // 현재 환경에 어떤 DB Libarary가 설치되어 있는지 확인
    qDebug() << "table 정보 : " << db;

    //QString queryStr; // 쿼리문을 전달할 변수
    //queryStr = QString("SELECT*FROM 'TB_PATIENT_INFO'"); // 쿼리문 저장
    //QSqlQuery query; // 데이터베이스에 전달할 쿼리 변수
    //query.prepare(queryStr); // 준비
    //query.exec(); // 실행
    //qDebug() << query.exec(); // 실행
    // DB에 있는 TB_PATIENT_INFO 전부 불러와서 ui에 띄우기

    QSqlQuery query;
    query.exec("SELECT resi_no FROM TB_PATIENT_INFO");
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@@@@";
    while (query.next()){
        QString resi_no = query.value(0).toString();
        qDebug() <<resi_no;
    }
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@@@@";
    db.close(); // 데이터를 모두 가져왔으면 데이터베이스 종료

    /*
    QString sql = "QSQLITE";
    QString dbName = "PATIENT_INFO.db";
    QSqlDatabase m_LocalDB;
        m_LocalDB = QSqlDatabase::addDatabase(sql,dbName);
        m_LocalDB.setDatabaseName("PATIENT_INFO.db");
        if(!m_LocalDB.open())
        {
            qDebug()<<"local Database Setting Open failed!";

            QSqlDatabase::removeDatabase("LocalDB");
        }
        QSqlQuery query; //
        query.exec("select resi_no from TB_PATIENT_INFO");
        //int fieldNo = query.record().indexof("resi_no");
        while (query.next())
        {
            QString resi_no = query.value(0).toString();
            //doSomething(resi_no);
            //qDebug() << query.value(0).toInt() << query.value(1).toString();
            qDebug() <<resi_no;
        }
        qDebug() <<"resi_no colmn 정보 불러오기!!";
        QString resi_no = query.value(0).toString();
        qDebug() <<resi_no;



    m_LocalDB.close(); // 데이터를 모두 가져왔으면 데이터베이스 종료
    */
    QApplication a(argc, argv); // QApplication 클래스의 객체 a 선언 (무슨 일을 하는지?)
    MainWindow w; // MainWindow의 객체 w 선언
    w.show(); // show the widget and its child widget (위젯과 자식 위젯을 보여줌)
    return a.exec(); // exec()는 QApplicaiton 클래스에서 제공하는 멤버함수로 이 어플리케이션을 실행하고 결과 값을 끝날 때 return 하라는 것
}
