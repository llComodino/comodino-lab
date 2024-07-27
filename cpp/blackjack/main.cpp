/* 
 * Black Jack Project
 * Author: 	Comodino
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Global variables
const int MAX_CARDS = 52;
const int MAX_PLAYERS = 7;
const int MAX_DEALER = 17;
const int MAX_SCORE = 21;
const int SUITS = 4;
const int RANKS = 13;

// Card structure
typedef struct {
    string suit;
    string rank;
    int value;
} Card;

// Player structure
typedef struct {
    string name;
    vector<Card> hand;
    int score;
} Player;

// Function prototypes
void createDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void dealCards(Card deck[], Player * players, int numPlayers);
void showCards(Player players[], int numPlayers);
void showDealer(Player players[], int numPlayers);
void hit(Card deck[], Player players[], int numPlayers);
void dealerHit(Card deck[], Player player, int numPlayers);
void checkScore(Player players[], int numPlayers);
void checkWinner(Player players[], int numPlayers);
void clearHands(Player players[], int numPlayers);

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create the deck of cards
    Card deck[MAX_CARDS];
    createDeck(deck);

    // Shuffle the deck of cards
    shuffleDeck(deck);

    // Create the dealer 
    Player dealer;

    // Create the players
    Player players[MAX_PLAYERS];
    int numPlayers = 0;
    
    cout << "How many players? (1 - 7): ";
    cin >> numPlayers;
    
    while (numPlayers < 1 || numPlayers > 7) {
        cout << "Invalid number of players. Please enter a number between 1 and 7: ";
        cin >> numPlayers;
    }

    // Give each player a name 
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter player " << i + 1 << "'s name: ";
        cin >> players[i].name;
    }

    // Deal the cards
    dealCards(deck, players, numPlayers);

    // Deal the dealer's cards
    dealer.hand.push_back(deck[numPlayers * 2]);
    dealer.hand.push_back(deck[numPlayers * 2 + 1]);

    // Show the cards
    showCards(players, numPlayers);

    // Show the dealer's first card
    cout << "Dealer's first card: " << dealer.hand[0].rank << " of " << dealer.hand[0].suit << endl;

    // Hit or stay
    char choice = 'h';
    for (int i = 0; i < numPlayers; i++) {
        
        cout << players[i].name << ", do you want to hit or stay? (h/s): ";
        cin >> choice;
        
        while (choice != 'h' && choice != 's') {
            cout << "Invalid choice. Please enter h to hit or s to stay: ";
            cin >> choice;
        }

        if (choice == 'h') {
            hit(deck, players, i);
        }
        
        // Check the score 
        if (players[i].score > MAX_SCORE) {
            cout << players[i].name << " busted!" << endl;
        }
    }

    // Dealer's turn
    while (dealer.score < MAX_DEALER) {
        dealerHit(deck, dealer, 1);
    }

    // Check the score
    checkScore(players, numPlayers);

    // Check the winner
    checkWinner(players, numPlayers);

    // Clear the hands
    clearHands(players, numPlayers);

    return 0;
}

// Function definitions

// Create the deck of cards 
void createDeck(Card deck[]) {
    string suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[RANKS] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    int values[RANKS] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    int card = 0;
    for (int suit = 0; suit < SUITS; suit++) {
        for (int rank = 0; rank < RANKS; rank++) {
            deck[card].suit = suits[suit];
            deck[card].rank = ranks[rank];
            deck[card].value = values[rank];
            card++;
        }
    }
}

// Shuffle the deck of cards 
void shuffleDeck(Card deck[]) {
    for (int i = 0; i < MAX_CARDS; i++) {
        int randomIndex = rand() % MAX_CARDS;
        Card temp = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
    }
}

// Deal the cards 
void dealCards(Card deck[], Player * players, int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        players[i].score = 0;
        players[i].hand.push_back(deck[i]);
        players[i].hand.push_back(deck[i + numPlayers]);
    }
}

// Show the cards 
void showCards(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        cout << players[i].name << "'s cards: " << endl;
        for (int j = 0; j < players[i].hand.size(); j++) {
            cout << players[i].hand[j].rank << " of " << players[i].hand[j].suit << endl;
        }
        cout << endl;
    }
}

// Show the dealer's cards 
void showDealer(Player players[], int numPlayers) {
    cout << "Dealer's cards: " << endl;
    for (int i = 0; i < players[numPlayers].hand.size(); i++) {
        cout << players[numPlayers].hand[i].rank << " of " << players[numPlayers].hand[i].suit << endl;
    }
    cout << endl;
}

// Hit 
void hit(Card deck[], Player players[], int numPlayers) {
    
    for (int k = 0, j = 0; k < numPlayers; k++) {
        while (players[k].score < MAX_SCORE) {
            players[numPlayers].hand.push_back(deck[numPlayers + (numPlayers + (++j))]);
            cout << players[numPlayers].name << "'s cards: " << endl;
            for (int i = 0; i < players[numPlayers].hand.size(); i++) {
                cout << players[numPlayers].hand[i].rank << " of " << players[numPlayers].hand[i].suit << endl;
            }
            cout << endl;
        }
    }
}

// Dealer hit 
void dealerHit(Card deck[], Player player, int numPlayers) {
    while (player.score < MAX_DEALER) {
        player.hand.push_back(deck[numPlayers + (numPlayers + 1)]);
        cout << "Dealer's cards: " << endl;
        for (int i = 0; i < player.hand.size(); i++) {
            cout << player.hand[i].rank << " of " << player.hand[i].suit << endl;
        }
        cout << endl;
    }
}

// Check the score 
void checkScore(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < players[i].hand.size(); j++) {
            players[i].score += players[i].hand[j].value;
        }
        cout << players[i].name << "'s score: " << players[i].score << endl;
    }
    cout << endl;
}

// Check the winner 
void checkWinner(Player players[], int numPlayers) {
    int highestScore = 0;
    int winner = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].score > highestScore && players[i].score <= MAX_SCORE) {
            highestScore = players[i].score;
            winner = i;
        }
    }
    cout << "The winner is " << players[winner].name << " with a score of " << players[winner].score << endl;
}

// Clear the hands 
void clearHands(Player players[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        players[i].hand.clear();
    }
}
