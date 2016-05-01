#include "server.h"
#include "unixsocket.h"
#include <QDialog>
#include "prtselectdialog.h"
#include "protocol.h"
#include "sqlhelper.h"
#include "unixutil.h"
#include <QDateTime>

Server::Server()
{

}

void Server::run() {
    UNIXSocket *us = new UNIXSocket();
    char rbuf[JobMsg::MAXL];
    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    forever {
        uid_t uid;
        int fd = us->waitClient(&uid);
        QString str = QString::number(uid);
        QString prt_name = emit send(str);
        us->sendMsg(fd, prt_name.toStdString().c_str(), prt_name.length() + 1);
        us->recvMsg(fd, rbuf);
        JobMsg jobMsg(rbuf);
        sqlHelper->addPrintLog(PrintLog(-1, 0, UnixUtil::getUserName(), prt_name, "/var/spool/cups-pdf/" + UnixUtil::getUserName() + "/" + QString(jobMsg.title) + ".pdf",
                                        QString(jobMsg.title), QString(jobMsg.options), QString(jobMsg.copies).toInt(),
                                        QDateTime::currentDateTime(),
                                        QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss")));
        //qDebug("%s\n", jobMsg.title);
        //qDebug("%s\n", jobMsg.options);
        //qDebug("%s\n", jobMsg.copies);
        //QDialog *dialog = new QDialog();
        //dialog->setWindowTitle("prt_name = "+prt_name);
        //dialog->show();
        //qDebug("123", prt_name);
    }
}

