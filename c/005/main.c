#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
    int primes[21];
    for (int i = 0; i < 21; i++) {
        primes[i] = 1;
    }
    for (int i = 2; i < 21; i++) {
        if (primes[i]) {
            int n = i + i;
            while (n < 21) {
                primes[n] = 0;
                n = n + i;
            }
        }
    }
    int n = 1;
    int m = floor(sqrt(20));
    for (int i = 2; i < 21; i++) {
        if (!primes[i]) continue;
        if (i <= m) {
            int x = i;
            while (x < 20) x = x * i;
            x = x / i;
            n = n * x;
        } else {
            n = n * i;
        }
    }
    printf("minimum number = %d\n", n);
    return 0;
}
