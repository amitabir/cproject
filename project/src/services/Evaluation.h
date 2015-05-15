#ifndef EVAL_H_
#define EVAL_H_

#include "BoardPoint.h"

// The win result will be shifted so we can take into account the depth of the tree (number of turns left).
#define EVALUATION_SHIFT_RESULT_FOR_WIN 100

/* This function receives a two dimensional char array which represents the board with only the walls on it, three BoardPoints which
represents the cat point, mouse point and cheese point and two ints which represents the number of turns left and if it is the mouse's
MiniMax tree or not. The function calculates the score using an appropriate algorithm and returns it as an int. */
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn, int isMouseTree);

#endif /* EVAL_H_ */
