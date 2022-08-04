#include "mainwindow.h" // mainwindow 헤더 incldue

#include <QApplication> // QApplication 헤더 include
                        // QApplication class는 GUI application의 control flow와 main setting들을 관리한다.


int main(int argc, char *argv[]) // argc argv 어플리케이션 터미널에서 실행할 때 argc: 인자 개수 argv : 인자 문자열
{
    QSqlDatabase db; //SQL데이터베이스 인스턴스 생성
    db = QSqlDatabase::addDatabase("QSQLITE"); // 데이터베이스 종류설정
    db.setDatabaseName("PATIENT_INFO.db"); // 데이터베이스 파일이름설정 (상대경로로)
    bool isOpenDB = db.open(); // QSqlDatabase의 멤버함수로 파일 열기에 성공했으면 True반환, 성공x False 반환
    qDebug() << "isOpenDB : " << isOpenDB; // 파일열기 성공했는지 여부 출력

    qDebug() << QSqlDatabase::drivers(); //현재 환경에 어떤 DB Libarary가 설치되어 있는지 확인
    qDebug() << "table 내용 : " << db;





    QApplication a(argc, argv); // QApplication 클래스의 객체 a 선언 (무슨 일을 하는지?)
    MainWindow w; // MainWindow의 객체 w 선언
    w.show(); // show the widget and its child widget (위젯과 자식 위젯을 보여줌)
    return a.exec(); // exec()는 QApplicaiton 클래스에서 제공하는 멤버함수로 이 어플리케이션을 실행하고 결과 값을 끝날 때 return 하라는 것
}
