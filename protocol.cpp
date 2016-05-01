#include "protocol.h"
#include <string.h>
#include "codeengine.h"

JobMsg::JobMsg() {}

JobMsg::JobMsg(char *title, char *options, char *copies) {
    strncpy(this->title, title, MAXL);
    strncpy(this->options, options, MAXL);
    strncpy(this->copies, copies, MAXL);
}

JobMsg::JobMsg(char *buf) {
    decode(buf);
}

uint32_t JobMsg::encode(char *buf) {
    uint32_t rlen = 0;
    rlen += CodeEngine::encodeString(&buf, title, MAXL);
    rlen += CodeEngine::encodeString(&buf, options, MAXL);
    rlen += CodeEngine::encodeString(&buf, copies, MAXL);
    return rlen;
}

void JobMsg::decode(char *buf) {
    CodeEngine::decodeString(&buf, title, MAXL);
    CodeEngine::decodeString(&buf, options, MAXL);
    CodeEngine::decodeString(&buf, copies, MAXL);
}
