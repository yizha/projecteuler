#include <stdio.h>

typedef struct _prime {
    int n;
    struct _prime *next;
} prime;

int main(int argc, char* argv) {
    // find primes under 10000 
    prime* head = NULL;
    int primes[10000];
    for (int i = 0; i < 10000; i++) {
        primes[i] = 1;
    }
    for (int i = 2; i < 10000; i++) {
        if (primes[i]) {
            prime* p = (prime*) malloc(sizeof(prime));
            p->n = i;
            p->next = head;
            head = p;
            int j = i + i;
            while (j < 10000) {
                primes[j] = 0;
                j = j + i;
            }
        }
    }
    // test 4-digits numbers
    for (int i = 1111; i < 9997; i++) {
        if (primes[i] || primes[i + 1] || primes[i + 2] || primes[i + 3]) continue;
        prime *ptr = head;

    }
}
