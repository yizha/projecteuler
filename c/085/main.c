#include <stdio.h>
#include <math.h>

/*
 rectangles count: a*(a+1)*b*(b+1) / 4
*/
int main(int argc, char** argv) {
    int s = 4 * 2000000;
    int a = 1;
    int b;
    int cnt = 0;
    int max = 0;
    int t;
    for (;;a++) {
        t = a*(a+1);
        b = floor(sqrt(s/t)) - 1;
        if (a > b) break;
        for (;;b++) {
            cnt = t*b*(b+1);
            if (cnt <= s) {
                if (cnt > max) {
                    printf("a=%d,b=%d,a*b=%d,count=%d\n",a,b,a*b,cnt/4);
                    max = cnt;
                }
            } else {
                break;
            }
        }
    }
}
