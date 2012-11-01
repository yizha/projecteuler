#include <stdio.h>

int main(int argc, char* argv) {
    int r[1000];
    r[0] = 1;
    int idx = 1;
    for (int i = 0; i < 1000; i++) {
        int overflow = 0;
        for (int j = 0; j < idx; j++) {
            int tmp = 2 * r[j] + overflow;
            r[j] = tmp % 10;
            overflow = tmp / 10;
        }
        while (overflow > 10) {
            r[idx++] = overflow % 10;
            overflow = overflow / 10;
        }
        if (overflow > 0) {
            r[idx++] = overflow;
        }
    }

    int sum = 0;
    for (int i = 0; i < idx; i++) {
        sum = sum + r[i];
    }
    printf("sum = %d\n", sum);

    return 0;
}
