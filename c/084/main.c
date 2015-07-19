#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define SQUARE_CNT 40
#define DICE_SIDES 4
#define STEPS      10000000

/*
0: GO
1: A1
2: CC1
3: A2
4: T1
5: R1
6: B1
7: CH1
8: B2
9: B3
10: JAIL
11: C1
12: U1
13: C2
14: C3
15: R2
16: D1
17: CC2
18: D2
19: D3
20: FP
21: E1
22: CH2
23: E2
24: E3
25: R3
26: F1
27: F2
28: U2
29: F3
30: G2J
31: G1
32: G2
33: CC3
34: G3
35: R4
36: CH3
37: H1
38: T2
39: H2
*/

/*
 * return a random number between 0 and limit inclusive.
 */
int rand_lim(int limit) {

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

time_t t;
int twins;
int pos;
int square[SQUARE_CNT];
int idx_sort[SQUARE_CNT];
void reset() {
    twins = 0;
    square[0] = 1;
    idx_sort[0] = 0;
    for (int i = 1; i < SQUARE_CNT; i++) {
        square[i] = 0;
        idx_sort[i] = i;
    }
    pos = 0;
    srand((unsigned) time(&t));
}

int roll() {
    int n1 = rand_lim(DICE_SIDES-1)+1;
    int n2 = rand_lim(DICE_SIDES-1)+1;
    if (n1 == n2) {
        twins++;
    } else {
        twins = 0;
    }
    return n1 + n2;
}

int on_CC(int cur_pos) {
    int n = rand_lim(15);
    if (n == 0) return 0;  // GO
    if (n == 1) return 10; // JAIL
    return cur_pos;
}

int on_CH(int cur_pos) {
    int n = rand_lim(15);
    if (n == 0) return 0;  // to GO
    if (n == 1) return 10; // to JAIL
    if (n == 2) return 11; // to C1
    if (n == 3) return 24; // to E3
    if (n == 4) return 39; // to H2
    if (n == 5) return 5;  // to R1
    if (n == 6 || n == 7) { // to next R
        if (cur_pos == 7) return 15;  // CH1 --> R2
        if (cur_pos == 22) return 25; // CH2 --> R3
        return 5;                     // CH3 --> R1
    }
    if (n == 8) { // to next U
        if (cur_pos == 7) return 12;  // CH1 --> U1
        if (cur_pos == 22) return 28; // CH2 --> U2
        return 12;                    // CH3 --> U1
    }
    if (n == 9) { // go back 3 squares
        if (cur_pos == 7) return 4;
        if (cur_pos == 22) return 19;
        return on_CC(33); // on CH3, go back to CC3
    }
    return cur_pos;
}

int move() {
    int steps = roll();
    if (twins >= 3) {
        pos = 10;
        twins = 0;
    } else {
        pos = pos + steps;
        if (pos > (SQUARE_CNT-1)) {
            pos = pos - SQUARE_CNT;
        }
    }
    switch (pos) {
        case 2:  // CC1
        case 17: // CC2
        case 33: // CC3
            pos = on_CC(pos);
            break;
        case 7:  // CH1
        case 22: // CH2
        case 36: // CH3
            pos = on_CH(pos);
            break;
        case 30: // G2J
            pos = 10; // JAIL
            break;
    }
    square[pos]++;
}

void sort() {
    int t;
    for (int i = 0; i < SQUARE_CNT; i++) {
        for (int j = i + 1; j < SQUARE_CNT; j++) {
            if (square[idx_sort[i]] < square[idx_sort[j]]) {
                t = idx_sort[i];
                idx_sort[i] = idx_sort[j];
                idx_sort[j] = t;
            }
        }
    }
}

int main(int argc, char** argv) {
    reset();
    for (int i = 0; i < STEPS; i++) move();
    
    sort();
    for (int i = 0; i < 5; i++) {
        printf("%02d: %d/%d\n", idx_sort[i], square[idx_sort[i]], STEPS);
    }
}
