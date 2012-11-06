#include <stdio.h>
#include <math.h>
#include <malloc.h>

int is_prime(int n) {
    if (n < 2) return 0;
    if (n < 4) return 1;
    int max = floor(sqrt(n)) + 1;
    for (int i = 3; i < max; i = i + 2) {
        if ((n % i) == 0) return 0;
    }   
    return 1;
}

int count_prime_divisitors(int n) {
    int cnt = 0;
    if ((n % 2) == 0) {
        cnt++;
        while ((n % 2) == 0) n = n / 2;
    }
    int max = floor(sqrt(n)) + 1;
    for (int i = 3; i < max; i = i + 2) {
        if (!is_prime(i)) continue;
        if ((n % i) == 0) {
            cnt++;
            while ((n % i) == 0) n = n / i;
        }
    }
    if (n > 1) cnt++;
    return cnt;
}

int main(int argc, char* argv) {
    // test 4-digits numbers
    int i = 210;
    while (1) {
        int a = i;
        int b = a + 1;
        int c = b + 1;
        int d = c + 1;
        if (is_prime(d)) {
            i = i + 4;
            continue;
        } else if (is_prime(c)) {
            i = i + 3;
            continue;
        } else if (is_prime(b)) {
            i = i + 2;
            continue;
        } else if (is_prime(a)) {
            i++;
            continue;
        } else {
            if (count_prime_divisitors(a) == 4
                && count_prime_divisitors(b) == 4
                && count_prime_divisitors(c) == 4
                && count_prime_divisitors(d) == 4) {
                printf("number = %d\n", a);
                return 0;
            }
            i++;
        }
    }
    return 0;
}
