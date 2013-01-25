#include <stdio.h>

#define TOP 100001 
#define DIV 1000000

void solve() {
    int cache[TOP];

    for (int i = 1; i < TOP; i++) cache[i] = 0;
    cache[0] = 1;

    for (int i = 1; i < TOP; i++) {
        for (int j = i; j < TOP; j++) {
            cache[j] = (cache[j] + cache[j - i]) % DIV;
        }
        //printf("%d --> %d\n", i, cache[i]);

        if ((cache[i] % DIV) == 0) {
            printf("%d --> %d\n", i, cache[i]);
            break;
        }
    }
}

int main(int argc, char* argv) {
    solve();
    return 0;
}
