#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QListView>
#include <QDialog>
#include <QVector>
#include <QString>
#include <sqlhelper.h>
#include "prtselectdialog.h"
#include "cupsutil.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->listWidget->addItem("Cww");
    //ui->listWidget->addItem("Cww2");
    /*
    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    QVector<QVector<QVariant> > res = sqlHelper->exec("select user_name, printer_name from user_printer;", 2);
    */
    QVector<QString> dests = cupsutil::getDests();
    qDebug() << dests.size();
    for (auto i : dests) {
        ui->listWidget->addItem(i);
        //ui->listWidget->addItem(i[1].toString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::test_server(QString msg) {

    PrtSelectDialog *dialog = new PrtSelectDialog();
    dialog->setWindowTitle("select a printer");
    dialog->exec();
    QString prt_name = dialog->getPtrName();
    delete dialog;
    return prt_name;
}

void MainWindow::on_pushButton_clicked()
{
    QList <QListWidgetItem *> ql = ui->listWidget->selectedItems();
    QDialog *dialog = new QDialog();
    for (auto i : ql) {
        dialog->setWindowTitle(i->text());
        dialog->show();
    }
    int job_id = cupsutil::printFile("Brother_HL-1208_Printer:4", "/home/cww/Desktop/test2", "my_title", 0, NULL);
    qDebug() << job_id;
}
