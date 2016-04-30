#include "protocol.h"

#include "codeengine.h"

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
