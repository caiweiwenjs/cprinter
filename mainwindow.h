#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QListView>
#include <QVector>
#include <QTableWidgetItem>
#include <QString>
#include "sqlhelper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();
    QString slot_getPrinterName(QString msg);
    QString slot_uploadPDF(QString filename);
    void slot_updatePrintLog();
    void slot_timeout();
private:
    void loadPrintLogs();
    void loadPrinters();
    bool printJob(PrintLog &printLog);
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    SqlHelper *sqlHelper;
    QVector<PrintLog> printLogs;
    QVector<UserPrinter> userPrinters;
};

#endif // MAINWINDOW_H
