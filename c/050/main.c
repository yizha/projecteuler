#include <stdio.h>
#include <malloc.h>

int main(int argc, char* argv) {
    // find primes under 1000000
    int numbers[1000000];
    int cnt = 0;
    for (int i = 2; i < 1000000; i++) {
        numbers[i] = 1;
    }
    numbers[0] = 0;
    numbers[1] = 0;
    for (int i = 2; i < 1000000; i++) {
        if (numbers[i]) {
            cnt++;
            int j = i + i;
            while (j < 1000000) {
                numbers[j] = 0;
                j = j + i;
            }
        }
    }
    // copy all primes to another array
    int *primes = (int*) malloc(cnt * sizeof(int));
    int x = 0;
    primes[x++] = 2;
    for (int i = 3; i < 1000000; i = i + 2) {
        if (numbers[i]) primes[x++] = i;
    }
    // search for the prime
    int max = 1000000;
    int i = 0;
    int max_cnt = 0;
    int the_prime = 0;
    while (1) {
        int sum = 0;
        int cnt = 0;
        int j = i;
        while (sum < max) {
            //printf("sum=%d\n",sum);
            if (numbers[sum]) {
                if (cnt > max_cnt) {
                    max_cnt = cnt;
                    the_prime = sum;
                }
            }
            sum = sum + primes[j];
            cnt++;
            j++;
        }
        i++;
        if (primes[i] >= (max / 2)) break;
    }
    printf("%d primes add to %d\n", max_cnt, the_prime);

    free(primes);

/*
    int start = 2;
    int prime = 2;
    int max_cnt = 1;
    while (start < 1000) {
        int i = start;
        int sum = 0;
        int cnt = 0;
        while (sum < 1000) {
            if (sum + i > 1000) break;
            if (primes[i]) sum = sum + i;
            if (primes[sum]) {
                cnt++;
                if (cnt > max_cnt) {
                    max_cnt = cnt;
                    prime = sum;
                }
                //printf("%d/%d\n", sum, cnt);
            }
            i++;
        }
        start++;
        while (!primes[start] && start < 1000) start++;
        printf("start = %d\n", start);
    }
    printf("%d primes add to %d\n", max_cnt, prime);
    */
}
