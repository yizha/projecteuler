#include <stdio.h>
#include <math.h>
#include <malloc.h>

typedef struct _node {
    int n;
    struct _node *next;
} Node;

Node *create_node(int n, Node *head) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->n = n;
    if (head == NULL) {
        node->next = NULL;
    } else {
        node->next = head;
    }
    return node;
}

int is_duplicate(Node *head, int n) {
    while (head != NULL) {
        if (head->n == n) return 1;
        head = head->next;
    }
    return 0;
}

void solve() {
    int L = 1500000/2;
    int max = floor(sqrt(L)) + 1;

    Node *nodes[L + 1];
    for (int i = 1; i < L + 1; i++) nodes[i] = NULL;

    for (int m = 2; m < max; m++) {
        for (int n = 1; n < m; n++) {
            int l = m*(m+n);
            if (l > L) break;
            int c = l + n*(n-m);
            if (is_duplicate(nodes[l], c)) continue;
            int j = l;
            int k = c;
            while (j <= L) {
                //printf("%d -> %d\n", j<<1, k);
                if (nodes[j] == NULL) {
                    nodes[j] = create_node(k, NULL);
                } else {
                    nodes[j] = create_node(k, nodes[j]);
                }
                j = j + l;
                k = k + c;
            }
            //printf("\n");
        }
    }

    int cnt = 0;
    for (int i = 1; i < L + 1; i++) {
        Node *ptr = nodes[i];
        if (ptr == NULL) continue;
        if (ptr->next == NULL) cnt++;
        /*printf("%d: ", i<<1);
        while (ptr != NULL) {
            printf("%d ", ptr->n);
            ptr = ptr->next;
        }
        printf("\n");*/
    }

    printf("count = %d\n", cnt);
}

int main(int argc, char* argv) {
    solve();
    return 0;
}
