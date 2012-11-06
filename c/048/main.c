#include <stdio.h>

void *power(int n, int *p) {
    int t = n;
    for (int i = 0; i < 10; i++)  {
        if (t > 0) {
            p[i] = t % 10;
            t = t / 10;
        } else {
            p[i] = 0;
        }
    }
    for (int i = 2; i <= n; i++) {
        int overflow = 0;
        for (int j = 0; j < 10; j++) {
            int t = p[j] * n + overflow;
            overflow = t / 10;
            p[j] = t % 10;
        }
    }
}

void *add(int *a, int *b) {
    int overflow = 0;
    for (int i = 0; i < 10; i++) {
        int t = a[i] + b[i] + overflow;
        overflow = t / 10;
        a[i] = t % 10;
    }
}

int main(int argc, char* argv) {
    int sum[] = {0,0,0,0,0,0,0,0,0,0};
    int p[] = {0,0,0,0,0,0,0,0,0,0};
    for (int i = 1; i < 1001; i++) {
        if ((i % 10) == 0) continue;
        power(i, p);
        add(sum, p);
    }

    for (int i = 9; i >= 0; i--) {
        printf("%d", sum[i]);
    }
    printf("\n");
}
