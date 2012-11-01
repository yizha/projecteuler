#include <stdio.h>
#include <math.h>
#include <time.h>

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

void fast(int s) {
    s = s / 2;
    int max_m = floor(sqrt(s)) + 1;
    for (int m = 2; m < max_m; m++) {
        if ((s % m) != 0) continue;
        int sm = s / m;
        while ((sm % 2) == 0) sm = sm / 2;
        int k = m + 1;
        while (k <= sm && k < 2 * m) {
            if ((sm % k) == 0 && gcd(m,k) == 1) {
                int d = s / (m * k);
                int n = k - m;
                int a = d * (m * m - n * n);
                int b = 2 * d * m * n;
                int c = d * (m * m + n * n);
                int p = a * b * c;
                printf("a=%d, b=%d, c=%d, product=%d\n", a, b, c, p);
                return;
            }
            k = k + 2;
        }
    }
    return;
}

void slow(int max) {
    int max_a = (max - 3) / 3 + 1; 
    for (int a = 1; a < max_a; a++) {
        int max_b = (max - a) / 2;
        for (int b = a + 1; b < max_b; b++) {
            int c = max - a - b;
            if ((a * a + b * b) == c * c) {
                int p = a * b * c;
                printf("a=%d, b=%d, c=%d, product=%d\n", a, b, c, p);
                return;
            }
        }
    }
    return;
}

int main(int argc, char **argv) {
    //slow(1000);
    fast(1000);
}
