#include <stdio.h>
#include <malloc.h>

int to_digit_array(int n, int *digits) {
    while (n > 0) {
        digits[n % 10]++;
        n = n / 10;
    }
}

int is_permutation(int a, int b, int c) {
    int a_d[] = {0,0,0,0,0,0,0,0,0,0};
    to_digit_array(a, a_d);
    int b_d[] = {0,0,0,0,0,0,0,0,0,0};
    to_digit_array(b, b_d);
    int c_d[] = {0,0,0,0,0,0,0,0,0,0};
    to_digit_array(c, c_d);
    for (int i = 0; i < 10; i++) {
        if ((a_d[i] != b_d[i]) || (b_d[i] != c_d[i])) return 0;
    }
    return 1;
}

int main(int argc, char* argv) {
    // find all 4-digit primes
    int primes[10000];
    for (int i = 0; i < 10000; i++) {
        primes[i] = 1;
    }
    int cnt = 0;
    for (int i = 2; i < 10000; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 10000) {
                primes[j] = 0;
                j = j + i;
            }
            if (i > 999) cnt++;
        }
    }
    // copy all 4-digit primes to a new array
    int *ptr = (int*) malloc(cnt * sizeof(int));
    int x = 0;
    for (int i = 1001; i < 10000; i++) {
        if (primes[i]) ptr[x++] = i;
    }
    // find three primes that increase equally
    for (int i = 0; i < cnt - 2; i++) {
        for (int j = i + 2; j < cnt; j++) {
            for (int k = i + 1; k < j; k++) {
                if (((ptr[i] + ptr[j]) == (ptr[k] << 1)) 
                        && is_permutation(ptr[i], ptr[k], ptr[j])) {
                    printf("%d%d%d\n", ptr[i], ptr[k], ptr[j]);
                }
            }
        }
    }

    free(ptr);
}
