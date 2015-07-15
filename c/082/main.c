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

int main(int argc, char** argv) {
    Matrix *m = load_matrix("matrix.txt");
    int max = m->size - 1;
    int **a = m->data;
    int **path_sum = create_matrix_array(m->size);
    
    // left --> right
    for (int col = 0; col <= max; col++) {
        if (col == 0) {
            for (int row = 0; row <= max; row++) {
                path_sum[row][col] = a[row][col];
            }
        } else {
            // top --> bottom 
            for (int row = 0; row <= max; row++) {
                if (row == 0) {
                    path_sum[row][col] = path_sum[row][col-1] + a[row][col];
                } else {
                    path_sum[row][col] = a[row][col] + min(path_sum[row][col-1],path_sum[row-1][col]);
                }
            }
            // bottom --> top 
            for (int row = max - 1; row >= 0; row--) {
                path_sum[row][col] = min(path_sum[row][col], path_sum[row+1][col] + a[row][col]);
            }
        }
    }

    int col = max;
    int min_path_sum = path_sum[0][col];
    for (int row = 1; row <= max; row++) {
        min_path_sum = min(min_path_sum,path_sum[row][col]);
    }
    printf("minal path sum = %d\n",min_path_sum);

    return 0;
}
