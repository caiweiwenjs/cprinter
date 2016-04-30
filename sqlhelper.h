#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QVector>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QDateTime>

class PrintLog;
class UserPrinter;

class SqlHelper
{
private:
    static SqlHelper *m_pInstance;
    SqlHelper(QString dbType, QString dbName,
                     QString hostName, QString userName, QString password);

    QSqlDatabase m_pDb;
public:
    static SqlHelper *GetInstance();
    //raw API
    QVector<QVector<QVariant> > exec(const QString &query, int fieldNumber);
    bool exec(const QString &query);
    //table API
    QVector<PrintLog> getPrintLogByUserName(QString userName);
    QVector<UserPrinter> getUserPrinterByUserName(QString userName);
};

//table print_log
class PrintLog {
private:
    int id;
    int status;
    QString userName;
    QString printerName;
    QString fileName;
    QString title;
    QString options;
    int copies;
    QDateTime submitTime;
    QDateTime printTime;
public:
    explicit PrintLog() {}
    explicit PrintLog(int _id, int _status, QString _userName, QString _printerName, QString _fileName, QString _title, QString _options,
                        int _copies, QDateTime _submitTime, QDateTime _printTime) :
        id(_id),
        status(_status),
        userName(_userName),
        printerName(_printerName),
        fileName(_fileName),
        title(_title),
        options(_options),
        copies(_copies),
        submitTime(_submitTime),
        printTime(_printTime) {}

    int getId() { return id; }
    int getStatus() { return status; }
    QString getUserName() { return userName; }
    QString getPrinterName() { return printerName; }
    QString getFileName() { return fileName; }
    QString getTitle() { return title; }
    QString getOptions() { return options; }
    int getCopies() { return copies; }
    QDateTime getSubmitTime() { return submitTime; }
    QDateTime getPrintTime() { return printTime; }
    void setId(int id) { this->id = id; }
    void setStatus(int status) { this->status = status; }
    void setUserName(QString userName) { this->userName = userName; }
    void setPrinterName(QString printerName) { this->printerName = printerName; }
    void setFileName(QString fileName) { this->fileName = fileName; }
    void setTitle(QString title) { this->title = title; }
    void setOptions(QString options) { this->options = options; }
    void setCopies(int copies) { this->copies = copies; }
    void setSubmitTime(QDateTime submitTime) { this->submitTime = submitTime; }
    void setPrintTime(QDateTime printTime) { this->printTime = printTime; }

};

//table user_printer
class UserPrinter {
private:
    QString userName;
    QString printerName;
public:
    explicit UserPrinter() {}
    explicit UserPrinter(QString _userName, QString _printerName) : userName(_userName), printerName(_printerName) {}

    QString getUserName() { return userName; }
    QString getPrinterName() { return printerName;}
    void setUserName(QString userName) { this->userName = userName; }
    void serPrinterName(QString printerName) { this->printerName = printerName;}
};

#endif // SQLHELPER_H
