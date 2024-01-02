#include "stdlib.h"
#include "gameOfLines.h"
#include "assert.h"

/* Not all functions tested due to time constraints */

void testWinConditionDraw(void);
void testWinConditionColumn(void);

int main(void) {
    testWinConditionDraw();
    testWinConditionColumn();
}
void testWinConditionDraw(void){
    int sizeOfArena = 4, expected = 0;
    int sizeOfWinLine = 4;
    int whoseTurn = 2;
    //Define arena memory
    int* arena = (int*)malloc(sizeof(int)*sizeOfArena*sizeOfArena); // the arena is quadratic, i.e.
    //initialize arena
    for (int i = 0; i < sizeOfArena*sizeOfArena; i++){
        *(arena+i) = 1; // dereference for at få den værdi
    }
    int result = winCondition(arena,sizeOfArena,sizeOfWinLine,whoseTurn);
    assert(result == expected);
}

void testWinConditionColumn(void){
    int sizeOfArena = 4, expected = 1;
    int sizeOfWinLine = 4;
    int whoseTurn = 1;
    //Define arena memory
    int* arena = (int*)malloc(sizeof(int)*sizeOfArena*sizeOfArena); // the arena is quadratic, i.e.
    //initialize arena
    for (int i = 0; i < sizeOfArena*sizeOfArena; i++){
        *(arena+i) = 0; // dereference for at få den værdi
    }
    for (int column = 0; column < sizeOfArena; column++){;
        if (!*(arena + column)) {
            *(arena + column)=1;
        }
    }
    int result = winCondition(arena,sizeOfArena,sizeOfWinLine,whoseTurn);
    assert(result == expected);
}