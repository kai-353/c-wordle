#include "string.h"
#include <stdio.h>

int main() {
    String str = create_string("Hello, World!", 13);
    print_string(str);
    free_string(&str);
    return 0;
}