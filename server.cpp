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
        QString prt_name = emit signal_getPrinterName(str);
        if (prt_name == "") {//discard selecting printer
            continue ;
        }
        us->sendMsg(fd, prt_name.toStdString().c_str(), prt_name.length() + 1);
        us->recvMsg(fd, rbuf);
        JobMsg jobMsg(rbuf);
        QString filename = emit signal_uploadPDF(QString(jobMsg.title) + ".pdf");
        sqlHelper->addPrintLog(PrintLog(-1, 0, UnixUtil::getUserName(), prt_name, filename,
                                        QString(jobMsg.title), QString(jobMsg.options), QString(jobMsg.copies).toInt(),
                                        QDateTime::currentDateTime(),
                                        QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss")));
        emit signal_updatePrintLog();
    }
}

