#include "upload.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QMessageBox>


Upload *Upload::GetInstance() {
    static Upload upload;
    return &upload;
}

Upload::Upload(QObject *parent) :
    QObject(parent)
{
     uploadManager = new QNetworkAccessManager(this);
    //progressDialog = new QProgressDialog();
}

void Upload::replyFinish() {
    //progressDialog->close();
    //file->flush();
    //file->close();

    //QByteArray byteArray =  reply->readAll();
    //qDebug() << byteArray;
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    //qDebug() << "buffer size = " << reply->readBufferSize();
    if (reply->error()) {
        //qDebug() << "error";
        //file->remove();
        //QMessageBox::information(this, tr("HTTP"),
        //                         tr("Download failed: %1.")
        //                         .arg(reply->errorString()));
        //downloadButton->setEnabled(true);
    } else if (!redirectionTarget.isNull()) {
       // QUrl newUrl = url.resolved(redirectionTarget.toUrl());
       // if (QMessageBox::question(this, tr("HTTP"),
         //                         tr("Redirect to %1 ?").arg(newUrl.toString()),
        //                          QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            //url = newUrl;
         //   reply->deleteLater();
            //file->open(QIODevice::WriteOnly);
            //file->resize(0);
            //startRequest(url);
        //    return;
      //  }
    } else {
        //qDebug() << "success";
        //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        //downloadButton->setEnabled(true);
    }

    reply->deleteLater();
    reply = 0;
    delete m_buf;
    m_buf = nullptr;
    //delete file;
    //file = 0;
}

void Upload::uploadError(QNetworkReply::NetworkError errorCode) {
    //qDebug() << errorCode;
}

void Upload::onUploadProgress(qint64 bytesSent, qint64 bytesTotal) {
    //progressDialog->setMaximum(bytesTotal);
    //progressDialog->setValue(bytesSent);
    //qDebug() << "bytesSent:" << bytesSent << " bytesTotal:" << bytesTotal;
}

QString Upload::upload(QString filename) {
    m_buf = nullptr;

    //qDebug() << DIR + filename;
    QFile file(DIR + filename);
    //qDebug() << file.open(QIODevice::ReadOnly);
    int file_len = file.size();
    QDataStream in(&file);
    m_buf = new char[file_len];
    //qDebug() << in.readRawData(m_buf, file_len);
    file.close();

    //qDebug() << file_len;
    QString rfn = UnixUtil::getUserName() + QString::number(QDateTime::currentMSecsSinceEpoch()) +".pdf";
    //qDebug() << URL + "?filename=" + rfn;
    QNetworkRequest request(QUrl(URL + "?filename=" + rfn));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    QByteArray arr = QByteArray(m_buf, file_len);
    reply = uploadManager->post(request, arr);
    //progressDialog->show();
    connect(reply, SIGNAL(finished()),
            this, SLOT(replyFinish()));
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
    //        this, SLOT(uploadError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(onUploadProgress(qint64,qint64)));
    return rfn;
}

