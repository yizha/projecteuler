#include <stdio.h>

int is_pandigital(int *nums, int *lens, int len) {
    int digits[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int s = 0;
    for (int i = 0; i < len; i++) {
        int n = nums[i];
        int n_len = lens[i];
        while (n > 0) {
            int d = n % 10;
            if (digits[d] == 1) return 0;
            digits[d] = 1;
            n = n / 10;
        }
        if (s == 0) {
            s = nums[i];
        } else {
            int k = 1;
            for (int j = 0; j < n_len; j++) k = k * 10;
            s = s * k + nums[i];
        }
    }
    return s;
}

int number_len(int n) {
    int len = 0;
    while (n > 0) {
        len++;
        n = n / 10;
    }
    return len;
}

int main(int argc, char *argv) {
    int max_pandigital = 0;
    int min = 100000000;
    int start_num[] = {1, 1, 12, 123, 1234};
    for (int i = 2; i < 10; i++) {
        int start = start_num[9 / i];
        int nums[i];
        int lens[i];
        while (1) {
            int num_len = 0;
            for (int j = 1; j <= i; j++) {
                int x = start * j;
                int idx = j - 1;
                nums[idx] = x;
                lens[idx] = number_len(x);
                num_len = num_len + lens[idx];
            }
            if (num_len == 9) {
                int n = is_pandigital(nums, lens, i);
                if (n > 0) {
                    if (n > max_pandigital) max_pandigital = n;
                }
            } else if (num_len > 9) {
                break;
            }
            start++;
        }
    }
    printf("max pandigital = %d\n", max_pandigital);
}
