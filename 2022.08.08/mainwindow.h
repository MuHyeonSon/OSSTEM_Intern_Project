#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDebug>
#include <QtSql/QSqlQuery>

#include <QSqlDatabase>

#include <QSqlQueryModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//---( https://dragonchan.tistory.com/16 )
private slots:
    void AddValues(int id, QString first, QString last, QString bd, double weight);
//---
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
