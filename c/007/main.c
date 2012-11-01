#include <stdio.h>

int main(int argc, char **argv) {
    int primes[10001];
    primes[0] = 2;
    int idx = 1;

    int n = 3;
    while (idx <= 10001) {
        int prime = 1;
        for (int i = 0; i < idx; i++) {
            if ((n % primes[i]) == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) {
            primes[idx++] = n;
        }
        n++;
    }

    printf("10001th prime = %d\n", primes[10000]);
    return 0;
}
