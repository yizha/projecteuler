#include <stdio.h>
#include <malloc.h>

int same_digits(int *a_d, int b, int len) {
    int b_d[] = {0,0,0,0,0,0,0,0,0,0};
    while (b > 0) {
        b_d[b % 10]++;
        b = b / 10;
    }
    for (int i = 0; i < 10; i++) {
        if (a_d[i] != b_d[i]) return 0;
    }
    return 1;
}

int main(int argc, char* argv) {
    int i = 3;
    while (1) {
        unsigned int min = 1;
        unsigned int max = 10;
        for (int j = 0; j < i - 1; j++) {
            min = min * 10;
            max = max * 10;
        }
        max = (max / 6) + 1;
        //printf("i=%d, min=%u, max=%u\n", i, min, max);

        for (unsigned int j = min; j < max; j++) {
            int digits[] = {0,0,0,0,0,0,0,0,0,0};
            unsigned int x = j;
            while (x > 0) {
                digits[x % 10]++;
                x = x / 10;
            }
            //printf("j=%u\n", j);
            unsigned int j2 = j << 1;
            //printf("j2=%u\n", j2);
            if (!same_digits(digits, j2, i)) continue;
            unsigned int j3 = j2 + j;
            //printf("j3=%u\n", j3);
            if (!same_digits(digits, j3, i)) continue;
            unsigned int j4 = j << 2;
            //printf("j4=%u\n", j4);
            if (!same_digits(digits, j4, i)) continue;
            unsigned int j5 = j4 + j;
            //printf("j5=%u\n", j5);
            if (!same_digits(digits, j5, i)) continue;
            unsigned int j6 = j3 << 1; 
            //printf("j6=%u\n", j6);
            if (!same_digits(digits, j6, i)) continue;
            printf("number = %u\n", j);
            return 0;
        }
        
        i++;
    }

    return 0;
}
