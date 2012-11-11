#include <stdio.h>
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
#define HIGH_CARD      0x0001;
#define ONE_PAIR       0x0002;
#define TWO_PAIRS      0x0004;
#define THREE          0x0008;
#define STRAIGHT       0x0010;
#define FLUSH          0x0020;
#define FULL_HOUSE     0x0040;
#define FOUR           0x0080;
#define STRAIGHT_FLUSH 0x0100;
#define ROYAL_FLUSH    0x0200;

typedef struct _hand {
    char cards[5];
    char suit;
    int type;
} hand;

void read_cards(hand *h, char *input, int start) {
    int i = start;
    int last = start + 13;
    char cards[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    char suit = -1;
    while (1) {
        // number
        char ch = input[i++];
        if (ch == 'A') {
            cards[12]++;
        } else if (ch == 'J') {
            cards[9]++;
        } else if (ch == 'Q') {
            cards[10]++;
        } else if (ch == 'K') {
            cards[11]++;
        } else if (ch == 'T') { // '10' --> Ten
            cards[8]++;
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
        if (i == last) {
            break;
        } else {
            i++;
        }
    }
    // set suit
    h->suit = suit;
    // determine type, save type & cards
    if (suit > 0 
            && (cards[12] == 1 
                && cards[11] == 1 
                && cards[10] == 1 
                && cards[9] == 1 
                && cards[8] == 1)) {
        h->type = ROYAL_FLUSH;
        /* add we don't need to save cards for ROYAL_FLUSH */
        return;
    } else {
        for (int i = 12; i >= 0; i++) {

        }
    }
}

int main(int argc, char* argv) {

    FILE *fp = fopen("poker.txt", "r");
    char line[32];
    while (!feof(fp)) {
        fgets(line, 30, fp);
        fgetc(fp);
        //printf("line --> %s\n", line); 
    }
    fclose(fp);
}
