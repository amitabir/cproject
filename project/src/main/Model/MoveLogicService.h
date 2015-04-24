#ifndef MOVE_LOGIC_SERVICE_H_
#define MOVE_LOGIC_SERVICE_H_

#include "../Utils/ListUtils.h"
#include "Constants.h"
#include "BoardPoint.h"
#include "GameModel.h"

#define NUM_POSSIBLE_MOVES 4

const static MoveDirection possibleMoves[NUM_POSSIBLE_MOVES] = {UP, DOWN, LEFT, RIGHT};

typedef struct game_state {
	char **board;
	BoardPoint catPoint;
	BoardPoint mousePoint;
	BoardPoint cheesePoint;
	int numTurns;
	int isMouseTurn;
} GameState;

BoardPoint getMovedPoint(BoardPoint origPoint, MoveDirection direction);

WinnerType hasWinner(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns);

int isMoveValid(char **board, BoardPoint cheesePoint, BoardPoint point, MoveDirection direction);

int findBestMoveDirection(char **board, int numTurns, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint,
	 int isMouseTurn, int numberSteps, MoveDirection *bestMove);

#endif /* MOVE_LOGIC_SERVICE_H_ */
