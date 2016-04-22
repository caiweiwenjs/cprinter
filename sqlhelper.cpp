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
    return ret;
}

