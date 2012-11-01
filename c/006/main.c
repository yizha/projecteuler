#include <stdio.h>

int sum(int n) {
    return n * (n + 1) / 2;
}

int sum_sq(int n) {
    return (2 * n + 1) * (n + 1) * n / 6;
}

int main(int argc, char **argv) {
    int n = 100;
    int s = sum(n);
    printf("difference = %d\n", s * s - sum_sq(n));
    return 0;
}
