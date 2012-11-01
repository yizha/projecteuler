#include <stdio.h>

void solution1(int limit) {
    int primes[limit];
    
    for (int i = 2; i < limit; i++) {
        primes[i] = 1;
    }

    long long sum = 0;
    for (int i = 2; i < limit; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < limit) {
                primes[j] = 0;
                j = j + i;
            }
            sum = sum + i;
        }
    }

    printf("sum = %lld\n", sum);
}

void solution2(int limit) {
    int primes[limit];
    primes[0] = 2;
    int idx = 1;
    long long sum = 2;
    for (int i = 3; i < limit; i++) {
        int prime = 1;
        for (int j = 0; j < idx; j++) {
            if ((i % primes[j]) == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) {
            primes[idx++] = i;
            sum = sum + i;
        }
    }
    printf("sum = %lld\n", sum);
}

int main(int argc, char **argv) {
    int limit = 1000000;
    solution1(limit);
    //solution2(limit); // slow
}
