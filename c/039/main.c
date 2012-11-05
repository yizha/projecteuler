#include <stdio.h>
#include <math.h>

/*
 * a^2 + b^2 = c^2
 * a = m^2 - n^2
 * b = 2mn
 * c = m^2 + n^2
 * a + b + c = 2m(m + n) = s
 * m(m + n) = s/2 (0<s<=1000)
 * m > n
 * so we have below conditions:
 * 1) s must be divisable by 2
 * 2) s/2 must not be a prime 
 */

int gcd(int m, int n) {
    int t = m - n;
    int x = t < 0 ? -t : t;
    while (x > 1) {
        if ((m % x) == 0 && (n % x) == 0) return x;
        m = m < n ? m : n;
        n = x;
        t = m - n;
        x = t < 0 ? -t : t;
    }
    return 1;
}

int main(int argc, char* argv) {
    // find all primes under 500
    int primes[500];
    for (int i = 0; i < 500; i++) {
        primes[500] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    for (int i = 2; i < 500; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 500) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }
    
    int num = 0;
    int num_solution_cnt = 0;
    for (int i = 12; i <= 1000; i = i + 2) { // even numbers only
        int s = i / 2;
        if (primes[s]) continue; // skip prime
        int max_m = floor(sqrt(s)) + 1;
        int cnt = 0;
        for (int m = 2; m < max_m; m++) {
            if ((s % m) != 0) continue;
            int sm = s / m;
            while ((sm % 2) == 0) sm = sm / 2;
            int k = m + 1;
            while ((k <= sm) && (k < 2 * m)) {
                if ((sm % k) == 0 && gcd(m, k) == 1) {
                    int d = s / (m * k); 
                    int n = k - m;
                    int a = d * (m * m - n * n); 
                    int b = 2 * d * m * n;
                    int c = d * (m * m + n * n);
                    //printf("{%d, %d, %d} --> %d\n", a, b, c, a + b + c);
                    cnt++;
                }
                k++;
            }
        }
        if (cnt > num_solution_cnt) {
            num_solution_cnt = cnt;
            num = i;
        }
    }

    printf("number = %d, count = %d\n", num, num_solution_cnt);
}
