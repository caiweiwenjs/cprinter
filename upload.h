#ifndef UPLOAD_H
#define UPLOAD_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QProgressDialog>
#include <unixutil.h>

class Upload : public QObject
{
    Q_OBJECT

private:
    explicit Upload(QObject *parent = 0);
    QNetworkAccessManager *uploadManager;
    QNetworkReply *reply;
    //static QProgressDialog *progressDialog;
    char *m_buf;
    const QString DIR = "/var/spool/cups-pdf/" + UnixUtil::getUserName() + "/";
    //const QString DIR = "/home/cww/";
    const QString URL = "http://localhost/upload.php";
private slots:
    void replyFinish();
    void uploadError(QNetworkReply::NetworkError errorCode);
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
public:
    static Upload *GetInstance();

    QString upload(QString filename);
};

#endif // UPLOAD_H
