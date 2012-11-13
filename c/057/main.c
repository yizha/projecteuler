#include <stdio.h>

void print_num(int *a, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", a[i]);
    }
}

void step(int *b, int *a, int *b_len, int *a_len) {
    // 2a --> p
    int i = 0;
    int overflow = 0;
    int p[500];
    for (; i < *a_len; i++) {
        int t = (a[i] << 1) + overflow;
        p[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            p[i++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    // p+b --> p
    overflow = 0;
    int j = 0;
    for (; j < i; j++) {
        int t = p[j] + b[j] + overflow;
        p[j] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            p[j++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    // swap numerator and denorminator
    // a --> b
    for (int k = 0; k < (*a_len + 1); k++) {
        b[k] = a[k];
    }
    *b_len = *a_len;
    // p (2a+b) --> a
    for (int k = 0; k < j; k++) {
        a[k] = p[k];
    }
    *a_len = j;
}

int qualified(int *b, int *a, int b_len, int a_len) {
    int s[500];
    int overflow = 0;
    int len = (b_len > a_len ? b_len : a_len);
    int i = 0;
    for (; i < len; i++) {
        int t = a[i] + b[i] + overflow;
        s[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            s[i++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    /*
    print_num(s, i);
    printf("/");
    print_num(a, a_len);
    int diff = (i - a_len);
    if (diff > 0) {
        printf("   ***   ");
    }
    printf("\n");
    return diff;
    */
    return (i - a_len);
}

int main(int argc, char* argv) {
    int i = 0;
    int cnt = 0;
    int b[500];
    int a[500];
    for (int i = 0; i < 500; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    b[0] = 1;
    a[0] = 2;
    int b_len = 1;
    int a_len = 1;

    do {
        if (qualified(b, a, b_len, a_len) > 0) cnt++;
        step(b, a, &b_len, &a_len);
        i++;
    } while (i < 1000);
    printf("count = %d\n", cnt);

    //printf("max int = %llu\n", 0xFFFFFFFFFFFFFFFF);
}
