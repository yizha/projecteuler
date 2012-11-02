#include <stdio.h>

unsigned int reverse_b10(unsigned int n) {
    unsigned int rev = 0;
    while (n > 0) {
         rev = rev * 10 + (n % 10);
         n = n / 10;
    }
    return rev;
}

unsigned int reverse_b2(unsigned int n) {
    unsigned int rev = 0;
    while (n > 0) {
        rev = (rev << 1) + (n & 0x1);
        n = n >> 1;
    }
    return rev;
}

int main(int argc, char* argv) {
    long sum = 0;
    for (int i = 1; i < 1000000; i = i + 2) {
        if (i == reverse_b10(i) && i == reverse_b2(i)) sum = sum + i;
    }
    printf("sum = %ld\n", sum);
    return 0;
}
