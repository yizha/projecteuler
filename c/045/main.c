#include <stdio.h>
#include <math.h>

/*
 * Hexagonal numbers are Triangle numbers,
 * so we can simply generate next Hexagonal number
 * and test if it is also a Pentagonal number.
 * Also 
 * H[n+1] - H[n] = (n+1)(2(n+1)-1) - n(2n-1)
 *               = 4n + 1
 * So we can get next Hexagonal number by:
 * H[n+1] = H[n] + n<<2 + 1
 * which should be fast.
 */

int is_perfect_square(unsigned long long n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 5 || h == 6 || h == 7 || h == 8) return 0;
    unsigned long long r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

int is_pentagonal(unsigned long long n) {
    unsigned long long x = 1 + 24 * n;
    unsigned long long r = is_perfect_square(x);
    if (r == 0) return 0;
    if ((r % 6) != 5) return 0;
    return 1;
}

int main(int argc, char* argv) {
    int i = 143;
    unsigned long long n = 40755;
    while (1) {
        n = n + (i<<2) + 1;
        if (is_pentagonal(n)) {
            printf("number = %d\n", n);
            break;
        }
        i++;
    }
    return 0;
}
