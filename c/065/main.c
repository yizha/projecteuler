#include <stdio.h>

int _multiple(int n, int *a, int size) {
    int overflow = 0;
    for (int i = 0; i < size; i++) {
        int t = a[i] * n + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[size++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    return size;
}

int _add(int *a, int *b, int a_size, int b_size) {
    int overflow = 0;
    int *x;
    int min_size;
    int max_size;
    if (a_size > b_size) {
        max_size = a_size;
        min_size = b_size;
        x = a;
    } else {
        max_size = b_size;
        min_size = a_size;
        x = b;
    }
    for (int i = 0; i < min_size; i++) {
        int t = a[i] + b[i] + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    for (int i = min_size; i < max_size; i++) {
        int t = x[i] + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    if (overflow > 0) {
        while (overflow > 0) {
            a[max_size++] = overflow % 10;
            overflow = overflow / 10;
        }
    }
    return max_size; 
}

void add_frac(int n, int *num, int *denorm, int *num_size, int *denorm_size) {
    /*int t = n * (*a) + (*b);
    *b = *a;
    *a = t;*/

    int t[1000];
    int t_size = *denorm_size;
    for (int i = 0; i < t_size; i++) {
        t[i] = denorm[i];
    }

    t_size = _multiple(n, t, t_size);
    t_size = _add(t, num, t_size, *num_size);

    for (int i = 0; i < *denorm_size; i++) {
        num[i] = denorm[i];
    }
    *num_size = *denorm_size;

    for (int i = 0; i < t_size; i++) {
        denorm[i] = t[i];
    }
    *denorm_size = t_size;
}

void calc_e(int n, int *frac, int *num, int *denorm, 
        int *num_size, int *denorm_size, int size) {
    if (n == 1) {
        num[0] = frac[0];
        denorm[0] = 1;
        *num_size = 1;
        *denorm_size = 1;
        return;
    }
    /*if (n == 1) {
        *num = 3;
        *denorm = 1;
        *num_size = 1;
        *denorm_size = 1;
        return;
    }*/
    num[0] = 1;
    denorm[0] = frac[n - 1];
    for (int i = 1; i < size; i++) {
        num[i] = 0;
        denorm[i] = 0;
    }
    *num_size = 1;
    *denorm_size = 1;

    for (int i = n - 2; i > 0; i--) {
        add_frac(frac[i], num, denorm, num_size, denorm_size);
    }

    int t[1000];
    int t_size = *denorm_size;
    for (int i = 0; i < t_size; i++) {
        t[i] = denorm[i];
    }

    t_size = _multiple(frac[0], t, t_size);
    *num_size = _add(num, t, *num_size, t_size);
}

int main(int argc, char* argv) {
    int frac[120];
    frac[0] = 2;
    int j = 1;
    int k = 1;
    for (int i = 0; i <= 102/3; i++) {
        frac[j++] = 1;
        frac[j++] = 2*(k++);
        frac[j++] = 1;
    }

    /*for (int i = 0 ; i < 101; i++) {
        printf("%d ", frac[i]);
    }
    printf("\n");
    return 0;*/

    int num[1000];
    int denorm[1000];
    int num_size = 0;
    int denorm_size = 0;
    int size = 1000;
    
    calc_e(100, frac, num, denorm, &num_size, &denorm_size, size);
    for (int i = num_size - 1; i >= 0; i--) printf("%d", num[i]);
    printf("(%d)/", num_size);
    for (int i = denorm_size - 1; i >= 0; i--) printf("%d", denorm[i]);
    printf("(%d)\n", denorm_size);
    
    /*for (int i = 1; i < 101; i++) {
        calc_e(i, frac, num, denorm, &num_size, &denorm_size, size);
        for (int i = num_size - 1; i >= 0; i--) printf("%d", num[i]);
        printf("/");
        for (int i = denorm_size - 1; i >= 0; i--) printf("%d", denorm[i]);
        printf("\n");
    }*/

    int sum = 0;
    for (int i = 0; i < num_size; i++) sum = sum + num[i];
    printf("sum=%d\n", sum);

    return 0;
}
