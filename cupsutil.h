#ifndef CUPSUTIL_H
#define CUPSUTIL_H

#include <QVector>
#include <QString>
#include <cups/cups.h>

class cupsutil
{
public:
    cupsutil();
    static QVector<QString> getDests();
    static int printFile(const char *name, const char *filename, const char *title,
                            int num_options, cups_option_t *options);
};

#endif // CUPSUTIL_H
