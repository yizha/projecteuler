#include <stdio.h>

unsigned long long reverse(unsigned long long n) {
    unsigned long long r = 0;
    while (n > 0) {
        r = 10 * r + (n % 10);
        n = n / 10;
    }
    return r;
}

unsigned long long is_palindromic(unsigned long long n) {
    return n == reverse(n);
}

unsigned long long next(unsigned long long n) {
    return n + reverse(n);
}

int main(int argc, char* argv) {
    int cnt = 0;
    for (int i = 1; i < 10000; i++) {
        unsigned long long n = i;
        int j = 0;
        for (; j < 50; j++) {
            n = next(n);
            if (is_palindromic(n)) {
                //printf("palindromic: %u\n", n);
                break;
            }
        }
        if (j == 50) {
            //if (is_palindromic(i)) printf("Palindromic Lychrel number: %d\n", i);
            cnt++;
        }
    }
    printf("Lychrel number count = %d\n", cnt);
}
