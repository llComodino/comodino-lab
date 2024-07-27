#include <stdio.h>
#include "data.h"

int main (void) {
    
    int deck[SUITS][FACES] = {0};
    deck_init(deck);
    deal(deck);
    return 0;
}
