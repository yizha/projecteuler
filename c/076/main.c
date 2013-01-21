#include <stdio.h>

#define CACHE_LIMIT 101

int cache[CACHE_LIMIT][CACHE_LIMIT];

int cnt_summations(int, int);

int cnt_full_summations(int n, int max_slots) {
    if (n < max_slots) max_slots = n;
    int cnt = 0;
    for (int i = 1; i <= max_slots; i++) {
        cnt = cnt + cnt_summations(n, i);
    }
    return cnt;
}

int cnt_summations(int n, int slots) {
    if (n < slots) slots = n;
    int cnt = cache[n][slots];
    if (cnt == 0) {
        if (slots <= 1 || (n == slots)) {
            cnt = 1;
        } else if (slots == 2) {
            cnt = n/2;
        } else {
            int left = n - slots;
            cnt = cnt_full_summations(left, slots);
        }
        cache[n][slots] = cnt;
    }
    return cnt;
}

void solve() {
    /*printf("6->1: %d\n", cnt_summations(6,1));
    printf("6->2: %d\n", cnt_summations(6,2));
    printf("6->3: %d\n", cnt_summations(6,3));
    printf("6->4: %d\n", cnt_summations(6,4));
    printf("6->5: %d\n", cnt_summations(6,5));
    printf("6->6: %d\n", cnt_summations(6,6));*/

    // init cache
    for (int i = 0; i < CACHE_LIMIT; i++) {
        for (int j = 0; j < CACHE_LIMIT; j++) {
            cache[i][j] = 0;
        }
    }

    printf("summation count of %d --> %d\n", 100, cnt_full_summations(100, 100) - 1);
}

int main(int argc, char* argv) {
    solve();
    return 0;
}
