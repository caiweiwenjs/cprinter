#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server s;
    QObject::connect(&s, SIGNAL(signal_getPrinterName(QString)),
                      &w, SLOT(slot_getPrinterName(QString)), Qt::BlockingQueuedConnection);
    QObject::connect(&s, SIGNAL(signal_updatePrintLog(void)),
                      &w, SLOT(slot_updatePrintLog(void)), Qt::BlockingQueuedConnection);
    s.start();
    w.show();

    return a.exec();
}
