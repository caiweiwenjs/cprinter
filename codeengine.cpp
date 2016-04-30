#include "codeengine.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

CodeEngine::CodeEngine()
{

}

uint32_t CodeEngine::encodeInt32(char **buf, uint32_t val) {
    if (buf == NULL || *buf == NULL) {
        return 0;
    }
    *((uint32_t *)(*buf)) = htonl(val);
    *buf += sizeof(uint32_t);
    return sizeof(uint32_t);
}

uint32_t CodeEngine::decodeInt32(char **buf, uint32_t *rval) {
    if (buf == NULL || *buf == NULL || rval == NULL) {
        return 0;
    }
    *rval = ntohl(*(uint32_t *)(*buf));
    *buf += sizeof(uint32_t);
    return sizeof(uint32_t);
}

uint32_t CodeEngine::encodeString(char **buf, char *str, uint32_t max) {
    if (buf == NULL || *buf == NULL || str == NULL || max <= 0) {
        return 0;
    }
    uint32_t len = strlen(str);
    if (len + 1 > max) return 0;
    uint32_t encode_len = encodeInt32(buf, len);
    memcpy(*buf, str, len + 1);
    *buf += len + 1;
    return len + 1 + encode_len;
}

uint32_t CodeEngine::decodeString(char **buf, char *str, uint32_t max) {
    if (buf == NULL || *buf == NULL || str == NULL || max <= 0) {
        return 0;
    }
    uint32_t len = 0;
    uint32_t decode_len = decodeInt32(buf, &len);
    if (len > max) {
        str[0] = '\0';
        return 0;
    }
    memcpy(str, *buf, len + 1);
    *buf += len + 1;
    return len + 1 + decode_len;
}
