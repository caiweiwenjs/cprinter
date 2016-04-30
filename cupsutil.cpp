#include "cupsutil.h"
#include <cups/cups.h>
#include <QVector>
#include <QString>

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

