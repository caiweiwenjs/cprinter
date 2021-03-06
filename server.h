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
        QString signal_getPrinterName(QString msg);
        QString signal_uploadPDF(QString filename);
        void signal_updatePrintLog();
};



/*
const int NR_PRT = 32;
const int LEN_PRT_NAME = 32;

struct Msg {
    int length;
    int type;
    uid_t uid;
    int nr_prt;
    char prt_name[NR_PRT][LEN_PRT_NAME];
};
*/
#endif // SERVER_H
