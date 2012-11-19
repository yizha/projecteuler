#include <stdio.h>
#include <math.h>
#include <malloc.h>

typedef struct _node {
    int numbers[10];
    int size;
    struct _node *next;
} node;

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

int concat(int a, int b) {
    int t = b;
    int k = 1;
    while (t > 0) {
        k = k * 10;
        t = t / 10;
    }
    return k * a + b;
}

node *new_node(node *p, int a, int b) {
    if (p == NULL) {
        p = (node*) malloc(sizeof(node));
        p->numbers[0] = a;
        p->numbers[1] = b;
        p->size = 2;
        p->next = NULL;
        return p;
    } else {
        node * np = (node*) malloc(sizeof(node));
        for (int i = 0; i < p->size; i++) {
            np->numbers[i] = p->numbers[i];
        }
        np->size = p->size;
        np->next = NULL;
        if (a > 0) {
            insert_prime(np, a);
        } 
        if (b > 0) {
            insert_prime(np, b);
        }
        return np;
    }
}

void insert_prime(node *p, int n) {
    int i = 0;
    for (; i < p->size; i++) {
        if (a < p->numbers[i]) break;
    }
    for (int j = p->size - 1; j >= i; j--) {
        p->numbers[j + 1] = p->numbers[j];
    }
    p->numbers[i] = a;
    p->size++;
}

int test(node *ptr, int a) {
    int ok = 2;
    for (int i = 0; i < ptr->idx; i++) {
        int n = ptr->numbers[i];
        if (n == a) {
            ok = 1;
            break;
        }
        int x = concat(a, n);
        if (!is_prime(x)) {
            ok = 0;
            break;
        }
        x = concat(n, a);
        if (!is_prime(x)) {
            ok = 0;
            break;
        }
    }
    return ok;
}

node *insert_node(node *head, node *np) {
    node *ptr = head;
    if (np->size > head->size) {
        np->next = head;
        head = np;
        return head;
    }
    while (ptr != NULL) {
        if (np->size < ptr->size) {
            ptr = ptr->next;
            continue;
        } else if (np->size > ptr->size) {

        }
    }
}

node *verify(node *head, int a, int b) {
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    if (head == NULL) {
        head = new_node(head, a, b);
        return head;
    } else {
        node *ptr = head;
        while (ptr != NULL) {
            int a_ok = test(ptr, a);
            int b_ok = test(ptr, b);
            if (a_ok > 0 && b_ok > 0) {
                node *np = NULL;
                if (a_ok == 1 && b_ok == 1) { // both a & b dup
                    break;
                } else if (a_ok == 1 && b_ok == 2) { // b is a new number
                    np = new_node(ptr, a, -1);
                } else if (a_ok == 2 && b_ok == 1) { // a is a new number
                    np = new_node(ptr, b, -1);
                } else { // a_ok == 2, b_ok == 2, both a & b are new numbers
                    np = new_node(ptr, a, b);
                }
            }
            ptr = ptr->next;
        }
        //node *p = create_node(a, b);
        return head;
    }
}

void solve() {
    int n = 3;
    while (1) {
        n = n + 2;
        if (!is_prime(n)) continue;
        int a = n;
        int b = 0;
        int k = 1;
        while (a > 10) {
            b = k * (a % 10) + b;
            a = a / 10;
            k = 10 * k;
            if (a == 2 || b == 2) continue;
            if (!is_prime(a) || !is_prime(b)) continue;
            int m = concat(b, a);
            if (!is_prime(m)) continue;
            verify(&heads, a, b);
            //printf("n=%d, a=%d, b=%d, m=%d\n", n, a, b, m);
        }
        //if (n > 10000) break;
    }
}

int main(int argc, char* argv) {
    /*int primes[1000000];
    for (int i = 0; i < 1000000; i++) primes[i] = 1;
    for (int i = 2; i < 1000000; i++) {
        if (primes[i]) {
            int j = i + i;
            while (j < 1000000) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }*/

    solve();
}
