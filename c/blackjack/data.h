#include <stdio.h>
#include <stdlib.h>

#define SUITS 4
#define FACES 13

typedef struct {
    char *name;
    int first_card;
    int second_card;
    int score;
    int split_score;
} Player;

typedef struct {
    char *name;
    size_t hidden_x;
    size_t hidden_y;
    int score;
} Dealer;

void deck_init (int [][FACES]);
void deal (int [][FACES]);
