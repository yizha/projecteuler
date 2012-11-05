#include <stdio.h>

int main(int argc, char* argv) {
    int digits_cnt[] = {9 * 1, 90 * 2, 900 * 3, 9000 * 4, 90000 * 5, 900000 * 6};
    int position[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

    int digits[] = {1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 7; i++) {
        int n = position[i];
        int j = 0;
        // where the n-th digit falls into?
        for (; j < 6; j++) {
            int x = digits_cnt[j];
            if (n > x) {
                n = n - x;
            } else {
                break;
            }
        }
        // which number and which digit of it we are looking for?
        int x = j + 1;
        int n_th = 0;
        int d_th = 0;
        if ((n % x) == 0) {
            n_th = n / x;
            d_th = x;
        } else {
            n_th = n / x + 1;
            d_th = n % x;
        }
        // now get the number then the digit
        int number = position[j] + n_th - 1;
        int mod_cnt = x - d_th;
        while (mod_cnt-- > 0) number = number / 10;
        digits[i] = number % 10;
    }

    int p = 1;
    for (int i = 0; i < 7; i++) {
        p = p * digits[i];
    }
    printf("products = %d\n", p);
}
