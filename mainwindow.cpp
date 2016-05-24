#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prtselectdialog.h"
#include "cupsutil.h"
#include "unixutil.h"
#include "server.h"
#include "upload.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //sql
    sqlHelper = SqlHelper::GetInstance();
    //printers
    loadPrinters();
    for (auto row : userPrinters) {
        ui->listWidget->addItem(row.getPrinterName());
    }
    //print logs
    QStringList header;
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    header << "ID" << "状态" << "用户名" << "打印机" << "文件名" << "标题" << "打印选项" << "份数" << "提交时间" << "打印时间";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    loadPrintLogs();
    slot_updatePrintLog();
    //timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
    timer->start(5000);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::loadPrintLogs() {
    printLogs = sqlHelper->getPrintLogByUserName(UnixUtil::getUserName());
}

void MainWindow::loadPrinters() {
    userPrinters = sqlHelper->getUserPrinterByUserName(UnixUtil::getUserName());
}


void MainWindow::slot_updatePrintLog() {
    int sz = printLogs.size();
    ui->tableWidget->clearContents();
    for (int i = 0;i < sz;i++) {
        QTableWidgetItem * item;
        item = new QTableWidgetItem(QString::number(printLogs[i].getId(), 10));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, item);
        QString strStatus;
        int status = printLogs[i].getStatus();
        switch (status) {
        case 0:
            strStatus = "新提交";
            break;
        case 1:
            strStatus = "通过";
            break;
        case 2:
            strStatus = "回绝";
            break;
        case 3:
            strStatus = "打印完成";
            break;
        default:
            strStatus = "打印失败";
        }
        item = new QTableWidgetItem(strStatus);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(printLogs[i].getUserName());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(printLogs[i].getPrinterName());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(printLogs[i].getFilePath());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 4, item);
        item = new QTableWidgetItem(printLogs[i].getTitle());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 5, item);
        item = new QTableWidgetItem(printLogs[i].getOptions());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 6, item);
        item = new QTableWidgetItem(QString::number(printLogs[i].getCopies(), 10));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 7, item);
        item = new QTableWidgetItem(printLogs[i].getSubmitTime().toString("yyyy-MM-dd hh:mm:ss"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 8, item);
        item = new QTableWidgetItem(printLogs[i].getPrintTime().toString("yyyy-MM-dd hh:mm:ss"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 9, item);
    }
    ui->tableWidget->show();
}

QString MainWindow::slot_uploadPDF(QString filename) {
    Upload *upload = Upload::GetInstance();
    return upload->upload(filename);
}

QString MainWindow::slot_getPrinterName(QString msg) {
    PrtSelectDialog *dialog = new PrtSelectDialog();
    dialog->setWindowTitle("select a printer");
    dialog->exec();
    QString prt_name = dialog->getPtrName();
    delete dialog;
    return prt_name;
}

void MainWindow::slot_timeout() {
    loadPrintLogs();
    for (auto printLog : printLogs)
        if (printLog.getStatus() == 1) {
            if (printJob(printLog)) {
                printLog.setStatus(3);
            } else {
                printLog.setStatus(4);
            }
            sqlHelper->updatePrintLog(printLog);
        }
    slot_updatePrintLog();
}

bool MainWindow::printJob(PrintLog &printLog) {
    QString printerName = printLog.getPrinterName();
    QString fileName = printLog.getFilePath();
    QString title = printLog.getTitle();
    QString str_options = printLog.getOptions();
    cups_option_t *options;
    int num_options = CupsUtil::parseOptions(str_options.toStdString().c_str(), &options);
    int job_id = CupsUtil::printFile(printerName.toStdString().c_str(),
                                     fileName.toStdString().c_str(),
                                     title.toStdString().c_str(),
                                     num_options, options);
    CupsUtil::freeOptions(num_options, options);
    printLog.setPrintTime(QDateTime::currentDateTime());
    return (job_id != 0);
}
/*
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
    //int job_id = CupsUtil::printFile("Brother_HL-1208_Printer:4", "/home/cww/Desktop/test2", "my_title", 0, NULL);
    //qDebug() << job_id;
}
*/
