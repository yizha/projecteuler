#include <stdio.h>
#include <math.h>

/*
 * a + (sqrt(n) + c)/b
 */

int period(int n, int a, int b, int c) {
    double n_root = sqrt(n);
    int new_a = a;
    int new_b = b;
    int new_c = c;
    int cnt = 1;

    while (1) {
        new_a = floor(new_b / (n_root + new_c));
        int t = n - new_c*new_c;
        if ((t % new_b) != 0) printf("too bad, %d/%d\n", t, new_b);
        new_b = t / new_b;
        new_c = -1 * new_c;
        new_c = new_c - new_a * new_b;
        if (new_a == a && new_b == b && new_c == c) {
            break;
        } else {
            cnt++;
        }
    }
    return cnt;
}

int main(int argc, char* argv) {
    //printf("%d\n", period(3, 1, 2, -1));

    int squares[10001];
    for (int i = 2; i <= 10000; i++) squares[i] = 0;
    for (int i = 2; i < 101; i++) squares[i*i] = 1;

    int cnt = 0;
    for (int n = 2; n <= 10000; n++) {
        if (squares[n]) continue;
        double n_root = sqrt(n);
        int n_root_int = floor(n_root);
        int a = floor(1 / (n_root - n_root_int));
        int b = n - n_root_int*n_root_int;
        int c = n_root_int - a*b;
        //printf("n=%d, a=%d, b=%d, c=%d\n", n, a, b, c);
        int p = period(n, a, b, c);
        //printf("n=%d,period=%d\n", n , p);
        if ((p % 2) == 1) cnt++;
    }

    printf("count=%d\n", cnt);
}
