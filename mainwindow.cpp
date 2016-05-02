#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QListView>
#include <QDialog>
#include <QVector>
#include <QString>
#include "sqlhelper.h"
#include "prtselectdialog.h"
#include "cupsutil.h"
#include "unixutil.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    QVector<UserPrinter> userPrinters = sqlHelper->getUserPrinterByUserName(UnixUtil::getUserName());
    for (auto row : userPrinters) {
        ui->listWidget->addItem(row.getPrinterName());
    }
    //ui->tableWidget->setWindowTitle("QTableWidget & Item");
    //ui->tableWidget->resize(350, 200);  //设置表格
    slot_updatePrintLog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_updatePrintLog() {
    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    QVector<PrintLog> printLogs = sqlHelper->getPrintLogByUserName(UnixUtil::getUserName());
    QStringList header;
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    header << "id" << "status" << "userName" << "printerName" << "fileName" << "title" << "options" << "copies" << "submitTime" << "printTime";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int sz = printLogs.size();
    for (int i = 0;i < sz;i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(printLogs[i].getId(), 10)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(printLogs[i].getStatus(), 10)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(printLogs[i].getUserName()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(printLogs[i].getPrinterName()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(printLogs[i].getFileName()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(printLogs[i].getTitle()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(printLogs[i].getOptions()));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(printLogs[i].getCopies(), 10)));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(printLogs[i].getSubmitTime().toString("yyyy-MM-dd hh:mm:ss")));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(printLogs[i].getPrintTime().toString("yyyy-MM-dd hh:mm:ss")));
    }
    ui->tableWidget->show();
}

QString MainWindow::slot_getPrinterName(QString msg) {
    PrtSelectDialog *dialog = new PrtSelectDialog();
    dialog->setWindowTitle("select a printer");
    dialog->exec();
    QString prt_name = dialog->getPtrName();
    delete dialog;
    return prt_name;
}

void MainWindow::on_pushButton_clicked()
{
    QList <QTableWidgetItem *> ql = ui->tableWidget->selectedItems();
    int row = -1;
    if (ql.size() > 0)
        row = ql[0]->row();
    if (row != -1) {
        QString printerName = ui->tableWidget->item(row, 3)->text();
        QString fileName = ui->tableWidget->item(row, 4)->text();
        QString title = ui->tableWidget->item(row, 5)->text();
        QString str_options = ui->tableWidget->item(row, 6)->text();
        //qDebug() << str_options;
        cups_option_t *options;
        int num_options = CupsUtil::parseOptions(str_options.toStdString().c_str(), &options);
        //qDebug() << num_options;
        int job_id = CupsUtil::printFile(printerName.toStdString().c_str(),
                                         fileName.toStdString().c_str(),
                                         title.toStdString().c_str(),
                                         num_options, options);
        CupsUtil::freeOptions(num_options, options);
    } else {
        //select a row
    }
    //qDebug() << row;
    /*
    QDialog *dialog = new QDialog();
    for (auto i : ql) {
        dialog->setWindowTitle(i->text());
        dialog->show();
    }*/
    //int job_id = CupsUtil::printFile("Brother_HL-1208_Printer:4", "/home/cww/Desktop/test2", "my_title", 0, NULL);
    //qDebug() << job_id;
}
