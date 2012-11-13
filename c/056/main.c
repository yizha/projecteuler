#include <stdio.h>

int multiply(int *a, int b, int a_len, int x) {
    int overflow = 0;
    int i = 0;
    for (; i < a_len; i++) {
        int t = a[i] * b + overflow;
        a[i] = t % x;
        if (t >= x) {
            overflow = t / x;
        } else {
            overflow = 0;
        }
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[i++] = overflow % x;
            overflow = overflow / x;
        }
    }
    return i;
}

int sum_digits(int *a, int len) {
    int s = 0;
    for (int i = 0; i < len; i++) {
        int n = a[i];
        while (n > 0) {
            s = s + (n % 10);
            n = n / 10;
        }
    }
    return s;
}

int main(int argc, char* argv) {
    int max_a;
    int max_b;
    int max_sum = 0;
    int x = 10000;
    for (int i = 2; i < 100; i++) {
        for (int j = 2; j < 100; j++) {
            int a[100];
            a[0] = i;
            int len = 1;
            int b = j;
            while (--b > 0) {
                len = multiply(a, i, len, x);
            }
            int sum = sum_digits(a, len);
            /*printf("a=%d, b=%d, num=", i, j);
            for (int i = 0; i < len; i++) {
                printf("%d,", a[i]);
            }
            printf("\n");*/
            if (sum > max_sum) {
                max_sum = sum;
                max_a = i;
                max_b = j;
            }
        }
    }
    printf("a=%d, b=%d, max sum=%d\n", max_a, max_b, max_sum);
}
