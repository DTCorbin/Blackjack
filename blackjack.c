#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DECK_SIZE 48 //standard deck without jokers
#define TARGET 21 // Game objective

//global game variables
int deck[DECK_SIZE];                                            //could be in main
int len = sizeof(deck)/sizeof(int);                             //could be in main
char suits[4][9] = {"Spades", "Hearts", "Clubs", "Diamonds"};   //could be in main
int ranks[] = {1, 2, 3, 4, 5, 6, 7, 8 , 9, 10, 11, 12};         //could be in main
int deckPtr = 0;    //could be in main
int splitable = 0;  //could be in main
int splitVal = 0;   //could be in main


void deckInit(int *deck){
    for (int i = 0; i < len; i++) {
        deck[i] = i;
    }
}

void shuffle (int *deck) {
    puts("Shuffling deck...");
    int rIndex = 0;
    srand(time(NULL));
    int temp = deck[0];
    for (int i = 0; i < len; i++) {
        rIndex = rand() % DECK_SIZE;
        temp = deck[rIndex];
        deck[rIndex] = deck[i];
        deck[i] = temp;
    }
}

int deal(int *deck, int total){
    int prev = 0;
    for (deckPtr; deckPtr < 2; deckPtr++) {
        
        int rankIndex = deck[deckPtr]%12;
        int cardVal = ranks[rankIndex];
        if (prev == cardVal){
            splitable = 1;
            splitVal = cardVal;
        } else{
            prev = cardVal;
        }
        int suitIndex = deck[deckPtr]/12;
        char *cardSuit = suits[suitIndex];
        // face cards are worth 10
        if (cardVal >= 10) {
            total += 10;
        } else{
            total += cardVal;
        }
        printf("You got: %d of %s\n", cardVal, cardSuit);
    }
    printf("Total: %d\n", total);
    return total;
}

int hit(int *deck, int total){
    printf("Here is your next card....\n");
    int rankIndex = deck[deckPtr]%12;
    int cardVal = ranks[rankIndex];
    int suitIndex = deck[deckPtr]/12;
    char *cardSuit = suits[suitIndex];
    // face cards are worth 10
    if (cardVal >= 10) {
        total += 10;
    } else{
        total += cardVal;
    }
    deckPtr++;
    printf("You got: %d of %s\n", cardVal, cardSuit);
    printf("Total: %d\n", total);
    return total;
}

void stand (int total, float bet) {
    if (total >= 18 && total <= TARGET){
        float winnings = bet * 1.5;
        printf("\nCongratulations, you won $%.2f\n\nI hope you enjoyed a quick game of Blackjack!\n", winnings);
    } else {
        printf("\nSorry, you lost your $%.2f\n\nBetter luck next time!", bet);
    }
}

void doubleDown (int *deck, int total, float bet) {
    bet = bet * 2;
    total = hit(deck, total);
    stand(total, bet);
}

//DEBUGGING PURPOSES ONLY
// void printDeck(int *deck){
//     for (int i = 0; i < len; i++) {
//         printf("%d: %d\n ", i, deck[i]);
//     }
// }

int main () {
    float bet;
    int total = 0;
    char move;

    deckInit(deck);
    shuffle(deck);
    puts("\t\t\t\tWelcome to BlackJack\n\n\
        Your goal is to get as close to 21 as possible without going over.\n\n\
        To hit: type h\n\
        To double down: type d\n\
        To split: type s\n\
        To stand: type q\n\n\
        Please enjoy your game. Good Luck!\n\n");

    //getchar is being used to consume the \n from scanf
    bet:
    printf("Please place your bet: ");
    if (scanf("%f", &bet)!= 1) {
        getchar();
        printf("Your bet has to be a monetary value. ");
        goto bet;
    } else{
        getchar();
    }

    total = deal(deck, total);
    int splitTotal = total;
    firstMove:
    printf("\nWhat is your first move? ");
    scanf("%c", &move);
    getchar();
    //had to be an if else chain due to the split conditional
    if (move == 's' && splitable) {
        total = total/2;
        splitTotal = total;
        splitVal++;
    } else if (move == 'h') {
        total = hit(deck, total);
        splitTotal = total;
    } else if (move == 'd') {
        doubleDown(deck, total, bet);
        return 0;
    } else if (move == 'q') {
        stand(total, bet);
        return 0;
    } else {
        puts("Illegal move... Lets try again.\n");
        goto firstMove;
    }

    for (int i = 0; i <= splitable; i++){
        total = splitTotal;
        printf("\nGame %d of %d\n", (i+1), (splitable+1));
        decision:
        printf("\nWhat would you like to do next? ");
        scanf("%c", &move);
        getchar();
        switch (move){
            case 'h':
                total = hit(deck, total);
                goto decision;
                break;
            case 'd':
                doubleDown(deck, total, bet);
                break;
            case 'q':
                stand(total, bet);
                break;
            case 's':
                printf("\nSplitting must be done on the first move. When both cards are the same\n");
                goto decision;
                break;
            default:
                printf("\nPlease enter a valid letter.\n");
                goto decision;
        }

    }
    // To Do:
    //refactor to get rid of as many global variables as possible
    return 0;
}
