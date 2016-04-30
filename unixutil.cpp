#include "unixutil.h"
#include <pwd.h>
#include <unistd.h>

UnixUtil::UnixUtil()
{

}


QString UnixUtil::userName;

QString UnixUtil::getUserName() {
    if (userName.length() == 0) {
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        userName = pwd->pw_name;
    }
    return userName;
}
