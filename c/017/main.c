#include <stdio.h>

// one --> 3
// two --> 3
// three --> 5
// four --> 4
// five --> 4
// six --> 3
// seven --> 5
// eight --> 5
// nine --> 4
// ==> 36
// ten --> 3
// eleven --> 6
// twelve --> 6
// thirteen --> 8
// fourteen --> 8
// fifteen --> 7
// sixteen --> 7
// seventeen --> 9
// eighteen --> 8
// nineteen --> 8
// ==> 70
// twenty --> 6
// thirty --> 6
// forty --> 5
// fifty --> 5
// sixty --> 5
// seventy --> 7
// eighty --> 6
// ninety --> 6
// ==> 46
// hundred --> 7
// hundred and --> 10
// thousand --> 8
int main(int argc, char* argv) {
    int sum = 0;
    // 1 ~ 9, 10 ~ 19, 20 ~ 99
    int sum_nn = 36 + 70 + ((46 * 10) + (36 * 8));
    sum = sum + sum_nn;
    // hundres (100, 200 ... 900)
    sum = sum + 36 + 7 * 9;
    // hundres and 1~99
    sum = sum + (36 + 10 * 9) * 99 + sum_nn * 9;
    // one thousand
    sum = sum + 3 + 8;

    printf("sum = %d\n", sum);
}
