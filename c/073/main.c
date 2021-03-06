#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define LIMIT 12001

int count(int n, int* nums, int* primes) {
    int min = n/3 + 1;
    int max = (n%2) == 0 ? n/2 : n/2 + 1;
    int cnt = max - min;
    if (nums[n]) return cnt;
    int *x = (int*) malloc(cnt*sizeof(int));
    int j = 0;
    for (int i = min; i < max; i++) x[j++] = i;
    int r = floor(sqrt(n)) + 1;
    int i = 0;
    int p = primes[i++];
    while (p <= r) {
        if ((n % p) == 0) {
            while ((n % p) == 0) n = n / p;
            for (int j = 0; j < cnt; j++) {
                if (x[j] != 0 && (x[j] % p) == 0) x[j] = 0;
            }
        }
        p = primes[i++];
    }
    if (n > 1) {
        for (int j = 0; j < cnt; j++) {
            if (x[j] != 0 && (x[j] % n) == 0) x[j] = 0;
        }
    }
    int n_cnt = 0;
    for (int j = 0; j < cnt; j++) {
        if (x[j] != 0) n_cnt++;
    }
    free(x);
    return n_cnt;
}

int solve() {
    int nums[LIMIT];
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

    int sum = 0;
    for (int i = 2; i < LIMIT; i++) {
        sum = sum + count(i, nums, primes);
    }
    printf("sum = %d\n", sum);
}

/**
 * recursive Stern-Brocot tree
 */
int countSB(int limit, int left, int right) {
    int med = left + right;
    if (med > limit) return 0;
    int cnt = 1;
    cnt = cnt + countSB(limit, left, med);
    cnt = cnt + countSB(limit, med, right);
    return cnt;
}
int solve1() {
    int cnt = countSB(12000, 3, 2);
    printf("count = %d\n", cnt);
}

/**
 * non-recursive Stern-Brocot tree
 */
int solve2() {
    int limit = 12000;
    int cnt = 0;
    int top = 0;
    int stack[12000/2];
    int left = 3;
    int right = 2;
    while (1) {
        int med = left + right;
        if (med > limit) {
            if (top > 0) {
                left = right;
                top--;
                right = stack[top];
            } else {
                break;
            }
        } else {
            cnt = cnt + 1;
            stack[top] = right;
            top++;
            right = med;
        }
    }
    printf("count = %d\n", cnt);
}

int main(int argc, char* argv) {
    //solve();
    //solve1();
    solve2();
}
