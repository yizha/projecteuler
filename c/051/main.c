#include <stdio.h>
#include <math.h>

/*
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
}
*/

int is_prime(int *digits, int len) {
    int d = digits[len - 1];
    if (d == 0 || d == 2 || d == 4 || d == 5 || d == 6 || d == 8) return 0;
    int s = 0;
    for (int i = 0; i < len; i++) s = s + digits[i];
    if ((s % 3) == 0) return 0;
    int n = 0;
    for (int i = 0; i < len; i++) n = 10 * n + digits[i];
    int max = floor(sqrt(n)) + 1;
    for (int i = 7; i < max; i = i + 2) {
        if ((n % i) == 0) return 0;
    }   
    return 1;
}

int next_pattern(int *p, int n, int m) {
    int i = 0;
    for (; i < n; i++) {
        if (p[i] == 1) break;
    }
    if (i == n) { // 1st pattern for this n-digit number
        for (i = 0; i < m; i++) {
            p[i] = 1;
        }
        return 1;
    }
    // now generate the next pattern
    int one_cnt = 0;
    for (i = 0; i < n - 1; i++) {
        if (p[i] == 1) one_cnt++;
        if (p[i] != 1 || p[i + 1] != 0) continue;
        p[i] = 0;
        p[i + 1] = 1;
        if (one_cnt > 0 && i > 0) {
            for (int j = 0; j < i; j++) {
                p[j] = ((one_cnt-- > 0) ? 1 : 0);
            }
        }
        return 1;
    }
    return 0;
}

int next_pattern_number(int *pattern, int * digits, int len) {

}

int main(int argc, char* argv) {
    int i = 2; // start from 2-digits number
    while (1) {

        i++;
    }
}
