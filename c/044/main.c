#include <stdio.h>
#include <math.h>
#include <malloc.h>

int is_perfect_square(unsigned int n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 5 || h == 6 || h == 7 || h == 8) return 0;
    int r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

int is_pentagonal(unsigned int n) {
    unsigned int x = 1 + 24 * n;
    unsigned int r = is_perfect_square(x);
    if (r == 0) return 0;
    if ((r % 6) != 5) return 0;
    return 1;
}

typedef struct _node {
    int i;
    unsigned int n;
    struct _node *next;
} node;

node *next(node *head) {
    node *n = (node*) malloc(sizeof(node));
    n->i = head->i + 1;
    n->n = head->n + 3 * head->i + 1;
    n->next = head;
    return n;
}

node *search(node *head) {
    unsigned int k = head->n;
    node *ptr = head->next;
    while (ptr != NULL) {
        unsigned int j = ptr->n;
        unsigned int d = k - j;
        if (!is_pentagonal(d)) {
            ptr = ptr->next;
            continue;
        }
        //printf("wow\n");
        d = k + j;
        if (!is_pentagonal(d)) {
            ptr = ptr->next;
            continue;
        }
        //printf("waa\n");
        return ptr;
    }
    return NULL;
}

node *create_root() {
    node *head = (node *) malloc(sizeof(node));
    head->i = 1;
    head->n = 1;
    head->next = NULL;
    return head;
}

int main(int argc, char* argv) {
    node *head = create_root();
    node *found = NULL;
    while (found == NULL) {
        head = next(head);
        found = search(head);
    }
    printf("%d->%u, %d->%u, diff = %u, sum = %u\n", 
            head->i,head->n, found->i,found->n, head->n - found->n, head->n + found->n);
}
