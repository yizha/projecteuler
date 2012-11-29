/**
 * Solve Pell's Equation
 */

#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define BIGINT_MAX_SIZE 1000
#define BIGINT_BIT_MOD  10000
#define BIGINT_BIT_SIZE 4

typedef struct _bigint {
    int num[BIGINT_MAX_SIZE];
    int size;
} BigInt;

void to_bigint(int n, BigInt *a) {
    int size = 0;
    while (n > 0) {
        a->num[size++] = n % BIGINT_BIT_MOD;
        n = n / BIGINT_BIT_MOD;
    }
    a->size = size;
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

void _add(BigInt *big_a, BigInt *big_b) {
    int *a = big_a->num;
    int *b = big_b->num;
    int a_size = big_a->size;
    int b_size = big_b->size;
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
        a[i] = t % BIGINT_BIT_MOD;
        overflow = t / BIGINT_BIT_MOD;
    }
    for (int i = min_size; i < max_size; i++) {
        int t = x[i] + overflow;
        a[i] = t % BIGINT_BIT_MOD;
        overflow = t / BIGINT_BIT_MOD;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[max_size++] = overflow % BIGINT_BIT_MOD;
            overflow = overflow / BIGINT_BIT_MOD;
        }
    }
    big_a->size = max_size; 
}

int compare(BigInt *a, BigInt *b) {
    /*printf("a=");print_bigint(a);
    printf(",b=");print_bigint(b);
    printf("\n");*/
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->num[i] > b->num[i]) return 1;
        if (a->num[i] < b->num[i]) return -1;
    }
    return 0;
}

int is_perfect_square(int n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/5/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 6 || h == 7 || h == 8) return 0;
    int r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

void next_a(BigInt *big_a, int n, double n_root, int *b, int *c) {
    if ((*b) == 0) {
        int a = floor(n_root);
        *b = n - a * a;
        *c = a;
        to_bigint(a, big_a);
    } else {
        int a = floor((n_root + (*c))/(*b));
        *c = (*c) - a * (*b);
        int t = n - (*c) * (*c);
        *b = t / (*b);
        *c = -1 * (*c);
        to_bigint(a, big_a);
    }
}

int verify(BigInt *left, BigInt *right, BigInt *x, BigInt *d, BigInt *y, BigInt *one) {
    left->size = x->size;
    for (int i = 0; i < x->size; i++) {
        left->num[i] = x->num[i];
    }
    right->size = y->size;
    for (int i = 0; i < y->size; i++) {
        right->num[i] = y->num[i];
    }

    _multiply(left, left);
    //printf("left=");print_bigint(left);printf("\n");
    _multiply(right, right);
    //printf("right=");print_bigint(right);printf("\n");
    _multiply(right, d);
    //printf("right=");print_bigint(right);printf("\n");
    _add(right, one);
    //printf("right=");print_bigint(right);printf("\n");

    //int r = compare(left, right);
    //printf("compare result = %d\n", r);
    return (compare(left, right) == 0);
}

void next_frac(BigInt *big_a, BigInt **p0, BigInt **p1, BigInt **p2) {
    /*printf("p0=");print_bigint(*p0);
    printf(",p1=");print_bigint(*p1);
    printf(",p2=");print_bigint(*p2);
    printf("\n");*/
    BigInt *p;
    p = *p2;
    *p2 = *p1;
    *p1 = *p0;
    *p0 = p;
    /*printf("p0=");print_bigint(*p0);
    printf(",p1=");print_bigint(*p1);
    printf(",p2=");print_bigint(*p2);
    printf("\n");*/
    (*p0)->size = (*p1)->size;
    for (int i = 0; i < (*p1)->size; i++) {
        (*p0)->num[i] = (*p1)->num[i];
    }
    
    /*printf("p0=");print_bigint(*p0);
    printf(",p1=");print_bigint(*p1);
    printf(",p2=");print_bigint(*p2);
    printf("\n");*/
    _multiply(*p0, big_a);
    /*printf("p0=");print_bigint(*p0);
    printf(",p1=");print_bigint(*p1);
    printf(",p2=");print_bigint(*p2);
    printf("\n");*/
    _add(*p0, *p2);
    /*printf("p0=");print_bigint(*p0);
    printf(",p1=");print_bigint(*p1);
    printf(",p2=");print_bigint(*p2);
    printf("\n");*/
}

void solve() {

    BigInt *p = (BigInt*) malloc(13*sizeof(BigInt));

    BigInt *left = p;
    BigInt *right = p + 1;

    BigInt *big_d = p + 2;
    BigInt *one = p + 3;
    one->size = 1;
    one->num[0] = 1;

    BigInt *num0 = p + 4;
    BigInt *num1 = p + 5;
    BigInt *num2 = p + 6;

    BigInt *denorm0 = p + 7;
    BigInt *denorm1 = p + 8;
    BigInt *denorm2 = p + 9;

    BigInt *big_a = p + 10;

    BigInt *big_x = p + 11;
    BigInt *big_y = p + 12;
    big_x->size = 0;
    big_y->size = 0;
    int d = 0;

    for (int n = 2; n <= 1000; n++) {
        if (is_perfect_square(n)) continue;

        to_bigint(n, big_d);
        //printf("d=");print_bigint(d);printf("\n");
        double n_root = sqrt(n);
        int b = 0;
        int c = 0;

        num0->num[0] = 1;
        num0->size = 1;
        num1->num[0] = 0;
        num1->size = 1;

        denorm0->num[0] = 0;
        denorm0->size = 1;
        denorm1->num[0] = 1;
        denorm1->size = 1;       

        do {
            next_a(big_a, n, n_root, &b, &c);
            //printf("a=");print_bigint(big_a);printf("\n");
            next_frac(big_a, &num0, &num1, &num2);
            //printf("num=");print_bigint(num0);printf("\n");
            next_frac(big_a, &denorm0, &denorm1, &denorm2);
            //printf("denorm=");print_bigint(denorm0);printf("\n");
        } while (!verify(left, right, num0, big_d, denorm0, one));
        /*
        print_bigint(num0);
        printf("^2 - %d*", n);
        print_bigint(denorm0);
        printf("^2 = 1\n");
        */
        if (compare(num0, big_x) > 0) {
            big_x->size = num0->size;
            for (int i = 0; i < num0->size; i++) {
                big_x->num[i] = num0->num[i];
            }

            big_y->size = denorm0->size;
            for (int i = 0; i < denorm0->size; i++) {
                big_y->num[i] = denorm0->num[i];
            }

            d = n;
        }
    }
    
    printf("\nD=%d\n", d);
    print_bigint(big_x);
    printf("^2 - %d*", d);
    print_bigint(big_y);
    printf("^2 = 1\n");
    
    free(p);
}

int main(int argc, char* argv) {
    /*    
    int n = 10;
    double n_root = sqrt(n);
    int b = 0;
    int c = 0;

    BigInt *big_a = (BigInt*) malloc(sizeof(BigInt));
    for (int i = 0; i < 20; i++) {
        next_a(big_a, n, n_root, &b, &c);
        printf("a=");print_bigint(big_a);printf(",b=%d,c=%d\n", b, c);
        //printf("a=%d,b=%d,c=%d\n", a, b, c);
    }
    free(big_a);

    //printf("max unsigned int = %u\n", 0xFFFFFFFF);
    */

    solve();
}
