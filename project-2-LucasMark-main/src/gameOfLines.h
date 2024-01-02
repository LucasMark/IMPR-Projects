void scanSettings(int *opponent_is_ai, int *size_of_arena, int *size_of_win_line);
void gameOfLines(int opponent_is_ai, int size_of_arena, int size_of_win_line);
void printArena(const int *arena, int sizeOfArena);
int move(int sizeOfArena, const int *arena);
int aiMove(int size_of_arena, const int *arena);
void updateField(int move, int *arena, int whichPlayer);
int winCondition(const int *arena, int size_of_arena, int size_of_win_line, int whoseTurn);