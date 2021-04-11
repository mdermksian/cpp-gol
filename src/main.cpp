#include <stdio.h>
int main(void) {
#ifdef _WIN32
    printf("Hello, windows");
#else
    printf("Hello, other");
#endif
    return 0;
}