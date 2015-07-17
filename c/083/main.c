#include <stdio.h>
#include <malloc.h>

typedef struct matrix {
    int **data;
    int size;
} Matrix;

int** create_matrix_array(int size) {
    int **a = (int**) malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        a[i] = (int*) malloc(size * sizeof(int));
    }
    return a;
}

Matrix* load_matrix(char* filename) {
    FILE *fp = fopen(filename, "r");
    // load matrix size
    int size = 0;
    char ch = fgetc(fp);
    while (ch >= '0' && ch <= '9') {
        size = 10 * size + (ch - '0');
        ch = fgetc(fp);
    } ;
    //printf("size=%d\n",size);
    // initialize matrix
    Matrix *m = (Matrix*) malloc(sizeof(Matrix));
    m->size = size;
    m->data = create_matrix_array(size);
    // load matrix data
    int **a = m->data;
    int max = size - 1;
    int n_flag = 0;
    int row = 0;
    int col = 0;
    int n = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            n = 10 * n + (ch - '0');
            n_flag = 1;
        } else if (n_flag == 1) {
            a[row][col] = n;
            n = 0;
            n_flag = 0;
            if (col == max) {
                row++;
                col = 0;
            } else {
                col++;
            }
        }
    }
    fclose(fp);

    return m;
}

void print_matrix(Matrix *m) {
    int size = m->size;
    int **a = m->data;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}

int min(int a, int b) {
    return a<b ? a : b;
}

/*
 * status:
 *  -1: unreachable
 *   0: reachable
 *   1: visited
 */
typedef struct _node {
    int row;
    int col;
    int distance;
    int status;
    struct _node *next;
} Node;

Node* insert_reachable(Node* head, Node* node) {
    // skip node which is already reachable
    // (which is already in reachable list)
    if (node->status == 0) return head;
    node->status = 0;
    if (head == NULL) return node;
    int d = node->distance;
    if (d <= head->distance) {
        node->next = head;
        return node;
    } else {
        Node *p = head;
        for (;;) {
            if (p->next == NULL) break;
            if (d <= p->next->distance) break;
            p = p->next;
        }
        node->next = p->next;
        p->next = node;
        return head;
    }
}

Node* calculate_distance(int size, Node **g, int **a, Node* h, int row, int col, int base_d) {
    // skip non-exist node
    if (row < 0 || row >= size || col < 0 || col >= size) {
        //printf("skip non-exist node at (%d,%d)!\n",row,col);
        return h;
    }
    Node *node = &g[row][col];
    // skip visited node
    if (node->status == 1) {
        //printf("skip visited node at (%d,%d)!\n",row,col);
        return h;
    }
    //printf("calculate distance for node at (%d,%d)\n",row,col);
    int d = base_d + a[row][col];
    if (node->distance == -1 || d < node->distance) {
        node->distance = d;
    }
    return insert_reachable(h, node);
}

Node* visit_node(int size, Node **g, int **a, Node *h) {
    Node *cur = h;
    h = h->next;
    int row = cur->row;
    int col = cur->col;
    int d = cur->distance;
    //printf("visiting node at (%d,%d), its distance=%d\n",row,col,d);
    h = calculate_distance(size, g, a, h, row-1, col, d); // up
    h = calculate_distance(size, g, a, h, row, col-1, d); // left
    h = calculate_distance(size, g, a, h, row+1, col, d); // down
    h = calculate_distance(size, g, a, h, row, col+1, d); // righ
    cur->status = 1;
    return h;
}

/*
 * Dijkstra Algo
 */
int main(int argc, char** argv) {

    // load the data
    Matrix *m = load_matrix("matrix.txt");
    int size = m->size;
    int **a = m->data;

    // initialize the graph and the reachable node order list
    Node **graph = (Node**) malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        graph[i] = (Node*) malloc(size * sizeof(Node));
        for (int j = 0; j < size; j++) {
            Node *node = &graph[i][j];
            node->row = i;
            node->col = j;
            node->distance = -1;
            node->status = -1;
            node->next = NULL;
        }
    }

    Node *node;
    Node *head;

    node = &graph[0][0];
    node->distance = a[0][0];
    node->status = 1;

    node = &graph[0][1];
    node->distance = a[0][0] + a[0][1];
    node->status = 0;
    head = node;

    node = &graph[1][0];
    node->distance = a[0][0] + a[1][0];

    head = insert_reachable(head, node);
    
    // calculating the mininal distance for every node in graph
    while (head != NULL) {
        head = visit_node(size, graph, a, head);
    }
    
    printf("minal path sum = %d\n",graph[size-1][size-1].distance);

    return 0;
}
