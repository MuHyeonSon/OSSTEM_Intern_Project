#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "secdialog.h" //qt 튜토리얼5

#include <QMainWindow>
#include <QString>

#include <QMainWindow> //QMainWindow 헤더 include
#include <QDebug> // 디버깅을 위한 헤더
#include <QtSql/QSqlQuery> // QSqlQuery class는 SQL문을 실행하고 manipulating하는 방법을 제공
#include <QSqlDatabase>
//#include <QSqlQueryModel>
//#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } //Ui라는 namespace (코드작성할 때 사용)
QT_END_NAMESPACE

class MainWindow : public QMainWindow //MainWindow class 정의
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    SecDialog *secdialog; //객체생성후 그것을 포인터객체에 주고 heap 메모리에서 사용
};
#endif // MAINWINDOW_H
