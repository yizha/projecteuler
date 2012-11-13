#include <stdio.h>
#include <math.h>

/*
 * diagonal number count: 4n-3
 * diagonal number to test: (2n-1)^2 - 2m(n-1), m=1,2,3
 * square length: 2n-1
 */

int is_prime(int n) {
    if (n < 2) return 0;
    if (n < 4) return 1;
    if ((n % 2) == 0) return 0;
    int max = floor(sqrt(n)) + 1;
    for (int i = 3; i < max; i = i + 2) {
        if ((n % i) == 0) return 0;
    }   
    return 1;
}

int main(int argc, char* argv) {
    int n = 1;
    int step = 2;
    int diagonal_prime_cnt = 0;
    int diagonal_number_cnt = 1;
    while (1) {
        for (int i = 0; i < 3; i++) {
            n = n + step;
            if (is_prime(n)) diagonal_prime_cnt++;
        }
        n = n + step;
        diagonal_number_cnt = diagonal_number_cnt + 4;
        double f = diagonal_prime_cnt / (diagonal_number_cnt*1.0);
        //printf("%d: %f\n", step, f);
        if (f < 0.1) break;
        step = step + 2;
    }
    printf("side length = %d\n", step + 1);
}
