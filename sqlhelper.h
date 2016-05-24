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
    bool addPrintLog(const PrintLog &printLog);
    bool updatePrintLog(const PrintLog &printLog); //update status and print time only
};

//table print_log
class PrintLog {
private:
    int id;
    int status;
    QString userName;
    QString printerName;
    QString filePath;
    QString title;
    QString options;
    int copies;
    QDateTime submitTime;
    QDateTime printTime;
public:
    explicit PrintLog() {}
    explicit PrintLog(int _id, int _status, QString _userName, QString _printerName, QString _filePath, QString _title, QString _options,
                        int _copies, QDateTime _submitTime, QDateTime _printTime) :
        id(_id),
        status(_status),
        userName(_userName),
        printerName(_printerName),
        filePath(_filePath),
        title(_title),
        options(_options),
        copies(_copies),
        submitTime(_submitTime),
        printTime(_printTime) {}

    int getId() { return id; }
    int getId() const { return id; }
    int getStatus() { return status; }
    int getStatus() const { return status; }
    QString getUserName() { return userName; }
    QString getUserName() const { return userName; }
    QString getPrinterName() { return printerName; }
    QString getPrinterName() const { return printerName; }
    QString getFilePath() { return filePath; }
    QString getFilePath() const { return filePath; }
    QString getTitle() { return title; }
    QString getTitle() const { return title; }
    QString getOptions() { return options; }
    QString getOptions() const { return options; }
    int getCopies() { return copies; }
    int getCopies() const { return copies; }
    QDateTime getSubmitTime() { return submitTime; }
    QDateTime getSubmitTime() const { return submitTime; }
    QDateTime getPrintTime() { return printTime; }
    QDateTime getPrintTime() const { return printTime; }

    void setId(int id) { this->id = id; }
    void setStatus(int status) { this->status = status; }
    void setUserName(QString userName) { this->userName = userName; }
    void setPrinterName(QString printerName) { this->printerName = printerName; }
    void setFilePath(QString filePath) { this->filePath = filePath; }
    void setTitle(QString title) { this->title = title; }
    void setOptions(QString options) { this->options = options; }
    void setCopies(int copies) { this->copies = copies; }
    void setSubmitTime(QDateTime submitTime) { this->submitTime = submitTime; }
    void setPrintTime(QDateTime printTime) { this->printTime = printTime; }

};

//table user_printer
class UserPrinter {
private:
    int id;
    QString userName;
    QString printerName;
public:
    explicit UserPrinter() {}
    explicit UserPrinter(QString _userName, QString _printerName) : userName(_userName), printerName(_printerName) {}

    int getId() { return id; }
    int getId() const { return id; }
    QString getUserName() { return userName; }
    QString getUserName() const { return userName; }
    QString getPrinterName() { return printerName;}
    QString getPrinterName() const { return printerName;}
    void setId(int id) { this->id = id; }
    void setUserName(QString userName) { this->userName = userName; }
    void serPrinterName(QString printerName) { this->printerName = printerName;}
};

#endif // SQLHELPER_H
