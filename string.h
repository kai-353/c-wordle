#ifndef STRING_H
#define STRING_H

#include <stdint.h>

typedef struct String {
    char *chars;
    uint32_t length;
} String;

String create_string(const char *chars, uint32_t length);
void free_string(String *str);
void print_string(String str);

#endif // STRING_H
