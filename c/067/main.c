#include <stdio.h>

#define ROWS 100

void load(int (*a)[ROWS]) {
    FILE *fp = fopen("triangle.txt", "r");

    int n = 0;
    int n_flag = 0;
    int row = 0;
    int col = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            n = 10 * n + (ch - '0');
            n_flag = 1;
        } else if (n_flag) {
            a[row][col] = n;
            n = 0;
            n_flag = 0;
            col++;
            if (col - 1 == row) {
                row++;
                col = 0;
            }
        }
    }

    fclose(fp);
}

int main(int argc, char* argv) {
    int data[ROWS][ROWS];
    load(data);

    //printf("max sum = %d\n", data[0][0]);

    for (int i = ROWS - 2; i >= 0; i--) {
        int j = i + 1;
        for (int k = 0; k <= i; k++) {
            int left = data[i][k] + data[j][k];
            int right = data[i][k] + data[j][k + 1];
            data[i][k] = left > right ? left : right;
        }
    }

    printf("max sum = %d\n", data[0][0]);

    return 0;
}
