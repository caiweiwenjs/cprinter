#include "server.h"
#include "unixsocket.h"
#include <QDialog>
#include "prtselectdialog.h"

Server::Server()
{

}

void Server::run() {
    UNIXSocket *us = new UNIXSocket();
    char rbuf[1024];
    forever {
        uid_t uid;
        int fd = us->waitClient(&uid);
        QString str = QString::number(uid);
        QString prt_name = emit send(str);
        us->sendMsg(fd, prt_name.toStdString().c_str(), prt_name.length() + 1);
        us->recvMsg(fd, rbuf);
        //QDialog *dialog = new QDialog();
        //dialog->setWindowTitle("prt_name = "+prt_name);
        //dialog->show();
        //qDebug("123", prt_name);
    }
}

