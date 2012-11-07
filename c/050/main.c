#include <stdio.h>

int main(int argc, char* argv) {
    int primes[1000000];
    primes[2] = 1;
    for (int i = 3; i < 1000000; i = i + 2) {
        primes[i] = 1;
    }
    for (int i = 3; i < 1000000; i = i + 2) {
        if (primes[i]) {
            int j = i + i;
            while (j < 1000000) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }

    int sum = 0;
    int i = 2;
    int cnt = 0;
    int max = 0;
    while (sum < 1000) {
        if (primes[i]) sum = sum + i;
        if (primes[sum]) {
            cnt++;
            max = sum;
        }
        i++;
    }
    printf("%d primes add to %d\n", cnt, max);
}
