#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
    long long n = 600851475143L;
    long long lf = 1;
    if ((n%2) == 0) {
        lf = 2;
        n = n/2;
        while ((n%2) == 0) n = n/2;
    }

    long long f = 3;
    long long mf = (long long) sqrt(n);
    while ((n > 1) && (f < mf)) {
        if ((n%f) == 0) {
            lf = f;
            n = n/f;
            while ((n%f) == 0) n = n/f;
            mf = (long long) sqrt(n);
        }
        f = f + 2;
    }

    if (n > lf) {
        printf("max prime factor = %lld\n", n);
    } else {
        printf("max prime factor = %lld\n", lf);
    }
    return 0;
}
