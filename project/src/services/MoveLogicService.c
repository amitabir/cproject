#include <stdio.h>
#include <stdlib.h>
#include "MoveLogicService.h"
#include "../main/MiniMax.h"
#include "Evaluation.h"
#include "../main/ListUtils.h"
#include "../model/Constants.h"


// Accessing the array defined in the header file, this method returns the move direction according to the move index.
MoveDirection moveIndexToMoveDirection(int moveIndex) {
	return possibleMoves[moveIndex];
}

// Runs the evaluation function with the mouse as maxPlayer, returns the win type.
WinnerType hasWinner(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns) {
	int score = getScoreForState(board, catPoint, mousePoint, cheesePoint, numTurns, 1, 1);
	if (score == MAX_EVALUATION) {
		return MOUSE_WINS;
	} else if (score == MIN_EVALUATION) {
		return CAT_WINS;
	} else if (numTurns == 0) {
		return DRAW;
	}
	return NO_WIN;
}

// Returns 1 if the move in the given direction is valid, 0 otherwise.
int isMoveValid(char **board, BoardPoint cheesePoint, BoardPoint point, MoveDirection direction) {
	BoardPoint newPoint;
	newPoint = getMovedPoint(point, direction);

	if (newPoint.row >= BOARD_ROWS || newPoint.row < 0 || newPoint.col >= BOARD_COLS || newPoint.col < 0) {
		return 0;
	}

	if (board[newPoint.row][newPoint.col] == WALL_TILE) {
		return 0;
	}
	
	if (newPoint.row == cheesePoint.row &&  newPoint.col == cheesePoint.col) {
		return 0;
	}
	
	return 1;
}

/* This function receives a pointer to a two dimensional int array which represents the game board, an int numTurns
that represents the number of turns and an int isMouseTurn that represents if it's the mouse's turn. Creates a new
GameState with the given parameters. 
Returns NULL pointer if the allocation has failed. */
GameState* createState(char **board, int numTurns, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int isMouseTurn, int isMouseTree) {
	// Creating the state
	GameState *state;
	if ((state = (GameState *) malloc(sizeof(GameState))) == NULL) {
        perror("Error: standard function malloc has failed");
        return NULL;
	}
	// Initializing the state
	state->board = board;
	state->catPoint = catPoint;
	state->mousePoint = mousePoint;
	state->cheesePoint = cheesePoint;
	state->numTurns = numTurns;
	state->isMouseTurn = isMouseTurn;
	state->isMouseTree = isMouseTree;
	return state;
}

/* This function is used by getChildrenList and creates a new state according to its parent. 
This function receives a moveDirection that represents one of the possible move directions indicated by this child.
A new state is created similar to parentState with the numTurns reduced and chancing the current player turn.
 The state is pointer is returned , or NULL in case of an error. */
GameState* createStateFromParent(GameState *parentState, MoveDirection moveDirection) {
	GameState *childState;
	BoardPoint mousePoint = parentState->mousePoint, catPoint = parentState->catPoint;
	
	// Make the move
	if (parentState->isMouseTurn) {
		mousePoint = getMovedPoint(mousePoint, moveDirection);
	} else {
		catPoint = getMovedPoint(catPoint, moveDirection);
	}
	
	// Create new state from parent
	if ((childState = createState(parentState->board, parentState->numTurns - 1, catPoint,
		 		mousePoint, parentState->cheesePoint, !parentState->isMouseTurn, parentState->isMouseTree)) == NULL) {
		return NULL;
	}	
	return childState;
}

// This function receives a void pointer to a state which is a GameState struct pointer. The state is freed
void freeState(void *state){
	// Casting the void pointer to Connect4State
	GameState *gameState = (GameState *) state;
	// Freeing the state
	free(gameState);
}

// Returns the current player's point on the board.
BoardPoint getPlayerPoint(GameState *gameState) {
	if (gameState->isMouseTurn) {
		return gameState->mousePoint;
	} else {
		return gameState->catPoint;
	}
}

/* This function receives a void pointer state which is a GameState struct pointer and return a ListRef to its children list.
 A child is created for every move direction that is valid. If there is a winner, an empty list is returned. */
ListRef getGameStateChildren(void *state) {
	// Casting the void pointer to GameState pointer
	GameState *gameState = (GameState *) state;
 	ListRef childrenList = newList(NULL);
	
	// If the game isn't won yet - find the list of the children
	if (hasWinner(gameState->board, gameState->catPoint, gameState->mousePoint, gameState->cheesePoint, gameState->numTurns) == NO_WIN) {
 		int moveIndex;
		ListRef tempList = childrenList;
		BoardPoint playerPoint = getPlayerPoint(gameState);
 		
		// Going through the possible moves and creating a child for each one that is valid
 		for (moveIndex = 0; moveIndex < NUM_POSSIBLE_MOVES; moveIndex++) {
			if (isMoveValid(gameState->board, gameState->cheesePoint, playerPoint, moveIndexToMoveDirection(moveIndex))) {
				GameState *childState = createStateFromParent(gameState, moveIndexToMoveDirection(moveIndex));
				if (childState == NULL) { // standart function failed
					destroyList(childrenList, freeState);
					return NULL;
				}
 				tempList = append(tempList, childState);
 			}
		}
	}
 	return childrenList;
 }

/* This function receives a void pointer which is a GameState struct pointer. The score of the board is calculated
by executing the moves in the moves list, using the calScoreForBoard function and then removing the moves in the moves list
to restore the initial board. The score is returned */
int stateEvaluation(void *state) {
	GameState *gameState = (GameState *) state;
	int score = getScoreForState(gameState->board, gameState->catPoint, gameState->mousePoint, gameState->cheesePoint, gameState->numTurns,
		 		gameState->isMouseTurn, gameState->isMouseTree);
	return score;
}

/* This function receives a pointer to the game state and an int chilIndex and returns the index of the direction of the move that this child represents. 
The child index is not necessarily the move index since some of the moves may be invalid.  */
int childIndexToMoveIndex(GameState *gameState, int childIndex)  {
	int availableMoves = 0, moveIndex, result = -1;
	BoardPoint playerPoint = getPlayerPoint(gameState);
	
	for (moveIndex = 0; moveIndex < NUM_POSSIBLE_MOVES; moveIndex++) {
		if (isMoveValid(gameState->board, gameState->cheesePoint, playerPoint, moveIndexToMoveDirection(moveIndex))) {
			// If the available moves count equals the childIndex, it means we've found the right move.
			if (availableMoves == childIndex) {
				result = moveIndex;
				break;
			}
			availableMoves++;
		}
	}
	return result;
}

// Returns the best possible move for the current player using minimax - see header for doc.
int findBestMoveDirection(char **board, int numTurns, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint,
	 	int isMouseTurn, int numberSteps, MoveDirection *bestMove) {
				
	// Creating an initial state
	int bestMoveIndex;
	GameState *initialState = createState(board, numTurns, catPoint, mousePoint, cheesePoint, isMouseTurn, isMouseTurn);
	if (initialState == NULL) { // If state creation has failed
		return 0;
	}
	// Getting the best child using the MiniMax algorithm
	struct MiniMaxResult result = getBestChild(initialState, numberSteps, getGameStateChildren, freeState, stateEvaluation, 1,
		 												MIN_EVALUATION, MAX_EVALUATION);
	
	// An index -1 returned means that the getBestChild method has failed (due to standart function error).
	if (result.index == -1) {
		freeState(initialState);
		return 0;
	}
	
	bestMoveIndex = childIndexToMoveIndex(initialState, result.index);
	freeState(initialState);
	*bestMove = moveIndexToMoveDirection(bestMoveIndex);
	return 1;
}
