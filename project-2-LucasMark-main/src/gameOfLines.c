#include "stdio.h"
#include "stdlib.h"
#include "gameOfLines.h"
#include "time.h"

void scanSettings(int *opponentIsAi, int *sizeOfArena, int *sizeOfWinLine){
    char playerChoice;
    while(1) {
        printf("Do yo want to play against another player? y/n \n");
        scanf(" %c",&playerChoice);
        if (playerChoice == 'y') {
            printf("Human opponent chosen \n");
            *opponentIsAi = 0;
            break;
        } else if (playerChoice == 'n') {
            printf("CPU opponent chosen \n");
            *opponentIsAi = 1;
            break;
        } else {
            printf("Invalid Input, please answer yes or no (y/n) \n");
        }
    }
    while(1) {
        printf("How large should the field be? needs to be larger than 1\n");
        scanf(" %d", sizeOfArena);
        if (*sizeOfArena < 2) {
            printf("Invalid input, needs to be an integer larger than 1 \n");
        } else {
            break;
        }
    }
    while (1) {
        printf("How long should a winning line be?Needs to be larger than 1, but no bigger than field size: %d \n",
               *sizeOfArena);
        scanf(" %d", sizeOfWinLine);
        if (*sizeOfWinLine > *sizeOfArena) { // is the win line valid
            printf("Invalid input, too large for the field \n");
        } else {
            printf("Length of winning line set to %d \n", *sizeOfWinLine);
            break;
        }
    }
}

int move(int sizeOfArena, const int *arena){ // scans player input
    int playerMove = 0;
    while(1) {
        printf("Pick a column in field of size 0 to %d \n", sizeOfArena-1);
        scanf(" %d", &playerMove);
        if(playerMove > sizeOfArena-1){ // Ensures player does not input a move outside the field
            printf("invalid input, too big");
        }else if(playerMove < 0){ // Ensures player does not input a move outside the field
            printf("invalid input, too small");
        }else{
            for (int i = sizeOfArena-1; i >= 0; i--) { // If the move is legal, the function returns it
                int pos = (sizeOfArena * i) + playerMove;
                if (!*(arena + pos)) {
                    return pos;
                }
            }
        }
    }
}
int aiMove(int sizeOfArena, const int *arena){ // Is almost identical to player move, just with rand.
    int aiMove = 0;
    srand(time(NULL));
    while(1) {
        aiMove = rand() % sizeOfArena;
        printf("CPU chooses column %d \n",aiMove);
        if(aiMove > sizeOfArena-1){
            printf("invalid input, too big \n");
        }else if(aiMove < 0){
            printf("invalid input, too small \n");
        }else{
            for (int i = sizeOfArena-1; i >= 0; i--) {
                int pos = (sizeOfArena * i) + aiMove;
                if (!*(arena + pos)) {
                    return pos;
                }
            }
        }
    }
}
void printArena(const int *arena, int sizeOfArena){
    for (int i = 0; i < sizeOfArena; i++){
        for(int j = 0; j < sizeOfArena; j++){
            int pos = i * sizeOfArena + j;
            printf("%d", *(arena+pos));
        }
        printf("\n");
    }
    printf("\n");
}
void updateField(int move, int *arena, int whichPlayer){ // Updates the field based on which player just made a move
    if (!*(arena+move)) {
        *(arena+move) = whichPlayer;
    } else {
        printf("rip bozo");
    }
}
int winCondition(const int *arena, const int sizeOfArena, const int sizeOfWinLine, const int whoseTurn){
    //draw condition - defaults to this if the field is full but no winner is found
    for (int i = 0; i < sizeOfArena*sizeOfArena; i++){
        if (*(arena+i) == 0){
            break;
        }else if (i == sizeOfArena*sizeOfArena-1){
            return 0;
        }
    }
    // row check
    for (int row = sizeOfArena-1; row >= 0; row--) {//start in the bottom right corner
        int length = 0;
        for(int column = 0; column < sizeOfArena ; column++){ //Loop checks the value of the row, one column at a time
            int pos = (sizeOfArena * row)+column; //Position is found
            if (*(arena+pos)==whoseTurn) { //Checks if the position holds the correct value
                length++;
                if(length==sizeOfWinLine)
                    return 1;
            }else{
                length = 0;
            }
        }
    }
    // column check
    for (int column = 0; column < sizeOfArena; column++) { //start in the top left corner
        int length = 0;
        for(int row = 0; row < sizeOfArena ; row++){ //Loop checks the value of the column, one row at a time
            int pos = (sizeOfArena * row)+column; //Position is found
            if (*(arena+pos)==whoseTurn) { //Checks if the position holds the correct value
                length++;
                if(length==sizeOfWinLine){
                    return 1;
                }
            }else{
                length = 0;
            }
        }
    }
    // "/" diagonal check - Bottom left to upwards right
    for (int row = sizeOfArena-1; row >= sizeOfWinLine - 1; row--) { //Start bottom left corner
        for(int column = 0; column <= (sizeOfArena-sizeOfWinLine) ; column++){
            int pos = (sizeOfArena * row)+column; //Position is found
            if (*(arena+pos)==whoseTurn) { //If there is potential for a win enter the loop
                int length = 1;
                for (int l = 1; l <= sizeOfWinLine; l++){ //Loop check the diagonal one row up, one position to the right
                    pos = pos-(sizeOfArena-1);
                    if (*(arena+pos)==whoseTurn) { // Checks until length is long enough to win
                        length++;
                        if(length==sizeOfWinLine){
                            return 1;
                        }
                        continue; // continues to check if it has not found a winning line
                    }else{
                        break; //No winning line is found, terminates the check
                    }
                }
            }
        }
    }
    // "\" diagonal check - Top left to downwards right
     for (int row = 0; row <= (sizeOfArena-sizeOfWinLine); row++) { //start in the top left corner
        for(int column = 0; column <= (sizeOfArena-sizeOfWinLine) ; column++){
            int pos = (sizeOfArena * row)+column; //Position is found
            if (*(arena+pos)==whoseTurn) { //If there is potential for a win enter the loop
                int length = 1;
                for (int l = 1; l <= sizeOfWinLine; l++){ //Loop check the diagonal one row down, one position to the right
                    pos = pos+(sizeOfArena+1);
                    if (*(arena+pos)==whoseTurn) { // Checks until length is long enough to win
                        length++;
                        if(length==sizeOfWinLine){
                            return 1;
                        }
                        continue; // continues to check if it has not found a winning line
                    }else{ //No winning line is found, terminates the check
                        break;
                    }
                }
            }
        }
    }
    return -1;
}