#include <stdio.h>
#include <malloc.h>

/*
High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit
*/
#define HIGH_CARD      0x0001
#define ONE_PAIR       0x0002
#define TWO_PAIRS      0x0004
#define THREE          0x0008
#define STRAIGHT       0x0010
#define FLUSH          0x0020
#define FULL_HOUSE     0x0040
#define FOUR           0x0080
#define STRAIGHT_FLUSH 0x0100
#define ROYAL_FLUSH    0x0200

typedef struct _hand {
    int cards[5];
    char suit;
    int type;
} hand;

void load_hand(hand *h, char *input, int start) {
    int i = start;
    int last = start + 13;
    int cards[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    char suit = -1;
    while (1) {
        // number
        char ch = input[i++];
        if (ch == 'A') {
            cards[12]++;
        } else if (ch == 'T') { // '10' --> Ten
            cards[8]++;
        } else if (ch == 'J') {
            cards[9]++;
        } else if (ch == 'Q') {
            cards[10]++;
        } else if (ch == 'K') {
            cards[11]++;
        } else { // '2' - '9'
            cards[ch - '0' - 2]++;
        }
        // suit
        char s = input[i++];
        if (suit == -1) {
            suit = s;
        } else if (suit != s) {
            suit = 0;
        }
        // space
        if (i > last) {
            break;
        } else {
            i++;
        }
    }
    // set suit
    h->suit = suit;
    // determine type, save type & cards
    if (suit > 0) { 
        if (cards[12] == 1 
                && cards[11] == 1 
                && cards[10] == 1 
                && cards[9] == 1 
                && cards[8] == 1) {
            h->type = ROYAL_FLUSH;
            h->cards[0] = 12;
            h->cards[1] = 11;
            h->cards[2] = 10;
            h->cards[3] = 9;
            h->cards[4] = 8;
            return;
        } else if (cards[0] == 1 && cards[1] == 1
                && cards[2] == 1 && cards[3] == 1
                && cards[12] == 1) { // 'A', '2', '3', '4', '5'
            h->type = STRAIGHT_FLUSH;
            h->cards[0] = 3;
            h->cards[1] = 2;
            h->cards[2] = 1;
            h->cards[3] = 0;
            h->cards[4] = -1;
            return;
        } else {
            int j = 0;
            for (int i = 12; i >= 4; i--) {
                int card_cnt = cards[i];
                while (card_cnt-- > 0) h->cards[j++] = i;
                if (cards[i] == 1 && cards[i - 1] == 1
                        && cards[i - 2] == 1 && cards[i - 3] == 1
                        && cards[i - 4] == 1) {
                    h->type = STRAIGHT_FLUSH;
                    return;
                }
            }
            h->type = FLUSH;
            return;
        }
    } else {
        if (cards[0] == 1 && cards[1] == 1
                && cards[2] == 1 && cards[3] == 1
                && cards[12] == 1) { // 'A', '2', '3', '4', '5'
            h->type = STRAIGHT;
            h->cards[0] = 3;
            h->cards[1] = 2;
            h->cards[2] = 1;
            h->cards[3] = 0;
            h->cards[4] = -1;
            return;
        } else {
            int pair[] = {-1,-1};
            int three = -1;
            int four = -1;
            int j = 0;
            int high_cards[5];
            int k = 0;
            for (int i = 12; i >= 0; i--) {
                int card_cnt = cards[i];
                if (card_cnt == 4) {
                    four = i;
                } else if (card_cnt == 3) {
                    three = i;
                } else if (card_cnt == 2) {
                    if (pair[0] == -1) {
                        pair[0] = i;
                    } else {
                        pair[1] = i;
                    }
                } else if (card_cnt == 1) {
                    if (i >= 4 && cards[i] == 1 && cards[i - 1] == 1
                            && cards[i - 2] == 1 && cards[i - 3] == 1
                            && cards[i - 4] == 1) {
                        h->type = STRAIGHT;
                        h->cards[0] = i;
                        h->cards[1] = i - 1;
                        h->cards[2] = i - 2;
                        h->cards[3] = i - 3;
                        h->cards[4] = i - 4;
                        return;
                    } else {
                        high_cards[k++] = i;
                    }
                }
            }
            
            if (four > -1) {
                h->type = FOUR;
                h->cards[0] = four;
                h->cards[1] = four;
                h->cards[2] = four;
                h->cards[3] = four;
                h->cards[4] = high_cards[0];
            } else if (three > -1 && pair[0] > -1) {
                h->type = FULL_HOUSE;
                h->cards[0] = three;
                h->cards[1] = three;
                h->cards[2] = three;
                h->cards[3] = pair[0];
                h->cards[4] = pair[0];
            } else if (three > -1) {
                h->type = THREE;
                h->cards[0] = three;
                h->cards[1] = three;
                h->cards[2] = three;
                h->cards[3] = high_cards[0];
                h->cards[4] = high_cards[1];
            } else if (pair[0] > -1 && pair[1] > -1) {
                h->type = TWO_PAIRS;
                h->cards[0] = pair[0];
                h->cards[1] = pair[0];
                h->cards[2] = pair[1];
                h->cards[3] = pair[1];
                h->cards[4] = high_cards[0];
            } else if (pair[0] > -1 && pair[1] == -1) {
                h->type = ONE_PAIR;
                h->cards[0] = pair[0];
                h->cards[1] = pair[0];
                h->cards[2] = high_cards[0];
                h->cards[3] = high_cards[1];
                h->cards[4] = high_cards[2];
            } else {
                h->type = HIGH_CARD;
                h->cards[0] = high_cards[0];
                h->cards[1] = high_cards[1];
                h->cards[2] = high_cards[2];
                h->cards[3] = high_cards[3];
                h->cards[4] = high_cards[4];
            }
            return;
        }
    }
}

void print_cards(hand *a, hand *b) {
    printf("   %d/%d/[%d,%d,%d,%d,%d] <--> %d/%d/[%d,%d,%d,%d,%d]", 
            a->type, a->suit, a->cards[0], a->cards[1], a->cards[2], a->cards[3], a->cards[4],
            b->type, b->suit, b->cards[0], b->cards[1], b->cards[2], b->cards[3], b->cards[4]);
}

int compare_hand(hand *a, hand *b) {
    //print_cards(a, b);
    int r = 0;
    if (a->type != b->type) {
        r = a->type - b->type;
    } else if (a->type == ROYAL_FLUSH) {
        r = (a->suit - b->suit);
    } else if (a->type == STRAIGHT_FLUSH) {
        if (a->suit != b->suit) {
            r = (a->suit - b->suit);
        } else {
            r = (a->cards[0] - b->cards[0]);
        }
    } else if (a->type == FOUR) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else {
            r = (a->cards[4] - b->cards[4]);
        }
    } else if (a->type == FULL_HOUSE) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else {
            r = (a->cards[3] - b->cards[3]);
        }
    } else if (a->type == FLUSH) {
        r = (a->cards[0] - b->cards[0]);
    } else if (a->type == STRAIGHT) {
        r = (a->cards[0] - b->cards[0]);
    } else if (a->type == THREE) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else if (a->cards[3] != b->cards[3]) {
            r = (a->cards[3] - b->cards[3]);
        } else {
            r = (a->cards[4] - b->cards[4]);
        }
    } else if (a->type == TWO_PAIRS) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else if (a->cards[2] != b->cards[2]) {
            r = (a->cards[2] - b->cards[2]);
        } else {
            r = (a->cards[4] - b->cards[4]);
        }
    } else if (a->type == ONE_PAIR) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else if (a->cards[2] != b->cards[2]) {
            r = (a->cards[2] - b->cards[2]);
        } else if (a->cards[3] != b->cards[3]) {
            r = (a->cards[3] - b->cards[3]);
        } else {
            r = (a->cards[4] - b->cards[4]);
        }
    } else if (a->type == HIGH_CARD) {
        if (a->cards[0] != b->cards[0]) {
            r = (a->cards[0] - b->cards[0]);
        } else if (a->cards[1] != b->cards[1]) {
            r = (a->cards[1] - b->cards[1]);
        } else if (a->cards[2] != b->cards[2]) {
            r = (a->cards[2] - b->cards[2]);
        } else if (a->cards[3] != b->cards[3]) {
            r = (a->cards[3] - b->cards[3]);
        } else {
            r = (a->cards[4] - b->cards[4]);
        }
    } else {
        printf("unknow type: %d\n", a->type);
    }
    //printf(" %d \n", r);
    return r;
}

int main(int argc, char* argv) {

    FILE *fp = fopen("poker.txt", "r");
    char line[32];
    hand *p1 = (hand*) malloc(sizeof(hand));
    hand *p2 = (hand*) malloc(sizeof(hand));
    int p1_win_cnt = 0;
    int p2_win_cnt = 0;
    int p1_equals_p2 = 0;
    while (!feof(fp)) {
        fgets(line, 30, fp);
        if (fgetc(fp) < 0) break;
        //printf("=> %s\n", line); 
        load_hand(p1, line, 0);
        load_hand(p2, line, 15);
        int x = compare_hand(p1, p2);
        if (x > 0) {
            p1_win_cnt++;
        } else if (x < 0) {
            p2_win_cnt++;
        } else {
            p1_equals_p2++;
        }
        //break;
    }
    fclose(fp);
    free(p1);
    free(p2);

    printf("player one win %d hands.\n", p1_win_cnt);
    printf("player two win %d hands.\n", p2_win_cnt);
}
