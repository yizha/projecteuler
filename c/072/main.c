#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define LIMIT 1000000

int phi(int n, int *nums, int *primes) {
    if (n == 1) return 1;
    if (nums[n]) return n - 1;
    int r = floor(sqrt(n)) + 1;
    int i = 0;
    int p = primes[i++];
    int cnt = n;
    while (p <= r) {
        if ((n % p) == 0) {
            cnt = (cnt / p) * (p - 1);
            while ((n % p) == 0) n = n / p;
        }
        p = primes[i++];
    }
    if (n > 1) cnt = (cnt / n) * (n - 1);
    return cnt;
}

void solve() {
    int *nums = (int*) malloc(LIMIT * sizeof(int));
    for (int i = 0; i < LIMIT; i++) {
        nums[i] = 1;
    }   
    int p_cnt = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i] == 1) {
            p_cnt++;
            int j = i + i;
            while (j < LIMIT) {
                nums[j] = 0;
                j = j + i;
            }
        }
    }   
    int *primes = (int*) malloc(p_cnt * sizeof(int));
    int j = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i]) primes[j++] = i;
    }

    unsigned long long sum = 0;
    for (int i = 2; i <= LIMIT; i++) {
        sum = sum + phi(i, nums, primes);
        //printf("phi(%d)=%d\n", i, phi(i, nums, primes));
    }
    printf("sum=%llu\n", sum);
}

void solve1() {
    unsigned long long sum = 0;
    int phis[LIMIT + 1];
    for (int i = 2; i <= LIMIT; i++) phis[i] = i;
    for (int i = 2; i <= LIMIT; i++) {
        if (phis[i] == i) { // prime
            for (int j = i; j <= LIMIT; j = j + i) {
                phis[j] = phis[j] - (phis[j] / i);
            }
        }
        sum = sum + phis[i];
    }
    printf("sum=%llu\n", sum);
}

int main(int argc, char* argv) {
    //solve();
    solve1();
}
