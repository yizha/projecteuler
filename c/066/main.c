#include <stdio.h>
#include <math.h>

int _multiply(int *a, int *b, int a_size, int b_size) {
    int t[1000] = {0};
    int size;
    for (int i = 0; i < b_size; i++) {
        int overflow = 0;
        int j = 0;
        for (; j < a_size; j++) {
            int idx = i + j;
            int n = a[j] * b[i] + overflow + t[idx];
            t[idx] = n % 10;
            overflow = n / 10;
        }
        size = i + j;
        while (overflow > 0) {
            overflow = overflow + t[size];
            t[size] = overflow % 10;
            overflow = overflow / 10;
            size++;
        }
    }
    for (int i = 0; i < size; i++) {
        a[i] = t[i];
    }
    return size;
}

int equals(int *a, int *b, int a_size, int b_size) {
    if (a_size != b_size) return 0;
    for (int i = 0; i < a_size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int is_perfect_square(int n) {
    int h = n & 0xF; // perfect square in base 16 ends in 0/1/4/5/9 only
    if (h > 9) return 0;
    if (h == 2 || h == 3 || h == 6 || h == 7 || h == 8) return 0;
    int r = floor(sqrt(n));
    if (r * r == n) return r;
    return 0;
}

int int_to_array(int n, int *a) {
    int size = 0;
    while (n > 0) {
        a[size++] = n % 10;
        n = n / 10;
    }
    return size;
}

void print_int_array(int *a, int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d", a[i]);
    }
}

int main(int argc, char* argv) {
    //printf("%u\n", 0xFFFFFFFF);
    /*int a[1000]; 
    a[0] = 9;
    a[1] = 7;
    a[2] = 6;
    a[3] = 2;
    int b[] = {3,1};
    int size = _multiply(a, a, 4, 4);
    printf("size=%d\n", size);
    printf("2679^2 =");print_int_array(a, size);
    return 0;*/

    int max_d = 0;
    int max_x = 0;
    int max_y = 0;
    int x1a[1000];
    int x2a[1000];
    int ya[1000];
    int da[5];
    int x1_size;
    int x2_size;
    int y_size;
    int d_size;
    int one[1] = {1};
    for (int d = 62; d <= 100; d++) {
        if (is_perfect_square(d)) continue;
        int y = 0;
        while (1) {
            y++;
            /*
            int t = y % 10;
            int a = (t * t * (d % 10)) % 10;
            if (a != 0 && a != 3 && a != 4 && a != 5 && a != 8 && a != 9) continue;
            */
            int x = floor(sqrt(d) * y) + 1;
            //printf("x=%d\n", x);
            x1_size = int_to_array(x + 1, x1a);
            x2_size = int_to_array(x - 1, x2a);
            y_size = int_to_array(y, ya);
            //printf("y=");print_int_array(ya, y_size);
            d_size = int_to_array(d, da);
            //printf("d=");print_int_array(da, d_size);
            x1_size = _multiply(x1a, x2a, x1_size, x2_size);
            //printf("(x+1)*(x-1)=");print_int_array(x1a, x1_size);
            y_size = _multiply(ya, ya, y_size, y_size);
            //printf("y^2=");print_int_array(ya, y_size);
            y_size = _multiply(ya, da, y_size, d_size);
            //printf("d*y^2=");print_int_array(ya, y_size);
            /*printf("x=%d,d=%d,y=%d\n", x, d, y);
            printf("(x+1)*(x-1)=");print_int_array(x1a, x1_size);
            printf("\n");
            printf("      d*y^2=");print_int_array(ya, y_size);
            printf("\n");*/
            //printf("\n");
            if (!equals(x1a, ya, x1_size, y_size)) continue;
            /*int b = (((x+1)%10)*((x-1)%10));
            if (a != b) continue;*/
            printf("%d^2-%d*%d^2=1\n", x, d, y);
            //printf("d=%d, x=%d\n",d,x);
            break;
        }
    }
    //printf("x=%llu\n",max);
}
