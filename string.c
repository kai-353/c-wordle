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

uint32_t max(const uint32_t a, const uint32_t b) {
    return (a > b) ? a : b;
}

int compare_strings(const String *str1, const String *str2) {
    for (uint32_t i = 0; i < max(str1->length, str2->length); i++) {
        // final characters are equal
        if (str1->chars[i] == str2->chars[i] && i == str1->length - 1 && i == str2->length - 1) {
            return 0;
        }
        // str1 > str2
        if (str1->chars[i] > str2->chars[i]) {
            return 1;
        }
        // str1 < str2
        if (str1->chars[i] < str2->chars[i]) {
            return -1;
        }
    }
    return 0;
}
