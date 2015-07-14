/* https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation */
#include <stdio.h>
#include <malloc.h>

typedef struct _bigint {
    int num[120];
    int size;
} BigInt;

void _multiple(BigInt *bigint, int n) {
    int *a = bigint->num;
    int size = bigint->size;
    int overflow = 0;
    for (int i = 0; i < size; i++) {
        int t = a[i] * n + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[size++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    bigint->size = size;
}

int _add(BigInt *ba, BigInt *bb) {
    int *a = ba->num;
    int a_size = ba->size;
    int *b = bb->num;
    int b_size = bb->size;
    int overflow = 0;
    int *x;
    int min_size;
    int max_size;
    if (a_size > b_size) {
        max_size = a_size;
        min_size = b_size;
        x = a;
    } else {
        max_size = b_size;
        min_size = a_size;
        x = b;
    }
    for (int i = 0; i < min_size; i++) {
        int t = a[i] + b[i] + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    for (int i = min_size; i < max_size; i++) {
        int t = x[i] + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[max_size++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    ba->size = max_size; 
}

BigInt* create_big_num(int n) {
    BigInt *num = (BigInt*) malloc(sizeof(BigInt));
    
    return num;
}

int calc_one(int n) {
    int cnt = 0;
    int sum = 0;
    int c = n;
    int p = 0;
    int x = 0;

    int p20,sx;
    while ((cnt < 100) && (c > 0)) {
        x = 0;
        p20 = 20*p;
        sx = x*(p20+x);
        int nsx = sx;
        int nx = x;
        while (nsx < c) {
            sx = nsx;
            x = nx;
            nsx = nsx + (2*nx + p20 + 1);
            nx = nx + 1;
            if (nsx == c) {
                sx = nsx;
                x = nx;
                break;
            }
        }

        cnt = cnt + 1;
        p = 10*p + x;
        c = 100*(c-sx);
        sum = sum + x;
        printf("cnt=%d,p=%d,c=%d,x=%d,sum=%d\n",cnt,p,c,x,sum);
    }

    if (cnt < 100) {
        // non-irrational square root
        return 0;
    } else {
        // sum of the first 100 decimal digit
        // of the irrational square root
        return sum;
    }
}

int main(int argc, char* argv) {
    calc_one(3);
    return 0;
}
