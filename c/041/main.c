#include <stdio.h>
#include <math.h>

/*
 * 9 + 8 + 7 + 6 + ... + 2 + 1 = 45 is dividable by 3
 * 8 + 7 + 6 + ... + 2 + 1 = 36 is diviable by 3
 * so 1..9 and 1..8 pandigital are all diviable by 3, 
 * cannot be primes.
 * We only need to test pandigitals 1..7 and below
 */

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void revert(int *a, int start, int end) {
    while (start < end) swap(&a[start++], &a[end--]);
}

int to_int(int *digits, int end) {
    int n = 0;
    for (int i = end; i >= 0; i--) {
        n = 10 * n + digits[i];
    }
    return n;
}

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
    int num = 0;
    for (int n = 6; n > 0; n--) {
        
        int digits[] = {1, 2, 3, 4, 5, 6, 7};
        num = to_int(digits, n);
        //printf("num = %d\n", num);
        if (is_prime(num)) {
            printf("max pandigital prime = %d\n", num);
            return 0;
        }
        int i = 0;
        while (i < n) {
            int next = i + 1;
            if (digits[i] < digits[next]) {
                for (int j = 0; j <= i; j++) {
                    if (digits[j] < digits[next]) {
                        swap(&digits[j], &digits[next]);
                        if (i > 0) revert(digits, 0, i);
                        i = 0;
                        break;
                    }
                }
                int num = to_int(digits, n);
                //printf("num = %d\n", num);
                if (is_prime(num)) {
                    printf("max pandigital prime = %d\n", num);
                    return 0;
                }
            } else {
                i++;
            }
        }
    }
}
