#include <stdio.h>
#include <math.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void revert(int *a, int start, int end) {
    while (start < end) swap(&a[start++], &a[end--]);
}

long long to_int(int *digits, int start, int end) { 
    long long n = 0; 
    for (int i = start; i <= end; i++) { 
        n = 10 * n + digits[i]; 
    }   
    return n; 
}

long long is_qualified(int *digits) {
    /*
    d2d3d4=406 is divisible by 2
    d3d4d5=063 is divisible by 3
    d4d5d6=635 is divisible by 5
    d5d6d7=357 is divisible by 7
    d6d7d8=572 is divisible by 11
    d7d8d9=728 is divisible by 13
    d8d9d10=289 is divisible by 17
    */

    int n;
    n = (int) to_int(digits, 1, 3);
    if ((n % 2) != 0) return 0;
    n = (int) to_int(digits, 2, 4);
    if ((n % 3) != 0) return 0;
    n = (int) to_int(digits, 3, 5);
    if ((n % 5) != 0) return 0;
    n = (int) to_int(digits, 4, 6);
    if ((n % 7) != 0) return 0;
    n = (int) to_int(digits, 5, 7);
    if ((n % 11) != 0) return 0;
    n = (int) to_int(digits, 6, 8);
    if ((n % 13) != 0) return 0;
    n = (int) to_int(digits, 7, 9);
    if ((n % 17) != 0) return 0;
    return to_int(digits, 0, 9);
}

int main(int argc, char* argv) {
    long long sum = 0;
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long num = is_qualified(digits);
    if (num > 0) {
        //printf("qualified number = %lld\n", num);
        sum = sum + num;
    }
    int n = 9;
    int i = n;
    while (i > 0) {
        int prev = i - 1;
        if (digits[prev] < digits[i]) {
            for (int j = n; j >= i; j--) {
                if (digits[j] > digits[prev]) {
                    swap(&digits[j], &digits[prev]);
                    if (i < n) revert(digits, i, n);
                    i = n;
                    break;
                }
            }
            num = is_qualified(digits);
            if (num > 0) {
                //printf("qualified number = %lld\n", num);
                sum = sum + num;
            }
        } else {
            i--;
        }
    }
    printf("sum = %lld\n", sum);
}
