#include <stdio.h>
#include <malloc.h>

int gcd(int m, int n) {
    if (m == n) return m;
    if (m > n && (m % n) == 0) return n;
    if (m < n && (n % m) == 0) return m;
    int t = m - n;
    int x = t < 0 ? -t : t;
    while (x > 1) {
        if ((m % x) == 0 && (n % x) == 0) return x;
        m = m < n ? m : n;
        n = x;
        t = m - n;
        x = t < 0 ? -t : t;
    }   
    return 1;
}

unsigned int combinations(int n, int m) {
    int size = m;
    int *a = (int*) malloc(size * sizeof(int));
    int *b = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        a[i] = n--;
        b[i] = m--;
    }
    /*
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
    */
    for (int i = 0; i < size; i++) {
        int j = 0;
        while (b[i] != 1) {
            int d = gcd(a[j], b[i]);
            if (d > 1) {
                a[j] = a[j] / d;
                b[i] = b[i] / d;
            }
            j++;
        }
    }
    /*
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
    */
    unsigned int p = 1;
    for (int i = 0; i < size; i++) {
        p = p * a[i];
    }

    free(a);
    free(b);

    return p;
}

int main(int argc, char* argv) {
    int cnt = 0;
    int target = 1000000;
    for (int i = 23; i < 101; i++) {
        int m = i / 2;
        for (int j = 1; j <= m; j++) {
            unsigned c = combinations(i, j);
            //printf("C[%d,%d]=%d\n", i, j, c);
            if (c > target) {
                cnt = cnt + ((i - j) - j + 1);
                break;
            }
        }
    }
    printf("count = %d\n", cnt);
    return 0;
}
