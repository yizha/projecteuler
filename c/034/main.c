#include <stdio.h>

int main(int argc, char* argv) {
    int f[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362800};
    int sum = 0;
    for (int i = 11; i < 9999999; i++) {
        int n = i;
        int s = 0;
        while (n > 0) {
            s = s + f[n % 10];
            n = n / 10;
        }
        if (i == s) sum = sum + i;
    }

    printf("sum = %d\n", sum);
}
