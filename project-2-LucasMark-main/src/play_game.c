
#include <stdio.h>
#include "stdlib.h"
#include "gameOfLines.h"

int main(void) {
    int opponentIsAi, sizeOfArena, sizeOfWinLine;
    scanSettings(&opponentIsAi, &sizeOfArena, &sizeOfWinLine);
    gameOfLines(opponentIsAi, sizeOfArena, sizeOfWinLine);
    return 0;
}

void gameOfLines(int opponentIsAi, int sizeOfArena, int sizeOfWinLine) {
    int winner = -1;
    //Define arena memory
    int* arena = (int*)malloc(sizeof(int)*sizeOfArena*sizeOfArena); // the arena is quadratic, i.e.
    //initialize arena
    for (int i = 0; i < sizeOfArena*sizeOfArena; i++){
        *(arena+i) = 0; // dereference for at få den værdi
    }
    printArena(arena,sizeOfArena);
    do {
        int whoseTurn = 1;

        int player1Move;
        if (opponentIsAi==0){
            player1Move = move(sizeOfArena, arena);
        } else {
            player1Move = aiMove(sizeOfArena,arena);
        }
        updateField(player1Move, arena, whoseTurn);
        printArena(arena,sizeOfArena);

        winner = winCondition(arena, sizeOfArena, sizeOfWinLine, whoseTurn);
        if (winner == -1){
            whoseTurn = 2;
            int player2Move = move(sizeOfArena, arena);
            updateField(player2Move, arena,whoseTurn);
            printArena(arena,sizeOfArena);

            winner = winCondition(arena, sizeOfArena, sizeOfWinLine, whoseTurn);
        }
        if(winner > 0){
            printf("The winner is player %d! with a winning line of %d \n", whoseTurn, sizeOfWinLine);
        } else if(winner == 0) {
            printf("Game is a draw!\n");
        }

    } while (winner == -1);
    // Print who won (the_winner).
}