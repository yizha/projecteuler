/* https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation */
#include <stdio.h>

int calc_one(int n) {
    int cnt = -1;
    int sum = 0;
    int c = n;
    int p = 0;
    int x = -1;

    int p20,sx;
    while ((cnt < 100) || (c == 0)) {
        if (p == 0) {
            p20 = 0;
            x = 1;
        } else {
            p20 = (p<<4) + (p<<2); // 20p
            x = c / p20;
        }
        // x(20p+x)
        sx = x*(p20+x);
        if (sx == c) {
            break;
        } else if (sx > c) {
            do {
                sx = sx - ((x<<1) + p20 - 1);
                x = x - 1;
            } while (sx > c);
            if (sx == c) {
                break;
            }
        } else { // sx < c
            do {
                sx = sx + ((x<<1) + p20 +1);
                x = x + 1;
            } while (sx < c);
            if (sx == c) {
                break;
            }
        }

        cnt = cnt + 1;
        p = 10*p + x;
        c = 100*(c-sx);
        printf("%d\n", x);
        if (cnt > 0) sum = sum + x;
    }

    if (cnt < 100) {
        // non-irrational square root
        return 0;
    } else {
        // sum of the first 100 decimal digit
        // of the irrational square root
        return sum;
    }
}

int main(int argc, char* argv) {
    calc_one(1);
    return 0;
}
