#include "common.h"

Common::Common()
{

}

QString Common::DIR =  "/var/spool/cups-pdf/" + UnixUtil::getUserName() + "/";
QString Common::URL = "http://localhost/upload.php";
QString Common::EXT = ".pdf";

QString Common::getDir() {
    return DIR;
}

QString Common::getUrl() {
    return URL;
}

QString Common::getExt() {
    return EXT;
}
