#include <stdio.h>

int truncatable_prime(int n, int *primes) {
    int x = n;
    while (x > 0) {
        if (primes[x] == 0) return 0;
        x = x / 10;
    }
    int d = 10;
    x = n % d;
    while (x < n) {
        if (primes[x] == 0) return 0;
        d = d * 10;
        x = n % d;
    }
    return 1;
}

int main(int argc, char* argv) {
    unsigned int primes[1000000];
    for (int i = 0; i < 1000000; i++) {
        primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    int cnt = 0;
    int sum = 0;
    for (int i = 2; i < 1000000; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 1000000) {
                primes[j] = 0;
                j = j + i;
            }
            if (i > 22) {
                if (truncatable_prime(i, primes)) {
                    sum = sum + i;
                    if (++cnt == 11) {
                        break;
                    }
                }
            }
        }
    }
    printf("sum = %d\n", sum);
}
