#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX 1000000

int main(int argc, char* argv) {
    int primes[100];
    for (int i = 2; i < 100; i++) primes[i] = 1;
    for (int i = 2; i < 100; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 100) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }

    int n = 1;
    int factors[100];
    int size = 0;
    for (int i = 2; i < 100; i++) {
        if (primes[i]) {
            n = n * i;
            factors[size++] = i;
            if (n > MAX) {
                n = n / i;
                size--;
                break;
            }
        }
    }

    printf("n=%d\n", n);
    /*
    char *numbers = (char*) malloc(n + 1);
    memset(numbers, 1, n + 1);
    for (int i = 0; i < size; i++) {
        int j = factors[i];
        while (j <= n) {
            numbers[j] = 0;
            j = j + factors[i];
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (numbers[i] == 1) cnt++;
    }
    printf("cnt=%d\n", cnt);

    free(numbers);
    */
}
