#include "sqlhelper.h"

SqlHelper::SqlHelper(QString dbType, QString dbName,
                     QString hostName, QString userName, QString password) {

    m_pDb = QSqlDatabase::addDatabase(dbType);
    m_pDb.setDatabaseName(dbName);
    m_pDb.setHostName(hostName);
    m_pDb.setUserName(userName);
    m_pDb.setPassword(password);
    if (!m_pDb.open()) {
        qDebug() << m_pDb.lastError();
        //delete m_pDb;
    }
}

SqlHelper *SqlHelper::m_pInstance = nullptr;

SqlHelper *SqlHelper::GetInstance() {
    if (m_pInstance == nullptr)
        m_pInstance = new SqlHelper("QMYSQL", "pcms", "localhost", "cww", "caiweiwenjs");
    return m_pInstance;
}

QVector<QVector<QVariant> > SqlHelper::exec(const QString &sql, int fieldNumber) {
    QSqlQuery query;
    bool ret = query.exec(sql);
    QVector<QVector<QVariant> > result;
    if (!ret) {
        qDebug() << query.lastError();
        return result;
    }
    if (query.record().count() != fieldNumber) {
        qDebug() << "Wrong fieldNumber!";
        return result;
    }
    while (query.next()) {
        QVector<QVariant> row;
        for (int i = 0;i < fieldNumber;i++)
            row.push_back(query.value(i));
        result.push_back(row);
    }
    return result;
}

bool SqlHelper::exec(const QString &sql) {
    QSqlQuery query;
    bool ret = query.exec(sql);
    if (!ret) {
        qDebug() << query.lastError();
    }

    return (ret && query.numRowsAffected());
}

QVector<PrintLog> SqlHelper::getPrintLogByUserName(QString userName) {
    QString sql = "select id, status, user_name, printer_name, file_path, title, options, copies, submit_time, print_time from tab_print_log where user_name = '" + userName + "';";
    QVector<PrintLog> res;
    QVector<QVector<QVariant> > table = exec(sql, 10);
    for (auto i : table) {
        int id = i[0].toInt();
        int status = i[1].toInt();
        QString userName = i[2].toString();
        QString printerName = i[3].toString();
        QString filePath = i[4].toString();
        QString title = i[5].toString();
        QString options = i[6].toString();
        int copies  = i[7].toInt();
        QDateTime submitTime = i[8].toDateTime();
        QDateTime printTime = i[9].toDateTime();
        res.push_back(PrintLog(id, status, userName, printerName, filePath, title, options, copies, submitTime, printTime));
    }
    return res;
}

QVector<UserPrinter> SqlHelper::getUserPrinterByUserName(QString userName) {
    QString sql = "select user_name, printer_name from tab_user_printer where user_name = '"+userName+"';";
    QVector<UserPrinter> res;
    QVector<QVector<QVariant> > table = exec(sql, 2);

    for (auto i : table) {
        QString userName = i[0].toString();
        QString printerName = i[1].toString();
        res.push_back(UserPrinter(userName, printerName));
    }

    return res;
}

bool SqlHelper::addPrintLog(const PrintLog &printLog) {
    QString fmt = "insert into tab_print_log(status, user_name, printer_name, file_path, title, options, copies, submit_time, print_time) values(%1, '%2', '%3', '%4', '%5', '%6', %7, '%8', '%9');";
    QString sql = fmt.arg(printLog.getStatus()).
                          arg(printLog.getUserName()).
                          arg(printLog.getPrinterName()).
                          arg(printLog.getFilePath()).
                          arg(printLog.getTitle()).
                          arg(printLog.getOptions()).
                          arg(printLog.getCopies()).
                          arg(printLog.getSubmitTime().toString("yyyy-MM-dd hh:mm:ss")).
                          arg(printLog.getPrintTime().toString("yyyy-MM-dd hh:mm:ss"));
    return exec(sql);
}

bool SqlHelper::updatePrintLog(const PrintLog &printLog) {
    QString fmt = "update tab_print_log set status = %1, print_time = '%2' where id = '%3';";
    QString sql = fmt.arg(printLog.getStatus()).
                        arg(printLog.getPrintTime().toString("yyyy-MM-dd hh:mm:ss")).
                        arg(printLog.getId());
    return exec(sql);
}

