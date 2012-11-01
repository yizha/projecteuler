#include <stdio.h>
#include <malloc.h>
#include "uthash.h"

typedef struct _node {
    unsigned long n;
    struct _node *next;
} node;

typedef struct _hash {
    int n;
    int steps;
    UT_hash_handle hh;
} hash;

int _get(hash **ht, int n) {
    hash *e;
    HASH_FIND_INT(*ht, &n, e);
    if (e == NULL) {
        return 0;
    } else {
        return e->steps;
    }
}

void _set(hash **ht, int n, int steps) {
    hash *e;
    HASH_FIND_INT(*ht, &n, e);
    if (e == NULL) {
        e = (hash*) malloc(sizeof(hash));
        e->n = n;
        HASH_ADD_INT(*ht, n, e);
    } else {
        //printf("oops, key = %d, value %d --> %d \n", n, e->steps, steps);
    }
    e->steps = steps;
}

node *create_node(unsigned long n) {
    node *head = (node*) malloc(sizeof(node));
    head->n = n;
    head->next = NULL;
    return head;
}

node *next_number(node *head) {
    unsigned long n = head->n;
    if ((n % 2) == 0) {
        n = n / 2;
    } else {
        n = 3 * n + 1;
    }
    node *r = (node*) malloc(sizeof(node));
    r->n = n;
    r->next = head;
    return r;
}

void complicated() {
    hash *ht = NULL;

    _set(&ht, 1, 1);

    int n = 0;
    int max_steps = 0;
    for (int i = 2; i < 1000000; i++) {
        if (_get(&ht, i) > 0) continue;
        node *head = create_node(i);
        while (head->n > 1) {
            head = next_number(head);
            if (_get(&ht, head->n) > 0) break;
        }
        
        int base_steps = _get(&ht, head->n);
        node *ptr = head->next;
        int step = 1;
        while (1) {
            if (ptr == NULL) break;
            _set(&ht, ptr->n, base_steps + (step++));
            ptr = ptr->next;
        }
        while (1) {
            node *p = head;
            head = head->next;
            free(p);
            if (head == NULL) break;
        }
        int i_steps = _get(&ht, i);
        if (i_steps > max_steps) {
            max_steps = i_steps;
            n = i;
        }
    }

    printf("number (steps) = %d (%d)\n", n, max_steps);
}

void easy() {

    int max_n = 0;
    int max_steps = 0;

    for (int i = 1; i < 1000000; i++) {
    
        int steps = 1;
        unsigned long n = i;
        while (n > 1) {
            if ((n % 2) == 0) {
                n = n / 2;
            } else {
                n = n * 3 + 1;
            }
            steps++;
        }

        if (steps > max_steps) {
            max_n = i;
            max_steps = steps;
        }
    }

    printf("number (steps) = %d (%d)\n", max_n, max_steps);
}

int main(int argc, char **argv) {
    //complicated();
    easy();
}
