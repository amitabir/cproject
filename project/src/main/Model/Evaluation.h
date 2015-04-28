#ifndef EVAL_H_
#define EVAL_H_

#include "BoardPoint.h"

int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn);

#endif /* EVAL_H_ */
