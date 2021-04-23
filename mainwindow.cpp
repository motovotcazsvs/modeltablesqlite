#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>

void printSqlite();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/QtProject/qmlsqlite/MedicalMeasurements.db3");//для windows
    db.open();

    // объявляем модель данных
     model = new QSqlTableModel(this);
     // указываем таблицу из БД
     model->setTable("TABLEMEDICALMEASUREMENTS"); // Имя таблицы базы данных


      model->setFilter(" DATEMONTH >= 1"); // Условие WHERE.
      model->setSort(0, Qt::DescendingOrder); // Сортировка по убыванию id.
      model->select(); // Получить данные.

     //if(model->select())
     //{
         // передаем данные из модели в tableView

         ui->tableView->setModel(model);
         //ui->tableView->hideColumn(0); // don't show the ID
         // устанавливаем высоту строки по тексту
         ui->tableView->resizeRowsToContents();
         // шапка для первой колонки
         //model->setHeaderData(0, Qt::Horizontal, tr("ID"));
         // шапка для второй колонки
         //model->setHeaderData(1, Qt::Horizontal, tr("имя"));
         // передача управления элементу tableView
         ui->tableView->setSortingEnabled(true);
         ui->tableView->setFocus();
         //ui->tableView->scrollToBottom();

    // }




}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void printSqlite()
{
    QSqlQuery query;
    query.exec("SELECT NUMBERPERDAY, PROBENUMBER, DATEYEAR, DATEMONTH, DATEDAY, TIMEHOUR, TIMEMINUTE, GL, LC, BARCODE FROM TABLEMEDICALMEASUREMENTS");
    while(query.next()){
        //QString id = query.value(0).toString();
        QString number_per_day = query.value(1).toString();
        QString probe_number = query.value(2).toString();
        QString date_year = query.value(3).toString();
        QString date_month = query.value(4).toString();
        QString date_day = query.value(5).toString();
        QString time_hour = query.value(6).toString();
        QString time_minute = query.value(7).toString();
        QString gl = query.value(8).toString();
        QString lc = query.value(9).toString();
        QString bar_code = query.value(10).toString();
        qDebug() << number_per_day << " " << probe_number << " " << date_year << " " << date_month << " "
                 << date_day << " " << time_hour << " " << time_minute << " " << gl << " " << lc << " " << bar_code;
    }
}



