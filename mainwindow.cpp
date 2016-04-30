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
    QVector<PrintLog> printLogs = sqlHelper->getPrintLogByUserName(UnixUtil::getUserName());
    QVector<UserPrinter> userPrinters = sqlHelper->getUserPrinterByUserName(UnixUtil::getUserName());
    for (auto row : userPrinters) {
        ui->listWidget->addItem(row.getPrinterName());
    }
    //ui->tableWidget->setWindowTitle("QTableWidget & Item");
    //ui->tableWidget->resize(350, 200);  //设置表格
    QStringList header;
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(10);
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
    /*
    JobMsg jobMsg, jobMsg2;
    strcpy(jobMsg.title, "title1");
    strcpy(jobMsg.options, "options1");
    strcpy(jobMsg.copies, "copies1");
    char buf[1024];
    uint32_t len = jobMsg.encode(buf);
    jobMsg2.decode(buf);
    qDebug() << len;
    for (int i = 0;i < len;i++) {
        qDebug() << (int)buf[i];
    }
    qDebug() << jobMsg2.title;
    qDebug() << jobMsg2.options;
    qDebug() << jobMsg2.copies;
    */
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
    int job_id = CupsUtil::printFile("Brother_HL-1208_Printer:4", "/home/cww/Desktop/test2", "my_title", 0, NULL);
    //qDebug() << job_id;
}
