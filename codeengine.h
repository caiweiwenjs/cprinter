#ifndef CODE_ENGINE_H
#define CODE_ENGINE_H

#include <stdint.h>

class CodeEngine
{
public:
    CodeEngine();
    static uint32_t encodeInt32(char **buf, uint32_t val);
    static uint32_t decodeInt32(char **buf, uint32_t *rval);
    static uint32_t encodeString(char **buf, char *str, uint32_t max);
    static uint32_t decodeString(char **buf, char *str, uint32_t max);
};

#endif // UTIL_H
