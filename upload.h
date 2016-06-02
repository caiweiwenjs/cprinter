#ifndef UPLOAD_H
#define UPLOAD_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QProgressDialog>
#include "common.h"

class Upload : public QWidget
{
    Q_OBJECT

private:
    explicit Upload(QWidget *parent = 0);
    QNetworkAccessManager *uploadManager;
    QNetworkReply *reply;
    QProgressDialog *progressDialog;
    char *m_buf;
    //const QString DIR = "/var/spool/cups-pdf/" + UnixUtil::getUserName() + "/";
    //const QString DIR = "/home/cww/";
    //const QString URL = "http://localhost/upload.php";
private slots:
    void replyFinish();
    void uploadError(QNetworkReply::NetworkError errorCode);
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
public:
    static Upload *GetInstance(QWidget *parent);

    QString upload(QString filename);
};

#endif // UPLOAD_H
