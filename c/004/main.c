#include <stdio.h>

int is_palindrome(int n) {
    int d[10];
    int i = 0;
    while (n > 10) {
        d[i++] = n % 10;
        n = n / 10;
    }
    d[i] = n;
    int m = (i / 2) + 1;
    for (int j = 0; j < m; j++) {
        if (d[j] != d[i - j]) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    int a = 999;
    int b = 0;
    int m = 1;
    int max = 0;
    while (a >= 100) {
        if ((a % 11) == 0) {
            b = 999;
            m = 1;
        } else {
            b = 990;
            m = 11;
        }
        while (b >= a) {
            int x = a * b;
            if (x < max) break;
            if (is_palindrome(x)) max = x;
            b = b - m;
        }
        a--;
    }
    printf("largest palindrome = %d\n", max);
    return 0;
}
