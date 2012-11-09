#include <stdio.h>
#include <math.h>
#include <malloc.h>

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
    return n;
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
        one_cnt--;
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

int next_pattern_number(int *p, int * p_num, int len) {
    for (int i = 0; i < len; i++) {
        if (p[i] == 1) p_num[i] = 0;
    }
    do {
        int overflow = 1;
        for (int i = len - 1; i >= 0; i--) {
            if (p[i] == 1) continue;
            int t = p_num[i] + overflow;
            if (t > 9) {
                p_num[i] = t % 10;
                overflow = t / 10;
            } else {
                p_num[i] = t;
                overflow = 0;
                break;
            }
        }
        if (overflow == 1) {
            //printf("patter number over\n");
            return 0;
        }
    } while (p[0] == 0 && p_num[0] == 0);
    return 1;
}

int next_number(int *p, int *p_num, int len) {
    do {
        for (int i = 0; i < len; i++) {
            if (p[i] == 0) continue;
            if (p_num[i] == 9) return 0;
            p_num[i]++;
        }

    } while (p_num[0] == 0);
    return 1;
}

void print_array(int *p, int *p_num, int len) {
    for (int i = 0; i < len; i++) {
        if (p[i] == 1) {
            printf("x");
        } else {
            printf("%d", p_num[i]);
        }
    }
    printf("\n");
}

void print_array1(int *p_num, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d", p_num[i]);
    }
    printf("\n");
}

void solve() {
    
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

    int i = 2; // start from 2-digits number
    while (1) {
        int *p = (int*) malloc(i * sizeof(int));
        int *p_num = (int*) malloc(i * sizeof(int));

        for (int j = 1; j < i; j++) {
            // init pattern and pattern-number array
            for (int k = 0; k < i; k++) {
                p[k] = 0;
            }
            while (next_pattern(p, i, j) != 0) {
                for (int k = 0; k < i; k++) {
                    p_num[k] = 0;
                }
                while (next_pattern_number(p, p_num, i)) {
                    int prime_cnt = 0;
                    int primes[10];
                    int a = 0;
                    while (next_number(p, p_num, i)) {
                        //int n = is_prime(p_num, i);
                        int n = 0;
                        for (int x = 0; x < i; x++) n = 10 * n + p_num[x];
                        if (numbers[n] != 1) n = 0;
                        if (n > 0) {
                            prime_cnt++;
                            primes[a++] = n;
                            //printf("%d ", n);
                        }
                    }
                    //if (prime_cnt > 0) printf("\n");
                    if (prime_cnt == 8) {
                        printf("the prime = %d\n", primes[0]);
                        return;
                    }
                }
            }
        }

        free(p);
        free(p_num);
        i++;
    }
}

int main(int argc, char* argv) {
    solve();
    return 0;
}
