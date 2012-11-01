#include <stdio.h>

// takes forever
unsigned long recursive(int x, int y, unsigned long routes) {
    if (x > 0) {
        routes = routes + recursive(x - 1, y, routes);
    }
    if (y > 0) {
        routes = routes + recursive(x, y - 1, routes);
    }
    if ((x == 0) && (y == 0)) {
        routes++;
    }
    return routes;
}

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

long long simple_math() {
    // the solution is to pickup 20 positions from total 40 positions
    int m[20];
    int n[20];
    for (int i = 0; i < 20; i++) {
        m[i] = i + 21;
        n[i] = i + 1;
    }
    for (int i = 0; i < 20; i++) {
        if (n[i] > 1) {
            for (int j = 0; j < 20; j++) {
                int d = gcd(n[i], m[j]);
                if (d > 1) {
                    n[i] = n[i] / d;
                    m[j] = m[j] / d;
                    if (n[i] == 1) break;
                }
            }
        }
    }
    unsigned long long routes = 1;
    for (int i = 0; i < 20; i++) {
        routes = routes * m[i];
    }

    printf("route count = %llu\n", routes);
    return 0;
}

int main(int argc, char* argv) {
    simple_math();
}
