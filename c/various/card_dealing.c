#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SUITS 4
#define FACES 13

char *suits[SUITS] = {
    "Diamonds", 
    "Hearts", 
    "Spades", 
    "Clubs"
};

char *faces[FACES] = {
    "Ace", 
    "Two", 
    "Three", 
    "Four", 
    "Five", 
    "Six", 
    "Seven", 
    "Eight", 
    "Nine", 
    "Ten", 
    "Jack", 
    "Queen", 
    "King"
};

void deck_init (int deck[][FACES]);
void deal (int deck[][FACES]);

int main (void) {
    int deck[SUITS][FACES] = {0};
    deck_init(deck);
    deal(deck);
    return 0;
}

void deck_init (int deck[][FACES]) {

    srand(time(NULL));

    int i = 1;
    int x;
    int y;
    
    do {
        x = rand() % SUITS;
        y = rand() % FACES;
        
        if (deck[x][y] == 0) {
            deck[x][y] = i++;
        }
    } while (i <= SUITS * FACES);

    return;
}

void deal (int deck[][FACES]) {
    
    int i = 1;
    bool found;
    do {
        found = false;
        for (size_t j = 0; j < SUITS && found == false; j++) {
            for (size_t k = 0; k < FACES && found == false; k++) {
                if (deck[j][k] == i) {
                    printf("%s of %s\n", suits[j], faces[k]);
                    i++;
                    found = true;
                }
            }
        }
    } while (i < FACES * SUITS);
    return;
}
