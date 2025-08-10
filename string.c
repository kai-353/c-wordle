#include "string.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

String create_string(const char *chars, uint32_t length) {
    String str;
    str.length = length;
    str.chars = malloc(length);
    for (uint32_t i = 0; i < length; i++) {
        str.chars[i] = chars[i];
    }
    return str;
}

void free_string(String *str) {
    free(str->chars);
    str->chars = NULL;
    str->length = 0;
}

void print_string(String str) {
    for (uint32_t i = 0; i < str.length; i++) {
        printf("%c", str.chars[i]);
    }
    printf("\n");
}