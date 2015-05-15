#include "Evaluation.h"
#include "../main/MiniMax.h"
#include "BoardUtils.h"

// Base score to start with because the score might get lower and we don't want lots of negative number. This is merely a technical issue.
#define BASE_SCORE 500

// The base score for when the mouse can't reach the cheese in the remaining turns must be much lower than than other possibilities.
#define CANT_REACH_CHEESE_BASE_SCORE_MOUSE 0

// The base score for when the mouse can't reach the cheese in the remaining turns must be much higher than than other possibilities.
#define CANT_REACH_CHEESE_BASE_SCORE_CAT BASE_SCORE * 2

// Cat's weights
#define CAT_ALPHA 10
#define CAT_BETA 3

// Mouse's weights
#define MOUSE_ALPHA 10
#define MOUSE_BETA 3
#define MOUSE_GAMMA 1

#define MAX_DISTANCE = BAORD_ROWS + BOARD_COLS + 1;

/* This function is called by the getScoreForState function to calculate the algorithm on the game state. The function receives
the same parameters as the getScoreForState function and returns the algorithm result when finished. */
int innerEvaluate(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn, int isMouseTree) {
	int numTurnsLeftForMouse, mouseToCheese, catToMouse, mouseToCheeseNoCat, diffDistance;
	if (isMouseTurn) {
		numTurnsLeftForMouse = (numTurns + 1) / 2;
	} else {
		numTurnsLeftForMouse = numTurns / 2;
	}
	
	// Calculate shortest distances
	mouseToCheese = calcShortestDistance(board, mousePoint, cheesePoint, catPoint, cheesePoint, 1);
	catToMouse = calcShortestDistance(board, catPoint, mousePoint, catPoint, cheesePoint, 0);
	
	// Can the mouse reach the cheese in the remaining turns?
	if (numTurnsLeftForMouse <= mouseToCheese) {
		if (isMouseTree) {
			return CANT_REACH_CHEESE_BASE_SCORE_MOUSE + catToMouse;
		} else {
			return CANT_REACH_CHEESE_BASE_SCORE_CAT - catToMouse;
		}
	} else {
		// Calculate the diff distance
		mouseToCheeseNoCat = calcShortestDistance(board, mousePoint, cheesePoint, catPoint, cheesePoint, 0);
		diffDistance = mouseToCheese - mouseToCheeseNoCat;
		if (isMouseTree) {
			return BASE_SCORE - MOUSE_ALPHA * mouseToCheese - MOUSE_BETA * diffDistance + MOUSE_GAMMA * catToMouse;
		} else {
			return BASE_SCORE - CAT_ALPHA * catToMouse + CAT_BETA * diffDistance;
		}
	}
}

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn, int isMouseTree) {
	// First check for win - take into account the number of turns left.
	if(isAdjacent(mousePoint, catPoint)) {
		if (isMouseTree) {
			return MIN_EVALUATION + EVALUATION_SHIFT_RESULT_FOR_WIN - numTurns;
		} else {
			return MAX_EVALUATION - EVALUATION_SHIFT_RESULT_FOR_WIN + numTurns;
		}
	} else if(isAdjacent(mousePoint, cheesePoint)) {
		if (isMouseTree) {
			return MAX_EVALUATION - EVALUATION_SHIFT_RESULT_FOR_WIN + numTurns;
		} else {
			return MIN_EVALUATION + EVALUATION_SHIFT_RESULT_FOR_WIN - numTurns;
		}
	}
		
	return innerEvaluate(board, catPoint, mousePoint, cheesePoint, numTurns, isMouseTurn, isMouseTree);
}

