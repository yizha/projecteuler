#include <stdio.h>
#include <math.h>

int is_triangle_number(int n) {
    int s = 2 * n;
    int i = floor(sqrt(n));
    while (1) {
        int x = i * (i + 1);
        if (x > s) return 0;
        if (x == s) {
            //printf("%d = %d * (%d + 1) / 2\n", n, i, i);
            return 1;
        }
        i++;
    }
}

int main(int argc, char* argv) {
    FILE *fp = fopen("words.txt", "r");
    int ch;
    int word_num = 0;
    int first = 1;
    int cnt = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '"') {
            if (first) {
                first = 0;
            } else {
                if (is_triangle_number(word_num)) cnt++;
                first = 1;
                word_num = 0;
            }
        } else if (ch == ',') {
        } else {
            word_num = word_num + ch - 'A' + 1;
        }
    }
    printf("triangle word count = %d\n", cnt);
}
