#pragma once
#include <stddef.h>

#define FIND_PATTERN(start, end, pattern)                                                   \
    ({                                                                                      \
        uint8_t* result = NULL;                                                             \
        size_t pattern_size = sizeof(pattern);                                              \
        for (uint8_t* ptr = (uint8_t*)(start); ptr < (uint8_t*)(end)-pattern_size; ptr++) { \
            if (memcmp(ptr, pattern, pattern_size) == 0) {                                  \
                result = ptr;                                                               \
                break;                                                                      \
            }                                                                               \
        }                                                                                   \
        result;                                                                             \
    })

int memcmp(const void *cs, const void *ct, size_t count);
void *malloc(size_t size);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t count);