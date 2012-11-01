#include <stdio.h>

int main(int argc, char **argv) {
    int a = 2;
    int b = 3;
    int c = 0;
    int sum = 0;
    int i = 0;
    while (a < 4000000) {
        if (i == 0) {
            sum = sum + a;
            i = 3;
        }
        c = a + b; 
        a = b;
        b = c;
        i--;
    }
    printf("sum = %d\n", sum);
    return 0;
}
