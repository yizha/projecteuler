#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
 * I guess the last character should be '.',
 * base on the guess and with some simply calculation
 * I figure out the first char of the password should 
 * be 'g', and the plain should not contain any 
 * invisible ascii chars so I filter out them all, 
 * also I use the common word ' the ' to verify the 
 * deciphered text, and finally print out all candidates
 * on screen and check with eyes.
 * 
 * Lucky, only one candidate and it is it!
 */

void swap(int *a, int *b) {
    int t = *a; 
    *a = *b; 
    *b = t;
}

int get_cipher_text(char *cipher) {
    FILE *fp = fopen("cipher1.txt", "r");
    char ascii[4];
    int i = 0;
    char ch;
    int cnt = 0;
    while (1) {
        ch = fgetc(fp);
        if (ch == ',' || ch == EOF) {
            ascii[i] = '\0';
            cipher[cnt++] = atoi(ascii);
            if (ch == EOF) break;
            i = 0;
        } else {
            ascii[i++] = ch;
        }
        
    }   
    fclose(fp);
    return cnt;
}

int next_password_characters(int *n) {
    int one_cnt = 0;
    int i = 0;
    for (; i < 26 - 1; i++) {
        if (n[i] == 1) one_cnt++;
        if (n[i] == 1 && n[i + 1] == 0) {
            swap(&n[i], &n[i + 1]);
            one_cnt--;
            if (one_cnt > 0 && i > 0 && one_cnt < i) {
                for (int j = 0; j < i; j++) {
                    if (one_cnt > 0) {
                        n[j] = 1;
                        one_cnt--;
                    } else {
                        n[j] = 0;
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}

void get_password(char (*password)[3], int *alpha) {
    int j = 0;
    int ch[3];
    for (int i = 0; i < 26; i++) {
        if (alpha[i] == 1) ch[j++] = 'a' + i;
    }
    password[0][0] = ch[0];
    password[0][1] = ch[1];
    password[0][2] = ch[2];

    password[1][0] = ch[0];
    password[1][1] = ch[2];
    password[1][2] = ch[1];

    password[2][0] = ch[1];
    password[2][1] = ch[0];
    password[2][2] = ch[2];

    password[3][0] = ch[1];
    password[3][1] = ch[2];
    password[3][2] = ch[0];

    password[4][0] = ch[2];
    password[4][1] = ch[0];
    password[4][2] = ch[1];

    password[5][0] = ch[2];
    password[5][1] = ch[1];
    password[5][2] = ch[0];
}

void get_key(char *key, char *password, int len) {
    for (int i = 0; i < len; i++) {
        key[i] = password[i % 3];
    }
}

int has_the(char *text, int len) {
    for (int i = 0; i < len; i++) {
        if (i + 4 < len) {
            if (text[i] == ' ' 
                    && (text[i + 1] == 't' || (text[i + 1] - 32) == 't')
                    && text[i + 2] == 'h'
                    && text[i + 3] == 'e'
                    && text[i + 4] == ' ') return 1;
        }
    }
    return 0;
}

int deciphering(char *cipher_text, char *key, char *plain_text, int len) {
    for (int i = 0; i < len; i++) {
        char ch = cipher_text[i] ^ key[i];
        if ((ch != 10 && ch != 13 && ch < 32) || ch > 126) return 0; // invisible ascii character
        //if (ch < 32 || ch > 126) return 0; // invisible ascii character
        plain_text[i] = ch;
    }
    if (has_the(plain_text, len)) return 1;
    return 0;
}

void print_chars(char *ch, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", ch[i]);
    }
    printf("\n");
}

int ascii_sum(char *chars, int len) {
    int s = 0;
    for (int i = 0; i < len; i++) {
        s = s + chars[i];
    }
    return s;
}

char find_top_char(char *list, int len) {
    int *mark = (int*) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) mark[i] = 0;
    char top_ch;
    int max_cnt = 0;
    for (int i = 0; i < len; i++) {
        if (mark[i]) continue;
        int cnt = 0;
        char ch = list[i];
        for (int j = 0; j < len; j++) {
            if (mark[j]) continue;
            if (list[j] == ch) {
                cnt++;
                mark[j];
            }
        }
        if (cnt > max_cnt) {
            max_cnt = cnt;
            top_ch = ch;
        }
    }
    free(mark);
    return top_ch;
}

/*
 * Another way after reading threads, the key is 
 * using ' '(space) as the most common English
 * word, to find the password chars:
 *
 * 1. split cipher text into three arrays, 
 * 2. find the top frequency char in each list
 * 3. xor the top char with 'space' to get the password
 * 4. verify, and bingo we got it
 */
void another_way() {
    char cipher_text[1500];

    int len = get_cipher_text(cipher_text);
    // 1. split chars into 3 arrays
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    char list1[500];
    char list2[500];
    char list3[500];
    for (int i = 0; i < len; i++) {
        int x = i % 3;
        if (x == 0) {
            list1[i1++] = cipher_text[i];
        } else if (x == 1) {
            list2[i2++] = cipher_text[i];
        } else {
            list3[i3++] = cipher_text[i];
        }
    }
    // 2. find the top char in each array
    char top_ch1 = find_top_char(list1, i1);
    char top_ch2 = find_top_char(list2, i2);
    char top_ch3 = find_top_char(list3, i3);

    //printf("%d %d %d\n", top_ch1, top_ch2, top_ch3);
    
    // 3. xor with 'space' to get the password
    char pass[3] = {top_ch1 ^ ' ', top_ch2 ^ ' ', top_ch3 ^ ' '};
    
    printf("password=%c%c%c\n", pass[0], pass[1], pass[2]);

    // 4. verify it
    char plain_text[1500];
    int sum = 0;
    for (int i = 0; i < len; i++) {
        char ch = pass[i % 3] ^ cipher_text[i];
        printf("%c", ch);
        sum = sum + ch;
    }
    printf("\nascii sum = %d\n", sum);
}

void my_way() {
    char cipher_text[2000];
    char plain_text[2000];
    char key[2000];

    int alpha[26] = {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char password[6][3];

    int len = get_cipher_text(cipher_text);

    int more = 0;
    do {
        get_password(password, alpha);
        for (int i = 0; i < 6; i++) {
            char *pass = &password[i][0];
            if (pass[0] != 'g') continue;
            //print_chars(pass, 3);
            get_key(key, pass, len);
            int valid = deciphering(cipher_text, key, plain_text, len);
            if (valid) {
                printf("password ==> ");
                print_chars(pass, 3);
                printf("plain text ===> ");
                print_chars(plain_text, len);
                printf("ascii sum ===> %d\n", ascii_sum(plain_text, len));
                printf("\n");
                while (getchar() != 10) ;
            }
        }
        more = next_password_characters(alpha);
    } while (more > 0);
}


int main(int argc, char* argv) {
    //my_way();
    another_way();
}
