#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define LIMIT 10000000

int is_permutation(int a, int b) {
    int digits[10] = {0,0,0,0,0,0,0,0,0,0};
    while (a > 0) {
        digits[a % 10]++;
        a = a / 10;
    }
    while (b > 0) {
        digits[b % 10]--;
        b = b / 10;
    }
    for (int i = 0; i < 10; i++) {
        if (digits[i] != 0) return 0;
    }
    return 1;
}

int calc_phi(int n, int *primes) {
    if (n == 1) return 1;
    int root = floor(sqrt(n)) + 1;
    int i = 0;
    int p = primes[i++];
    int cnt = n;
    int prime = 1;
    while (p <= root) {
        if ((n % p) == 0) {
            prime = 0;
            while ((n % p) == 0) n = n / p;
            cnt = (cnt / p) * (p - 1);
        }
        p = primes[i++];
    }
    if (prime) {
        return cnt - 1;
    } else {
        if (n > 1) cnt = (cnt / n) * (n - 1);
        return cnt;
    }
}

void solve() {
    int *nums = (int*) malloc(LIMIT * sizeof(int));
    for (int i = 0; i < LIMIT; i++) {
        nums[i] = 1;
    }
    int cnt = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i] == 1) {
            cnt++;
            int j = i + i;
            while (j < LIMIT) {
                nums[j] = 0;
                j = j + i;
            }
        }
    }
    int *primes = (int*) malloc(cnt * sizeof(int));
    int j = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i]) primes[j++] = i;
    }

    //printf("phi(%d)=%d\n", 87109, phi(87109, primes));
    unsigned long long numerator = 10000;
    unsigned long long denominator = 1;
    int *phi = (int*) malloc(LIMIT * sizeof(int) + 1);
    for (int i = 0; i < LIMIT; i++) phi[i] = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i]) continue; //skip primes
        if (phi[i] == -1) {
            continue;
        } else if (phi[i] == 0) {
            int p = calc_phi(i, primes);
            phi[i] = p;
            if (is_permutation(i, p)) {
                //printf("phi(%d)=%d\n", i, p);
                if (numerator * p > i * denominator) {
                    numerator = i;
                    denominator = p;
                } else {
                    p = -1;
                }
            }
            int j = i << 1;
            if ((p % 2) == 0) {
                if (p > 0) p = p << 1;
            }
            while (j < LIMIT) {
                phi[j] = p;
                j = j << 1;
                if (p > 0) p = p << 1;
            }
        } else {
            if (is_permutation(i, phi[i])) {
                //printf("phi(%d)=%d\n", i, phi[i]);
                if (numerator * phi[i] > i * denominator) {
                    numerator = i;
                    denominator = phi[i];
                }
            }
        }
        //int p = calc_phi(i, primes);
        //printf("phi(%d)=%d\n", i, phi(i, primes));
    }

    free(phi);
    free(primes);

    printf("n/phi(n) --> %llu/%llu\n", numerator, denominator);
}

/**
 * if n is prime, then phi(n) = n - 1, which couldn't be permutation.
 * so we test n which has two and only two prime factors.
 */
void solve1() {
    // generate some primes
    int nums[10000];
    for (int i = 0; i < 10000; i++) {
        nums[i] = 1;
    }
    int cnt = 0;
    for (int i = 2; i < 10000; i++) {
        if (nums[i] == 1) {
            cnt++;
            int j = i + i;
            while (j < 10000) {
                nums[j] = 0;
                j = j + i;
            }
        }
    }
    int *primes = (int*) malloc(cnt * sizeof(int));
    int j = 0;
    int start = 0;
    for (int i = 2; i < 10000; i++) {
        if (nums[i]) primes[j++] = i;
        if (i < 1000) start = j; // we start from prime greater than 1000
    }

    //printf("start prime = %d, max prime = %d\n", primes[start + 1], primes[cnt - 1]);

    int i = start + 1;
    int min_n;
    int min_phi;
    double min_r = 1000.0;
    while (i < cnt - 1) {
        int a = primes[i];
        int j = i + 1;
        while (j < cnt) {
            int b = primes[j];
            int n = a * b;
            if (n > LIMIT) break;
            int phi = (a - 1) * (b - 1);
            //printf("phi(%d)=%d\n", n, phi);
            if (is_permutation(n, phi)) {
                //printf("phi(%d)=%d\n", n, phi);
                double r = ((double) n) / ((double) phi);
                if (r < min_r) {
                    min_n = n;
                    min_phi = phi;
                    min_r = r;
                }
            }
            j++;
        }
        i++;
    }

    printf("n/phi(n) --> %d/%d\n", min_n, min_phi);
}

int main(int argc, char* argv) {
    //solve();
    solve1();
}
