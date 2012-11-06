#include <stdio.h>
#include <math.h>
#include <malloc.h>

int is_perfect_square(unsigned long long n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 5 || h == 6 || h == 7 || h == 8) return 0;
    unsigned long long r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

int is_prime(int n) {
    if (n < 2) return 0;
    if (n < 4) return 1;
    int max = floor(sqrt(n)) + 1;
    for (int i = 3; i < max; i = i + 2) {
        if ((n % i) == 0) return 0;
    }   
    return 1;
}

typedef struct _prime {
    int n;
    struct _prime *next;
} prime;

prime *add_prime(prime *head, int n) {
    prime *p = (prime*) malloc(sizeof(prime));
    p->n = n;
    if (head != NULL) {
        p->next = head;
    } else {
        p->next = NULL;
    }
    return p;
}

int qualified(int n, prime *h) {
    while (h != NULL) {
        int s = (n - h->n) / 2;
        if (s == 1) return 1;
        int r = is_perfect_square(s);
        if (r) {
            //printf("%d = %d + 2 * %d^2\n", n, h->n, r);   
            return 1;
        }
        h = h->next;
    }
    return 0;
}

int main(int argc, char* argv) {
    prime *h = add_prime(NULL, 3);
    h = add_prime(h, 5);
    h = add_prime(h, 7);

    int i = 9;
    while (1) {
        if (is_prime(i)) {
            h = add_prime(h, i);
        } else {
            if (!qualified(i, h)) {
                printf("number = %d\n", i);
                return 0;
            }
        }
        i = i + 2;
    }
    return 0;
}
