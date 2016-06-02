#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include "unixutil.h"

class Common
{
private:
    static QString DIR;// = "/var/spool/cups-pdf/" + UnixUtil::getUserName() + "/";
    static QString URL;// = "http://localhost/upload.php";
    static QString EXT;
public:
    Common();
    static QString getDir();
    static QString getUrl();
    static QString getExt();
};

#endif // COMMON_H
