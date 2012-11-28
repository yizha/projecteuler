#include <stdio.h>
#include <math.h>
#include <malloc.h>

typedef struct _bigint {
    int num[1000];
    int size;
} BigInt;

void _multiply(BigInt *big_a, BigInt *big_b) {
    int t[1000] = {0};
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
            t[idx] = n % 10;
            overflow = n / 10;
        }
        size = i + j;
        while (overflow > 0) {
            overflow = overflow + t[size];
            t[size] = overflow % 10;
            overflow = overflow / 10;
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
    big_a->size = max_size; 
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

int is_perfect_square(int n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/5/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 6 || h == 7 || h == 8) return 0;
    int r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

void to_bigint(int n, BigInt *a) {
    int size = 0;
    while (n > 0) {
        a->num[size++] = n % 10;
        n = n / 10;
    }
    a->size = size;
}

void print_bigint(BigInt *a) {
    for (int i = a->size - 1; i >= 0; i--) {
        printf("%d", a->num[i]);
    }
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
    for (int i = 0; i < x->size; i++) {
        left->num[i] = x->num[i];
    }
    left->size = x->size;
    for (int i = 0; i < y->size; i++) {
        right->num[i] = y->num[i];
    }
    right->size = x->size;

    _multiply(left, left);

    _multiply(right, right);
    _multiply(right, d);
    _add(right, one);

    return (compare(left, right) == 0);
}

void next_frac(BigInt *big_a, BigInt *p0, BigInt *p1, BigInt *p2) {
    BigInt *p = p2;
    p2 = p1;
    p1 = p0;
    p0 = p;
    p0->size = p1->size;
    for (int i = 0; i < p1->size; i++) {
        p0->num[i] = p1->num[i];
    }
    
    _multiply(p0, big_a);
    _add(p0, p2);
}

void solve() {

    BigInt *p = (BigInt*) malloc(11*sizeof(BigInt));

    BigInt *left = p;
    BigInt *right = p + 1;

    BigInt *d = p + 2;
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

    for (int n = 2; n <= 13; n++) {
        if (is_perfect_square(n)) continue;

        to_bigint(n, d);
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
            next_frac(big_a, num0, num1, num2);
            next_frac(big_a, denorm0, denorm1, denorm2);
        } while (verify(left, right, num0, d, denorm0, one) != 0);

        print_bigint(num0);
        printf("^2 - %d*", n);
        print_bigint(denorm0);
        printf("^2 = 1\n");
    }

    free(p);
}

int main(int argc, char* argv) {
    /*int n = 23;
    double n_root = sqrt(n);
    int b = 0;
    int c = 0;

    for (int i = 0; i < 20; i++) {
        next_a(bign, n_root, &b, &c);
        printf("a=%d,b=%d,c=%d\n", a, b, c);
    }*/

    solve();
}
