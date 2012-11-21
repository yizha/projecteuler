#include <stdio.h>
#include <math.h>
#include <malloc.h>

int is_prime(int n) {
    if (n < 2) return 0;
    if (n < 4) return 1;
    if ((n % 2) == 0) return 0;
    int max = floor(sqrt(n)) + 1;
    for (int i = 3; i < max; i = i + 2) {
        if ((n % i) == 0) return 0;
    }   
    return 1;
}

int concat(int a, int b) {
    int t = b;
    int k = 1;
    while (t > 0) {
        k = k * 10;
        t = t / 10;
    }
    return k * a + b;
}

int qualified(int a, int b) {
    return is_prime(concat(a, b)) && is_prime(concat(b, a));
}

void solve() {
    int p_cnt = 0;
    int flags[10000];
    for (int i = 0; i < 10000; i++) flags[i] = 1;
    for (int i = 2; i < 10000; i++) {
        if (flags[i]) {
            p_cnt++;
            int j = i + i;
            while (j < 10000) {
                flags[j] = 0;
                j = j + i;
            }
        }
    }
    int *primes = (int*) malloc(p_cnt * sizeof(int));
    int j = 0;
    for (int i = 2; i < 10000; i++) {
        if (flags[i]) primes[j++] = i;
    }
    printf("prime cnt=%d\n", p_cnt);

    for (int a = 0; a < p_cnt; a++) {
        for (int b = a + 1; b < p_cnt; b++) {
            if (!qualified(primes[a], primes[b])) continue;
            for (int c = b + 1; c < p_cnt; c++) {
                if (!qualified(primes[a], primes[c])) continue;
                if (!qualified(primes[b], primes[c])) continue;
                for (int d = c + 1; d < p_cnt; d++) {
                    if (!qualified(primes[a], primes[d])) continue;
                    if (!qualified(primes[b], primes[d])) continue;
                    if (!qualified(primes[c], primes[d])) continue;
                    /*int sum = primes[a]+primes[b]+primes[c]+primes[d];
                    printf("%d,%d,%d,%d, sum=%d\n",
                                primes[a],primes[b],primes[c],primes[d],sum);
                    */
                    for (int e = d + 1; e < p_cnt; e++) {
                        if (!qualified(primes[a], primes[e])) continue;
                        if (!qualified(primes[b], primes[e])) continue;
                        if (!qualified(primes[c], primes[e])) continue;
                        if (!qualified(primes[d], primes[e])) continue;
                        int sum = primes[a]+primes[b]+primes[c]+primes[d]+primes[e];
                        printf("%d,%d,%d,%d,%d sum=%d\n",
                                primes[a],primes[b],primes[c],primes[d],primes[e],sum);
                        return;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv) {
    solve();
}
