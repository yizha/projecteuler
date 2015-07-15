/* https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation */
#include <stdio.h>
#include <malloc.h>

typedef struct _bigint {
    int num[120];
    int size;
} BigInt;

void _shift_left(BigInt *bi, int cnt) {
    if ((bi->size == 1) && (bi->num[0] == 0)) return;
    bi->size = bi->size + cnt;
    int *a = bi->num;
    for (int i = bi->size - 1; i >= cnt; i--) {
        a[i] = a[i - cnt];
    }
    for (int i = cnt - 1; i >= 0; i--) {
        a[i] = 0;
    }
}

void _multiply_n(BigInt *bi, int n) {
    int *a = bi->num;
    int size = bi->size;
    int overflow = 0;
    for (int i = 0; i < size; i++) {
        int t = a[i] * n + overflow;
        a[i] = t % 10;
        overflow = t / 10;
    }
    while (overflow > 0) {
        a[size++] = overflow % 10;
        overflow = overflow / 10;
    }
    size = size - 1;
    while ((a[size] == 0) && (size > 0)) size--;
    bi->size = size + 1;
}

void _add_n(BigInt *bi, int n) {
    int *a = bi->num;
    int size = bi->size;
    int overflow = 0;
    int i = 0;
    int t = a[i] + n;
    a[i] = t % 10;
    overflow = t / 10;
    i = i + 1;
    while ((overflow > 0) && (i < size)) {
        t = a[i] + overflow;
        a[i] = t % 10;
        overflow = t / 10;
        i = i + 1;
    }
    while (overflow > 0) {
        a[size++] = overflow % 10;
        overflow = overflow / 10;
    }
    bi->size = size;
}

void _add_bi(BigInt *ba, BigInt *bb) {
    int *a = ba->num;
    int a_size = ba->size;
    int *b = bb->num;
    int b_size = bb->size;
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
    while (overflow > 0) {
        a[max_size++] = overflow % 10;
        overflow = overflow / 10;
    }
    ba->size = max_size; 
}

void _sub_bi(BigInt *ba, BigInt *bb) {
    int *a = ba->num;
    int a_size = ba->size;
    int *b = bb->num;
    int b_size = bb->size;
    int underflow = 0;
    int i = 0;
    for (; i < b_size; i++) {
        int t = a[i] - b[i] - underflow;
        if (t < 0) {
            t = 10 + t;
            underflow = 1;
        } else {
            underflow = 0;
        }
        a[i] = t;
    }
    while ((underflow > 0) && (i < a_size)) {
        int t = a[i] - underflow;
        if (t < 0) {
            t = 10 + t;
            underflow = 1;
        } else {
            underflow = 0;
        }
        a[i] = t;
        i = i + 1;
    }
    if (underflow > 0) printf("underflow is not zero!!!");
    int size = a_size - 1;
    while ((a[size] == 0) && (size >= 0)) size--;
    ba->size = size + 1;
}

void _set_bi(BigInt *bi, int n) {
    int *a = bi->num;
    a[0] = 0;
    bi->size = 1;
    if (n > 0) {
        int i = 0;
        while (n > 0) {
            a[i++] = n % 10;
            n = n / 10;
        }
        bi->size = i;
    }
}

void _copy_bi(BigInt *ba, BigInt *bb) {
    int *a = ba->num;
    int *b = bb->num;
    int b_size = bb->size;
    for (int i = 0; i < b_size; i++) {
        a[i] = b[i];
    }
    ba->size = b_size;
}

int _compare_bi(BigInt *ba, BigInt *bb) {
    int a_size = ba->size;
    int b_size = bb->size;
    if (a_size > b_size) return 1;
    if (a_size < b_size) return -1;
    int *a = ba->num;
    int *b = bb->num;
    for (int i = a_size - 1; i >= 0; i--) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

int _is_zero(BigInt *bi) {
    if ((bi->size == 1) && (bi->num[0] == 0)) {
        return 1;
    } else {
        return 0;
    }
}

BigInt* create_bigint() {
    return (BigInt*) malloc(sizeof(BigInt));
}

BigInt *c;
BigInt *p;
BigInt *p20;
BigInt *sx;
BigInt *nsx;
BigInt *tmp;

void init() {
    c   = create_bigint();
    p   = create_bigint();
    p20 = create_bigint();
    sx  = create_bigint();
    nsx = create_bigint();
    tmp = create_bigint();
}

void print_bi(BigInt *bi) {
    int *n = bi->num;
    int i = bi->size - 1;
    while (i >= 0) {
        printf("%d",n[i--]);
    }
    printf("\n");
}

int calc_one(int n) {
    int cnt = 0;
    int sum = 0;
    int x = 0;
    _set_bi(c, n);
    _set_bi(p, 0);

    int term = 0;
    while ((cnt < 100) && (_is_zero(c) == 0)) {
        x = 0;
        // p20 = 20*p
        _copy_bi(p20, p);
        _multiply_n(p20, 2);
        _shift_left(p20, 1);
        // sx = x*(p20 + x)
        _copy_bi(sx, p20);
        _add_n(sx, x);
        _multiply_n(sx, x);
        // nsx = sx
        _copy_bi(nsx, sx);
        int nx = x;
        while (_compare_bi(nsx, c) < 0) {
            _copy_bi(sx, nsx);
            x = nx;
            // nsx + (2*nx + p20 + 1);
            _copy_bi(tmp, p20);
            _add_n(tmp, 2*nx+1);
            _add_bi(nsx, tmp);
            nx = nx + 1;
            if (_compare_bi(nsx, c) == 0) {
                //_copy_bi(sx, nsx);
                x = nx;
                term = 1;
                break;
            }
        }

        // rational square root
        if (term == 1) {
            break;
        }

        cnt = cnt + 1;
        // p = 10*p + x;
        _shift_left(p, 1);
        _add_n(p, x);
        // c = 100*(c-sx);
        _sub_bi(c, sx);
        _shift_left(c, 2);
        sum = sum + x;
        //printf("cnt=%d,x=%d,sum=%d\n",cnt,x,sum);
    }

    //printf("cnt=%d\n",cnt);
    if (cnt < 100) {
        // non-irrational square root
        return 0;
    } else {
        // sum of the first 100 decimal digit
        // of the irrational square root
        return sum;
    }
}

void test() {
    BigInt *ba = create_bigint();
    _set_bi(ba, 0);
    print_bi(ba);
    _add_n(ba, 2);
    print_bi(ba);
    _add_n(ba, 123);
    print_bi(ba);
    BigInt *bb = create_bigint();
    _copy_bi(bb, ba);
    print_bi(bb);
    _set_bi(bb, 999);
    _add_bi(ba,bb);
    print_bi(ba);
    _multiply_n(ba,0);
    print_bi(ba);
    _set_bi(ba, 123);
    _multiply_n(ba,1);
    print_bi(ba);
    _multiply_n(ba,12);
    print_bi(ba);
    _shift_left(ba,1);
    print_bi(ba);
    _shift_left(ba,3);
    print_bi(ba);
    print_bi(bb);
    _sub_bi(ba,bb);
    print_bi(ba);
    _set_bi(ba,0);
    _shift_left(ba,3);
    print_bi(ba);
}

int main(int argc, char* argv) {
    //test();
    init();
    int sum = 0;
    for (int i = 2; i < 100; i++) {
        int s = calc_one(i);
        //printf("%d --> %d\n",i,s);
        sum = sum + s;
    }
    printf("total sum = %d\n",sum);
    return 0;
}
