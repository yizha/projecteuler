#include <stdio.h>
#include <malloc.h>

typedef struct _node {
    int digits[10];
    unsigned long long numbers[10];
    int cnt;
    struct _node *next;
} Node;

int equals(int *d1, int *d2) {
    for (int i = 0; i < 10; i++) {
        if (d1[i] != d2[i]) return 0;
    }
    return 1;
}

void to_digits(unsigned long long n, int *digits) {
    for (int i = 0; i < 10; i++) digits[i] = 0;
    while (n > 0) {
        digits[n % 10]++;
        n = n / 10;
    }
}

Node *create_node(unsigned long long i) {
    unsigned long long n = i*i*i;
    Node *node = (Node*) malloc(sizeof(Node));
    to_digits(n, node->digits);
    node->numbers[0] = i;
    node->cnt = 1;
    node->next = NULL;
}

Node *add(Node *head, unsigned long long i, int target) {
    Node *ptr = head;
    unsigned long long n = i*i*i;
    int digits[10] = {0,0,0,0,0,0,0,0,0,0};
    to_digits(n, digits);
    while (1) {
        if (equals(digits, ptr->digits)) {
            ptr->numbers[ptr->cnt++] = i;
            if (ptr->cnt == target) {
                return ptr;
            } else {
                return NULL;
            }
        }
        if (ptr->next == NULL) break;
        ptr = ptr->next;
    }
    Node *node = (Node*) malloc(sizeof(Node));
    for (int i = 0; i < 10; i++) node->digits[i] = digits[i];
    node->numbers[0] = i;
    node->cnt = 1;
    node->next = NULL;
    ptr->next = node;
    return NULL;
}

int main(int argc, char* argv) {
    unsigned long long i = 345;
    Node *head = create_node(i);
    Node *node;
    i++;
    while (1) {
        node = add(head, i, 5);
        if (node != NULL) break;
        i++;
    }

    /*
    for (int i = 0; i < 10; i++) {
        printf("%d->%d,", i, node->digits[i]);
    }
    printf("\n");
    */
    for (int i = 0; i < node->cnt; i++) {
        unsigned long long k = node->numbers[i];
        unsigned long long n = k*k*k;
        printf("%llu -> %llu\n", k, n);
    }
    
    /*
    printf("%llu\n", 0xFFFFFFFFFFFFFFFF);
    unsigned long long i = 2048L;
    unsigned long long n = i*i*i;
    printf("%llu\n", n);
    */
}
