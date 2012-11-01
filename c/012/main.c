#include <stdio.h>
#include <math.h>
#include <malloc.h>

typedef struct _prime {
    int n;
    struct _prime *next;
} s_prime;


void get_new_primes(s_prime* head, int cnt) {
    s_prime *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    int n = tail->n;
    if (n == 2) {
        n = n + 1;
    } else {
        n = n + 2;
    }
    while (cnt > 0) {
        int prime = 1;
        int m = floor(sqrt(n));
        s_prime *ptr = head;
        while (1) {
            if (ptr->n > m) break;
            if ((n % ptr->n) == 0) {
                prime = 0;
                break;
            }
            ptr = ptr->next;
            if (ptr == NULL) break;
        }
        if (prime) {
            s_prime *p = (s_prime*) malloc(sizeof(s_prime));
            p->n = n;
            p->next = NULL;
            tail->next = p;
            tail = p;
            cnt--;
        }
        n = n + 2;
    }
}

s_prime *get_primes(int cnt) {
    s_prime *p = (s_prime *) malloc(sizeof(s_prime));
    p->n = 2;
    p->next = NULL;
    get_new_primes(p, cnt - 1);
    return p;
}

int div_number(int n, s_prime *head) {
    if (n == 1) return 1;

    s_prime *prime = head;
    int p = 1;
    while (1) {
        int d = prime->n;
        int cnt = 1;
        while ((n % d) == 0) {
            n = n / d;
            cnt++;
        }
        p = p * cnt;
        if (n == 1) break;
        prime = prime->next;
        if (prime == NULL) {
            get_new_primes(head, 1000);
        }
    }
    if (p == 1) { // n is a prime number
        return 2;
    } else {
        return p;
    }
}

int main(int argc, char **argv) {
    s_prime *p = get_primes(10000);
    int n = 1;
    int f = 0;
    int f_div_num = 0;
    int a_div_num = 0;
    int b_div_num = 0;
    while (1) {
        int a = n;
        int b = n + 1;
        if ((n % 2) == 0) {
            a = a / 2;
        } else {
            b = b / 2;
        }
        if (a == f) {
            a_div_num = f_div_num;
        } else {
            a_div_num = div_number(a, p);
        }
        b_div_num = div_number(b, p);
        f = b;
        f_div_num = b_div_num;
        int div_num = a_div_num * b_div_num;
        if (div_num > 500) {
            printf("number = %d\n", a * b);
            break;
        }
        n++;
    }
}
