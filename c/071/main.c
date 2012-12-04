#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define LIMIT 1000000

#define BIGINT_MAX_SIZE 1000
#define BIGINT_BIT_MOD  10000
#define BIGINT_BIT_SIZE 4

typedef struct _bigint {
    int num[BIGINT_MAX_SIZE];
    int size;
} BigInt;

void swap(BigInt **a, BigInt **b) {
    BigInt *t;
    t = *a;
    *a = *b;
    *b = t;
}

int int_size(int n) {
    int size = 0;
    while (n > 0) {
        size++;
        n = n / 10;
    }
    return size;
}

void print_bigint(BigInt *a) { 
    printf("%d", a->num[a->size - 1]); 
    for (int i = a->size - 2; i >= 0; i--) { 
        for (int j = 0; j < BIGINT_BIT_SIZE - int_size(a->num[i]); j++) printf("0"); 
        printf("%d", a->num[i]); 
    }
}

void to_bigint(int n, BigInt *a) {
    int size = 0;
    while (n > 0) {
        a->num[size++] = n % BIGINT_BIT_MOD;
        n = n / BIGINT_BIT_MOD;
    }   
    a->size = size;
}

void copy_to(BigInt *dest, BigInt *src) {
    for (int i = 0; i < src->size; i++) {
        dest->num[i] = src->num[i];
    }
    dest->size = src->size;
}

void _multiply(BigInt *big_a, BigInt *big_b) {
    int t[BIGINT_MAX_SIZE] = {0};
    int size;
    int *a = big_a->num;
    int *b = big_b->num;
    int a_size = big_a->size;
    int b_size = big_b->size;
    for (int i = 0; i < b_size; i++) {
        int overflow = 0;
        int j = 0;
        for (; j < a_size; j++) {
            int idx = i + j;
            int n = a[j] * b[i] + overflow + t[idx];
            t[idx] = n % BIGINT_BIT_MOD;
            overflow = n / BIGINT_BIT_MOD;
        }
        size = i + j;
        while (overflow > 0) {
            overflow = overflow + t[size];
            t[size] = overflow % BIGINT_BIT_MOD;
            overflow = overflow / BIGINT_BIT_MOD;
            size++;
        }
    }
    for (int i = 0; i < size; i++) {
        a[i] = t[i];
    }
    big_a->size = size;
}

int compare(BigInt *a, BigInt *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->num[i] > b->num[i]) return 1;
        if (a->num[i] < b->num[i]) return -1;
    }
    return 0;
}

int prime_numerator(int n, int d, int *nums, int *primes) {
    if (((d % n) != 0) && nums[n]) return n;
    //int root = floor(sqrt(d)) + 1;
    //root = root > n ? n : root;
    int i = 0;
    int p = primes[i++];
    while (p <= n) {
        //printf("i=%d,n=%d,p=%d\n",i,n,p);
        if ((n % p) == 0 && (d % p) == 0) {
            n--;
            i = 0;
        }
        p = primes[i++];
    }
    return n;
}

void solve() {
    int nums[LIMIT];
    for (int i = 0; i < LIMIT; i++) nums[i] = 1;
    int p_cnt = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i]) {
            p_cnt++;
            int j = i + i;
            while (j < LIMIT) {
                nums[j] = 0;
                j = j + i;
            }
        }
    }
    int *primes = (int*) malloc(p_cnt * sizeof(int));
    int j = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (nums[i]) primes[j++] = i;
    }
    //printf("prime cnt = %d\n", p_cnt);
    //printf("p = %d\n", primes[7704]);
    
    BigInt *ptr = (BigInt*) malloc(6 * sizeof(BigInt));
    BigInt *numerator = ptr;
    BigInt *denominator = ptr + 1;
    BigInt *big_num = ptr + 2;
    BigInt *big_denom = ptr + 3;
    BigInt *tmp_num = ptr + 4;
    BigInt *tmp_denom = ptr + 5;

    numerator->size = 1;
    numerator->num[0] = 2;
    denominator->size = 1;
    denominator->num[0] = 5;
    for (int i = 8; i <= LIMIT; i++) {
        int n = (i * 3)/7;
        //printf("%d/%d --> ", n, i);
        n = prime_numerator(n, i, nums, primes);
        //printf("%d/%d\n", n, i);
        to_bigint(n, big_num);
        to_bigint(i, big_denom);
        copy_to(tmp_num, big_num);
        copy_to(tmp_denom, big_denom);

        _multiply(tmp_num, denominator);
        _multiply(tmp_denom, numerator);
        //printf("%d/%d, ", n, i);
        //print_bigint(numerator);printf("/");print_bigint(denominator);
        //printf(" --> ");
        //print_bigint(tmp_num);printf("|");print_bigint(tmp_denom);
        int x = compare(tmp_num, tmp_denom);
        //printf(":%d  ", x);
        if (x > 0) {
            swap(&numerator, &big_num);
            swap(&denominator, &big_denom);
        }
        //print_bigint(numerator);printf("/");print_bigint(denominator);
        //printf("\n");
    }

    free(primes);
    free(ptr);

    print_bigint(numerator);
    printf("/");
    print_bigint(denominator);
    printf("\n");
}

void official_solve() {
    int n = 1000000;
    int a = 3;
    int b = 7;
    for (int i = 0; i < b; i++) {
        int q = n - i;
        int p = (a*q - 1) / b;
        int r = (a*q - b*p);
        //printf("%d/%d, r=%d\n", p, q, r);
        if (r == 1) {
            printf("%d/%d\n", p, q);
            return;
        }
    }
}

int main(int argc, char* argv) {
    //solve();
    official_solve();
}
