#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QVector>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>


class SqlHelper
{
private:
    static SqlHelper *m_pInstance;
    SqlHelper(QString dbType, QString dbName,
                     QString hostName, QString userName, QString password);

    QSqlDatabase m_pDb;
public:
    static SqlHelper *GetInstance();
    QVector<QVector<QVariant> > exec(const QString &query, int fieldNumber);
    bool exec(const QString &query);
};

#endif // SQLHELPER_H
