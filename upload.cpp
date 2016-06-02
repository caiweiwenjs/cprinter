#include "upload.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QMessageBox>
#include <QThread>
#include <QCoreApplication>


Upload *Upload::GetInstance(QWidget *parent) {
    static Upload upload(parent);
    return &upload;
}

Upload::Upload(QWidget *parent) :
    QWidget(parent)
{
    uploadManager = new QNetworkAccessManager(this);
    //progressDialog = new QProgressDialog("upload file", "cancel", 0, 100, parent);
    //progressDialog->setWindowModality(Qt::WindowModal);
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
    //waiting for cups-pdf generate pdf file
    int loop_cnt = 1000;
    QProgressDialog progress("正在生成pdf文件...", "停止", 0, loop_cnt, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    bool isCanceled = false;
    for (int i = 0; i < loop_cnt; i++) {
         progress.setValue(i);
         if (progress.wasCanceled()) {
             isCanceled = true;
             break;
         }
        //sleep
         QTime t;
         t.start();
         while(t.elapsed() < 2)
             QCoreApplication::processEvents();
     }
     progress.setValue(loop_cnt);
    if (isCanceled)
        return QString();

    m_buf = nullptr;
    QFile file(Common::getDir() + filename);
    file.open(QIODevice::ReadOnly);
    int file_len = file.size();
    QDataStream in(&file);
    m_buf = new char[file_len];
    in.readRawData(m_buf, file_len);
    file.close();

    //qDebug() << file_len;
    QString rfn = UnixUtil::getUserName() + QString::number(QDateTime::currentMSecsSinceEpoch()) + Common::getExt();
    //qDebug() << URL + "?filename=" + rfn;
    QNetworkRequest request(QUrl(Common::getUrl() + "?filename=" + rfn));
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

