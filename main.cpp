#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server s;
    QObject::connect(&s, SIGNAL(send(QString)),
                      &w, SLOT(test_server(QString)), Qt::BlockingQueuedConnection);
    s.start();
    w.show();

    return a.exec();
}
