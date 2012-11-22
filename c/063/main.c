#include <stdio.h>

int my_power(int m, int n) {
    int digits[100];
    digits[0] = 1;
    int size = 1;
    for (int i = 1; i < 100; i++) digits[i] = 0; 
    while (n > 0) {
        int overflow = 0;
        for (int i = 0; i < size; i++) {
            int t = digits[i] * m + overflow;
            digits[i] = t % 10;
            overflow = t / 10;
        }
        if (overflow > 0) {
            while (overflow > 0) {
                digits[size++] = overflow % 10;
                overflow = overflow / 10;
            }
        }
        n--;
    }
    /*for (int i = size - 1; i >= 0; i--) {
        printf("%d", digits[i]);
    }
    printf(", %d", size);
    printf("\n");*/
    return size;
}

int main(int argc, char* argv) {
    int n = 1;
    int cnt = 0;
    while (1) {
        int cycle_cnt = 0;
        for (int i = 1; i <= 9; i++) {
            if (my_power(i, n) == n) cycle_cnt++;
        }
        if (cycle_cnt == 0) break;
        cnt = cnt + cycle_cnt;
        n++;
    }

    printf("count=%d\n", cnt);
    return 0;
}
