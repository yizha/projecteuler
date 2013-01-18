#include <stdio.h>

int fact_n(int n, int *f) {
    int s = 0;
    while (n > 0) {
        s = s + f[n % 10];
        n = n / 10;
    }
    return s;
}
int count(int n, int *f) {
    int chain[100];
    int size = 0;
    chain[size++] = n;
    //printf("%d", n);
    while (1) {
        n = fact_n(n, f);
        int i = 0;
        for (; i < size; i++) {
            if (chain[i] == n) {
                //printf("(-->%d), size=%d\n", n, size);
                return size;
            }
        }
        chain[size++] = n;
        //printf("-->%d", n);
    }
}
void solve() {
    int f[] = {1,1,2,6,24,120,720,5040,40320,362880};
    int cnt = 0;
    for (int i = 1; i < 1000000; i++) {
        //int size;
        int size = count(i, f);
        if (size == 60) cnt++;
        //printf("%d --> %d\n", i, cnt);
    }
    printf("count = %d\n", cnt);
}

int main(int argc, char *argv) {
    solve();
}
