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

void fast() {
    int partition[TOP];

    for (int i = 1; i < TOP; i++) partition[i] = 0;
    partition[0] = 1;

    for (int i = 1; i < TOP; i++) {
        int part_n = 0;
        int pentagon = 0;
        int k = 1;
        while (1) {
            pentagon = pentagon + ((k<<1) - 1);
            if (pentagon > i) break;
            int x = k & 1;
            if (x == 1) {
                part_n = part_n + partition[i - pentagon];
            } else {
                part_n = part_n + DIV - partition[i - pentagon];
            }
            if (part_n > DIV) part_n = part_n - DIV;

            pentagon = pentagon + k;
            if (pentagon > i) break;
            if (x == 1) {
                part_n = part_n + partition[i - pentagon];
            } else {
                part_n = part_n + DIV - partition[i - pentagon];
            }
            if (part_n > DIV) part_n = part_n - DIV;

            k++;
        }
        //if (part_n > DIV) part_n = part_n - DIV;
        partition[i] = part_n;
        //printf("%d --> %d\n", i, part_n);
        if (part_n == DIV) {
            printf("%d --> %d\n", i, part_n);
            break;
        }
    }
}

int main(int argc, char* argv) {
    //solve();
    fast();
    return 0;
}
