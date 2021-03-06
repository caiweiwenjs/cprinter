#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

class JobMsg {
public:
    static const int MAXL = 1024;
    char title[MAXL];
    char options[MAXL];
    char copies[MAXL];

    JobMsg();
    JobMsg(char *title, char *options, char *copies);
    JobMsg(char *buf);
    uint32_t encode(char *buf);
    void decode(char *buf);
};

#endif // PROTOCOL_H
