#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define TARGET 5000
#define LIMIT 10000

int numbers[LIMIT];
int *primes;
int prime_cnt = 0;

void generate_primes() {
    numbers[0] = 0;
    numbers[1] = 0;
    for (int i = 2; i < LIMIT; i++) numbers[i] = 1;
    for (int i = 2; i < LIMIT; i++) {
        if (numbers[i] == 1) {
            prime_cnt++;
            int j = i + i;
            while (j < LIMIT) {
                numbers[j] = 0;
                j = j + i;
            }
        }
    }
    primes = (int*) malloc(sizeof(int) * prime_cnt);
    int j = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (numbers[i] == 1) primes[j++] = i;
    }
}

int ways_cache[LIMIT] = {0};

int count_cond_ways(int n, int idx) {
    int max = n/2;
    int base = primes[idx];
    int cnt = 0;
    while (base <= max) {
        int left = n - base;
        if (left < base) break;
        if (numbers[left] == 1) cnt++;
        cnt = cnt + count_cond_ways(left, idx);
        idx++;
        base = primes[idx];
    }
    return cnt;
}

int count_ways(int n) {
    if (n <= 3) return 0;
    if (ways_cache[n] > 0) return ways_cache[n];
    int cnt = 0;
    int left = n - 2;
    if (numbers[left] == 1) cnt++;
    if (ways_cache[left] > 0) {
        cnt = cnt + ways_cache[left];
    } else {
        cnt = cnt + count_cond_ways(left, 0);
    }
    int max = n/2;
    int i = 1;
    int base = primes[i];    
    while (base <= max) {
        int left = n - base;
        if (numbers[left] == 1) cnt++;
        cnt = cnt + count_cond_ways(left, i);
        i++;
        base = primes[i];
    }
    ways_cache[n] = cnt;
    //printf("%d --> %d\n", n, cnt);
    return cnt;
}

int search(int low, int high) {
    if ((high - low) == 1) return high;
    while (high > low) {
        int mid = (low + high) / 2;
        int ways = count_ways(mid);
        if (ways > TARGET) {
            high = mid;
        } else if (ways <= TARGET) {
            low = mid;
        }
        if ((high - low) == 1) return high;
    }
}

void solve() {
    int guess = 100;
    int ways = count_ways(guess);
    int low;
    int high;
    if (ways < TARGET) {
        while (ways < TARGET) {
            //printf("%d --> %d\n", guess, ways);
            low = guess;
            guess = guess << 1;
            ways = count_ways(guess);
        }
        if (ways == TARGET) {
            while (ways == TARGET) {
                guess++;
                ways = count_ways(guess);
            }
            printf("number = %d\n", guess);
            return;
        } else { // ways > TARGET
            high = guess;
        }
    } else if (ways > TARGET) {
        while (ways > TARGET) {
            high = guess;
            guess = guess >> 1;
            ways = count_ways(guess);
        }
        if (ways == TARGET) {
            while (ways == TARGET) {
                guess++;
                ways = count_ways(guess);
            }
            printf("number = %d\n", guess);
            return;
        } else { // ways < TARGET
            low = guess;
        }
    } else { // we found it !?!?!?
        while (ways == TARGET) {
            guess++;
            ways = count_ways(guess);
        }
        printf("number = %d\n", guess);
        return;
    }

    //printf("low=%d, high=%d\n", low, high);
    int n = search(low, high);
    printf("number = %d\n", n);
}

// check problem 31 on projecteuler.net
void simple() {
    //int target = 101;
    int ways[101] = {0};
    //for (int i = 0; i < target; i++) ways[i] = 0;
    ways[0] = 1;
    for (int i = 0; i < prime_cnt; i++) {
        if (primes[i] >= 101) break;
        for (int j = primes[i]; j < 101; j++) {
            ways[j] = ways[j] + ways[j - primes[i]];
        }
    }
    //printf("%d -> %d\n", target - 1, ways[target - 1]);
    for (int i = 4; i < 101; i++) {
        //printf("%d --> %d\n", i, ways[i]);
        if (numbers[i] == 1 && (ways[i] - 1) > 5000) { // "prime(itself) + 0" is counted as one way
            printf("%d --> %d\n", i, ways[i] - 1);
            break;
        } else if (numbers[i] == 0 && ways[i] > 5000) {
            printf("%d --> %d\n", i, ways[i]);
            break;
        }
    }
}

int main(int argc, char* argv) {
    generate_primes();
    //solve();
    simple();
    /*printf("\n");
    for (int i = 4; i < 101; i++) {
        printf("%d --> %d\n", i, count_ways(i));
    }*/
    return 0;
}
