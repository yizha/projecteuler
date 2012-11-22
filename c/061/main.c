#include <stdio.h>

/*
 *
 * Triangle     P3,n=n(n+1)/2       1, 3, 6,  10, 15, ...  -->  n=45~140, 96
 * Square       P4,n=n^2            1, 4, 9,  16, 25, ...  -->  n=32~99,  68
 * Pentagonal   P5,n=n(3n-1)/2      1, 5, 12, 22, 35, ...  -->  n=26~81,  56
 * Hexagonal    P6,n=n(2n-1)        1, 6, 15, 28, 45, ...  -->  n=23~70,  48
 * Heptagonal   P7,n=n(5n-3)/2      1, 7, 18, 34, 55, ...  -->  n=21~63,  43
 * Octagonal    P8,n=n(3n-2)        1, 8, 21, 40, 65, ...  -->  n=19~58,  40
 */

typedef struct _node {
    int head;
    int cnt;
    int tail[100];
    int type[100];
} Node;

int search(int level, int *parts, Node *nodes, int *marks) {
    if (level == 6) {
        if (parts[6] == parts[0]) {
            return 1;
        } else {
            return 0;
        }
    }
    Node *node = nodes + parts[level];
    int cnt = node->cnt;
    int new_level = level + 1;
    for (int i = 0; i < cnt; i++) {
        int type = node->type[i];
        if (marks[type]) continue;
        int tail = node->tail[i];
        marks[type] = new_level;
        parts[new_level] = tail;
        if (search(new_level, parts, nodes, marks)) {
            return 1;
        }
        marks[type] = 0;
    }
    return 0;
}

void print_nodes(Node *nodes) {
    for (int i = 0; i < 100; i++) {
        Node *node = nodes + i;
        printf("%d --> ", node->head);
        int cnt = node->cnt;
        for (int j = 0; j < cnt; j++) {
            printf("%d(%d) ", node->tail[j], node->type[j]);
        }
        printf("\n");
    }
}

void fill_nodes(Node *nodes) {
    // init
    for (int i = 10; i < 100; i++) {
        Node *node = nodes + i;
        node->head = i;
        for (int j = 0; j < 100; j++) {
            node->tail[j] = 0;
            node->type[j] = -1;
        }
        node->cnt = 0;
    }
    // Triangle     P3,n=n(n+1)/2       1, 3, 6,  10, 15, ...  -->  n=45~140, 96
    int k = 0;
    for (int i = 45; i <= 140; i++) {
        int n = i*(i+1)/2;
        int head = n / 100;
        int tail = n % 100;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    // Square       P4,n=n^2            1, 4, 9,  16, 25, ...  -->  n=32~99,  68
    for (int i = 32; i <= 99; i++) {
        int n = i*i;
        int head = n / 100;
        int tail = n % 100;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    // Pentagonal   P5,n=n(3n-1)/2      1, 5, 12, 22, 35, ...  -->  n=26~81,  56
    for (int i = 26; i <= 81; i++) {
        int n = i*(3*i-1)/2;
        int head = n / 100;
        int tail = n % 100;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    // Hexagonal    P6,n=n(2n-1)        1, 6, 15, 28, 45, ...  -->  n=23~70,  48
    for (int i = 23; i <= 70; i++) {
        int n = i*(2*i-1);
        int head = n / 100;
        int tail = n % 100;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    // Heptagonal   P7,n=n(5n-3)/2      1, 7, 18, 34, 55, ...  -->  n=21~63,  43
    for (int i = 21; i <= 63; i++) {
        int n = i*(5*i-3)/2;
        int head = n / 100;
        int tail = n % 100;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    // Octagonal    P8,n=n(3n-2)        1, 8, 21, 40, 65, ...  -->  n=19~58,  40
    /*
    for (int i = 19; i <= 58; i++) {
        int n = i*(3*i-2);
        int head = n / 100;
        int tail = n % 100;
        int idx = i - 19;
        oct_head[idx] = head;
        oct_tail[idx] = tail;
        Node *node = nodes + head;
        node->tail[node->cnt] = tail;
        node->type[node->cnt] = k;
        node->cnt++;
    }
    k++;
    */
}

int main(int argc, char* argv) {
    Node nodes[100];
    fill_nodes(nodes);
    //print_nodes(nodes);
    //return 0;

    int oct_head[40];
    int oct_tail[40];
    for (int i = 19; i <= 58; i++) {
        int n = i*(3*i-2);
        int head = n / 100;
        int tail = n % 100;
        int idx = i - 19;
        oct_head[idx] = head;
        oct_tail[idx] = tail;
    }

    int level;
    int parts[7];
    int marks[6];
    for (int i = 0; i < 40; i++) {
        if (oct_tail[i] < 10) continue;
        level = 1;
        parts[0] = oct_head[i];
        parts[1] = oct_tail[i];
        for (int j = 0; j < 5; j++) marks[j] = 0;
        marks[5] = 1;
        if (search(level, parts, nodes, marks)) {
            //printf("woo\n");
            break;
        }
    }

    /*for (int i = 0; i < 7; i++) {
        printf("%d ", parts[i]);
    }
    printf("\n");
    for (int i = 0; i < 6; i++) {
        printf("%d ", marks[i]);
    }
    printf("\n");*/

    int cyclic[6];
    int sum = 0 ;
    for (int i = 0; i < 6; i++) {
        cyclic[i] = 100 * parts[i] + parts[i + 1];
        sum = sum + cyclic[i];
        int j = 0;
        for (; j < 6; j++) {
            if (marks[j] == (i + 1)) break;
        }
        printf("%d(P%d)",cyclic[i], j+3);
        if (i < 5) printf(",");
    }
    printf("\n");
    printf("sum=%d\n", sum);

    return 0;
}
