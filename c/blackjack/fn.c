#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "data.h"

Player player = {
    "Comodino",
    0,
    0,
    0, 
    0
};

Dealer dealer = {
    "Dealer", 
    0, 
    0, 
    0
};

char *suits[SUITS] = {
    "Diamonds", 
    "Spades", 
    "Hearts", 
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
    
    void player_update (size_t *k);
    void dealer_update (size_t *k);
    void reveal_hidden (void);
    void deal_card (int *i, int deck[][FACES]);
    void deal_dealer (int *i, int deck[][FACES]);
    void double_card (int *i, int deck[][FACES]);
    void split (int *i, int deck[][FACES]);

    int i = 1;
    bool found;
    do {
        
        found = false;
        
        for (size_t j = 0; j < SUITS && found == false; j++) {
            for (size_t k = 0; k < FACES && found == false; k++) {
                
                if (deck[j][k] == i) {
                    
                    if (i % 2 != 0) {
                        
                        if (i == 1) {
                            player.first_card = k;
                        } else {
                            player.second_card = k;
                        }
                        player_update(&k);
                        printf("%8s: %6s of %s\n%8s: %i\n", player.name, faces[k], suits[j], "Score", player.score);
                        
                        if (player.score == 21) {
                            printf("%s BlackJack!\n", player.name);
                        }

                        puts("");
                        
                    } else {
                        
                        if (i != 2) {
                            
                            dealer_update(&k);
                            printf("%8s: %6s of %s\n%8s: %i\n\n", dealer.name, faces[k], suits[j], "Score", dealer.score);
                            
                        } else {
                            
                            puts("Dealer dealt himself a covered card\n");
                            dealer.hidden_x = j;
                            dealer.hidden_y = k;
                            
                        }
                        
                    }
                    
                    i++;
                    found = true;
                    
                }
            }
        }
    } while (i <= 4);


    int x;

    do {
        
        x = 0;

        puts("1. Card\n2. Stay");

        if (i == 5) {
            
            puts("3. Double");

            if (player.first_card == player.second_card) {
                puts("4. Split");
                
                do {
                    scanf("%d", &x);
                } while (x != 1 && x != 2 && x!= 3 && x != 4);
                
            }
            
            if (x == 0) {
                do {
                    scanf("%d", &x);
                } while (x != 1 && x != 2 && x!= 3);
            }
        }

        if (x == 0) {
            do {
                scanf("%d", &x);
            } while (x != 1 && x != 2);
        }

        switch (x) {

            case 1:
                deal_card(&i, deck);
            break;

            case 2:
            break;

            case 3:
                double_card(&i, deck);
            break;

            case 4:
                split(&i, deck);
            break;

            default:
                puts("Error! You should not be seeing this");
            break;
        }

        i++;
        
    } while (player.score < 21 && x != 2);

    if (player.score > 21) {
        puts("You lost!");
        return;
    } else {
        reveal_hidden();
        
        while (dealer.score < 16) {
            deal_dealer(&i, deck);

            if (dealer.score == player.score) {
                puts("You draw the dealer!\n");
                return;
            }
        }

        if (dealer.score > 21) {
            puts("The dealer busted! You won!\n");
        } else if (dealer.score > player.score) {
            puts("Dealer scored higher than you! You lost!\n");
        } else {
            puts("You Won!\n");
        }
    }
    return;
}

void player_update (size_t *k) {

    switch (*k) {
        case 0:
            if (player.score + 11 <= 21) {
                player.score += 11;
            } else {
                player.score += 1;
            }
        break;

        case 10:
        case 11:
        case 12:
            player.score += 10;
        break;

        default:
            player.score += *k + 1;
        break;
    }

    return;
}

void dealer_update (size_t *k) {

    switch (*k) {
        case 0:
            if (dealer.score + 11 <= 21) {
                dealer.score += 11;
            } else {
                dealer.score += 1;
            }
        break;

        case 10:
        case 11:
        case 12:
            dealer.score += 10;
        break;

        default:
            dealer.score += *k + 1;
        break;
    }

    return;
}

void reveal_hidden (void) {
    printf("%s had %s of %s covered!\n", dealer.name, faces[dealer.hidden_y], suits[dealer.hidden_x]);
    dealer_update(&dealer.hidden_y);
    printf("%8s: %i\n", "Score", dealer.score);
}
    
void deal_card (int *i, int deck[][FACES]) {
    bool found = false;    
    for (size_t j = 0; j < SUITS && found == false; j++) {
        for (size_t k = 0; k < FACES && found == false; k++) {
                
            if (deck[j][k] == *i) {

                player_update(&k);
                printf("%8s: %6s of %s\n%8s: %i\n", player.name, faces[k], suits[j], "Score", player.score);                    
                    
                found = true;
            }   
        }
    }
}

void double_card (int *i, int deck[][FACES]) {

    puts("You chose to double so be it! Good Luck!\n");
    bool found = false;    
    for (size_t j = 0; j < SUITS && found == false; j++) {
        for (size_t k = 0; k < FACES && found == false; k++) {
                
            if (deck[j][k] == *i) {

                player_update(&k);
                printf("%8s: %6s of %s\n%8s: %i\n", player.name, faces[k], suits[j], "Score", player.score);                    
                    
                found = true;
            }   
        }
    }
}

void split (int *i, int deck[][FACES]) {

    puts("You split! Good Luck!\n");
    
    player.score = player.first_card;
    player.split_score = player.score;

}

void deal_dealer (int *i, int deck[][FACES]) {

    bool found = false;    
    for (size_t j = 0; j < SUITS && found == false; j++) {
        for (size_t k = 0; k < FACES && found == false; k++) {
                
            if (deck[j][k] == *i) {

                dealer_update(&k);
                printf("%8s: %6s of %s\n%8s: %i\n", dealer.name, faces[k], suits[j], "Score", dealer.score);                    
                    
                found = true;
            }   
        }
    }
}
