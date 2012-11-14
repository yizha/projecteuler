#include <stdio.h>

int main(int argc, char* argv) {
    int primes[1000000];
    for (int i = 0; i < 1000000; i++) primes[i] = 1;
    for (int i = 2; i < 1000000; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 1000000) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }
}
