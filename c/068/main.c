#include <stdio.h>

#define SIZE 5
#define EXTERNAL {6,7,8,9,10}
#define MARKS {0,0,0,0,0}

void swap(int *a, int *b) {
    int t = *a; 
    *a = *b; 
    *b = t;
}

void revert(int *a, int start, int end) {
    while (start < end) swap(&a[start++], &a[end--]);
}

int compare(int s1[][3], int s2[][3]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 3; j++) {
            if (s1[i][j] > s2[i][j]) return 1;
            if (s1[i][j] < s2[i][j]) return -1;
        }
    }
    return 0;
}

int search(int level, int sum, int *a, int b, int *marks, int solution[][3]) {
    if (level == SIZE - 1)  { // last line
        int line = a[level] + b + solution[0][1];
        if (line == sum) {
            solution[level][0] = a[level];
            solution[level][1] = b;
            solution[level][2] = solution[0][1];
            return 1;
        } else {
            return 0;
        }
    } else {
        int c = sum - a[level] - b;
        if (c > SIZE || c < 1) return 0;
        if (marks[c - 1] == 1) return 0;
        marks[c - 1] = 1;
        solution[level][0] = a[level];
        solution[level][1] = b;
        solution[level][2] = c;
        if (search(level + 1, sum, a, c, marks, solution) == 1) { // check next line
            return 1;
        } else {
            return 0;
        }
    }
}

void scan(int sum, int *a, int *marks, int solution[][3], int max_solution[][3]) {
    for (int i = 1; i <= SIZE; i++) {
        marks[i - 1] = 1;
        int found = search(0, sum, a, i, marks, solution);
        if (found) {
            // save as max solution if it is greater
            if (compare(solution, max_solution) > 0) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < 3; k++) {
                        max_solution[j][k] = solution[j][k];
                    }
                }
            }
            // print out this solution
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    printf("%d", solution[j][k]);
                }
            }
            printf("\n");
        } else {
            // reset the marks
            for (int j = 0; j < SIZE; j++) marks[j] = 0;
        }
    }
}

int main(int argc, char* argv) {
    int a[] = EXTERNAL; // outer ring numbers
    int solution[SIZE][3]; // all solutions
    int max_solution[SIZE][3] = {0}; // the final answer
    // marks which number(s) of the inner ring are used
    int marks[] = MARKS;
    // compute the line sum
    int sum = 0;
    for (int i = 1; i <= SIZE * 2; i++) sum = sum + i; // the inner & outer ring
    for (int i = 1; i <= SIZE; i++) sum = sum + i; // the inner ring again
    sum = sum / SIZE;

    //printf("line sum = %d\n", sum);
    scan(sum, a, marks, solution, max_solution);

    // generate the permutation, and since we are looking 
    // for the max solution, so we can simply know it should
    // starts with 6, so we only need to permutate 7,8,9,10
    int cur = SIZE - 1;
    while (cur > 1) {
        int prev = cur - 1;
        if (a[cur] > a[prev]) {
            for (int j = SIZE - 1; j >= cur; j--) {
                if (a[j] > a[prev]) {
                    swap(&a[j], &a[prev]);
                    if (cur < SIZE - 1) revert(a, cur, SIZE - 1); 
                    cur = SIZE - 1;
                    break;
                }   
            }
            /*for (int j = 0; j < SIZE; j++) {
                printf("%d,", a[j]);
            }
            printf("\n");*/
            // we have the outer ring in a, we try to determin
            // the inner ring
            scan(sum, a, marks, solution, max_solution);
        } else {
            cur--;
        }   
    }

    printf("\nmax solution: ");
    for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < 3; k++) {
            printf("%d", max_solution[j][k]);
        }
    }
    printf("\n");
}
