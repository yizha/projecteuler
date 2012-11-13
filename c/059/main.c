#include <stdio.h>

int main(int argc, char* argv) {
    printf("%d\n", 0^0);
    printf("%d\n", 1^0);
    printf("%d\n", 0^1);
    printf("%d\n", 1^1);
    for (int i = 97; i <= 122; i++) {
        int x = i ^ 79;
        printf("%d --> %c\n", x, x);
        if (x>=97 && x<=122) {
            printf("%c --> %c\n", i, x);
        }
    }
}
