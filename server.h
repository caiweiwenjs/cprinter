#ifndef SERVER_H
#define SERVER_H

#include <QThread>

class Server : public QThread
{
Q_OBJECT
public:
    Server();
    virtual void run();
signals:
        QString send(QString msg);
};

const int NR_PRT = 32;
const int LEN_PRT_NAME = 32;

struct Msg {
    int length;
    int type;
    uid_t uid;
    int nr_prt;
    char prt_name[NR_PRT][LEN_PRT_NAME];
};

#endif // SERVER_H
