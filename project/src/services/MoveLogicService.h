#ifndef MOVE_LOGIC_SERVICE_H_
#define MOVE_LOGIC_SERVICE_H_

/* This service responsible for finding the best move for a machine player. It does so by executing the minimax algorithm and
 find the best direction to go.*/

#include "../main/ListUtils.h"
#include "../services/BoardPoint.h"
#include "../model/Constants.h"
#include "../model/GameModel.h"

// Number of possible moves
#define NUM_POSSIBLE_MOVES 4

// An array containing the four possible moves
const static MoveDirection possibleMoves[NUM_POSSIBLE_MOVES] = {UP, DOWN, LEFT, RIGHT};

// A struct maintaining the game state during the minimax algorithm run. According to the state, the evaulation function is applied and the evaluation of the state is made.
typedef struct game_state {
	char **board;
	BoardPoint catPoint;
	BoardPoint mousePoint;
	BoardPoint cheesePoint;
	int numTurns;
	int isMouseTurn;
	int isMouseTree;
} GameState;

/* Checks if the current board with the current positions of the cat, mouse and cheese is a winning state of the game.
   Returns the winner - cat, mouse or draw, according to who has won. */
WinnerType hasWinner(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns);

/* Check if moving the given point in the given direction is valid, using the board data and the cheese point location
	 Returns 1 if the move is valid, 0 otherwise. */
int isMoveValid(char **board, BoardPoint cheesePoint, BoardPoint point, MoveDirection direction);

/* This function receives a pointer to a two dimensional int array which represents the game board, and int numberSteps which
represent the number of steps to look forward and an all the game properties, and calculates the best move that should be taken
by the current player. 
 The best move is returned in the bestMove pointer. The function returns 0 on success, 1 otherwise. */
int findBestMoveDirection(char **board, int numTurns, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint,
	 int isMouseTurn, int numberSteps, MoveDirection *bestMove);

#endif /* MOVE_LOGIC_SERVICE_H_ */
