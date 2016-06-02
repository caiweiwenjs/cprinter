#include "cupsutil.h"
#include <cups/cups.h>
#include <QVector>
#include <QString>
#include <QProcess>


CupsUtil::CupsUtil()
{
    //int job_id;
    //job_id = cupsPrintFile("", "/home/cww/Desktop/test2")
}

QVector<QString> CupsUtil::getDests() {
    QVector<QString> ret;
    cups_dest_t *dests;
    int num_dests = cupsGetDests(&dests);
    for (int i = 0;i < num_dests;i++) {
        cups_dest_t *t = dests + i;
        if (t != nullptr)
              ret.push_back(t->name);
    }
    cupsFreeDests(num_dests, dests);
    return ret;
}

int CupsUtil::printFile(const char *name, const char *filename, const char *title,
                        int num_options, cups_option_t *options) {
    int job_id;
    job_id = cupsPrintFile(name, filename, title, num_options, options);
    return job_id;
}

int CupsUtil::printFile(QString printerName, QString fileName, QString title, QString str_options) {
    int job_id;
    QProcess lp_cups;
    lp_cups.start("./lp_cups", QStringList() << printerName << fileName << title << str_options);
    if (!lp_cups.waitForFinished())
        return 0;
    QByteArray result = lp_cups.readAll();
    job_id = result.toInt();
    //qDebug() << job_id;
    return job_id;
}

int CupsUtil::parseOptions(const char *arg, cups_option_t **options) {
    return cupsParseOptions(arg, 0, options);
}

void CupsUtil::freeOptions(int num_options, cups_option_t *options) {
    cupsFreeOptions(num_options, options);
}

