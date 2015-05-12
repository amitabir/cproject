#include "Evaluation.h"
#include "../main/MiniMax.h"
#include "BoardUtils.h"

// TODO remove
#include <stdio.h>

#define BASE_SCORE 500
#define CANT_REACH_CHEESE_BASE_SCORE_MOUSE 0
#define CANT_REACH_CHEESE_BASE_SCORE_CAT BASE_SCORE * 2



#define CANT_REACH_CHEESE_FACTOR 12

#define CAT_ALPHA_BELOW_TURNS 10
#define CAT_BETA_BELOW_TURNS 3
#define CAT_GAMMA_BELOW_TURNS 1

#define CAT_ALPHA_ABOVE_TURNS CAT_ALPHA_BELOW_TURNS
#define CAT_BETA_ABOVE_TURNS CAT_BETA_BELOW_TURNS
#define CAT_GAMMA_ABOVE_TURNS CAT_GAMMA_BELOW_TURNS

#define MOUSE_ALPHA_BELOW_TURNS 10
#define MOUSE_BETA_BELOW_TURNS 3
#define MOUSE_GAMMA_BELOW_TURNS 1

#define MOUSE_ALPHA_ABOVE_TURNS MOUSE_ALPHA_BELOW_TURNS
#define MOUSE_BETA_ABOVE_TURNS MOUSE_BETA_BELOW_TURNS
#define MOUSE_GAMMA_ABOVE_TURNS MOUSE_GAMMA_BELOW_TURNS

#define MAX_DISTANCE = BAORD_ROWS + BOARD_COLS + 1;

/* This function is called by the getScoreForState function to calculate the algorithm on the game state. The function receives
the same parameters as the getScoreForState function and returns the algorithm result when finished. */
int innerEvaluate(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn, int isMouseTree) {
	if (isMouseTree) {
		//printf("Evaluating for Mouse \n");
	} else {
		//printf("Evaluating for Cat \n");
	}
	
	int numTurnsLeftForMouse;
	if (isMouseTurn) {
		numTurnsLeftForMouse = (numTurns + 1) / 2;
	} else {
		numTurnsLeftForMouse = numTurns / 2;
	}
	
	int mouseToCheese =  calcShortestDistance(board, mousePoint, cheesePoint, catPoint, cheesePoint, 1);
	int catToMouse = calcShortestDistance(board, catPoint, mousePoint, catPoint, cheesePoint, 0);
	int mouseToCheeseNoCat = calcShortestDistance(board, mousePoint, cheesePoint, catPoint, cheesePoint, 0);
	int catToCheese = calcShortestDistance(board, catPoint, cheesePoint, catPoint, cheesePoint, 0);
	
	
	// printf("Mouse to Cheese = %d\n", mouseToCheese);
	// printf("Mouse to Cheese no Cat = %d\n", mouseToCheeseNoCat);
	// printf("Cat to mouse = %d\n", catToMouse);
	// printf("Cat to Cheese = %d\n", catToCheese);
	
	if (isMouseTree) {
		if (mouseToCheese == CANNOT_REACH_RESULT && mouseToCheeseNoCat == CANNOT_REACH_RESULT) {
			return CANT_REACH_CHEESE_FACTOR * catToMouse;
		}
	}
	
	
	// if (mouseToCheese == CANNOT_REACH_RESULT && mouseToCheeseNoCat != CANNOT_REACH_RESULT) {
// 		// The cat is blocking the way completely
// 		printf("The cat is blocking the way completely! \n");
// 		if (numTurnsLeftForMouse < 5) {
// 			return -CANT_REACH_CHEESE_FACTOR * catToMouse;
// 		} else {
// 			if (isMouseTree) {
// 					result = -MOUSE_ALPHA_ABOVE_TURNS * mouseToCheeseNoCat + MOUSE_GAMMA_ABOVE_TURNS * catToMouse;
// 			} else {
// 					result = -CAT_ALPHA_ABOVE_TURNS * catToMouse + CAT_BETA_ABOVE_TURNS * 15 - CAT_GAMMA_ABOVE_TURNS * catToCheese;
// 			}
// 		}
	// } else {
	
		if (numTurnsLeftForMouse <= mouseToCheese) {
//			printf("Mouse Can NOT Reach Cheese! \n");
			if (isMouseTree) {
				return CANT_REACH_CHEESE_BASE_SCORE_MOUSE + catToMouse;
			} else {
				return CANT_REACH_CHEESE_BASE_SCORE_CAT - catToMouse;
			}
		} else {
			int diffDistance = mouseToCheese - mouseToCheeseNoCat;
//			printf("Mouse Can Reach Cheese! \n");
			if (isMouseTree) {
				return BASE_SCORE - MOUSE_ALPHA_BELOW_TURNS * mouseToCheese - MOUSE_BETA_BELOW_TURNS * diffDistance +
						 	MOUSE_GAMMA_BELOW_TURNS * catToMouse;
			} else {
				return BASE_SCORE - CAT_ALPHA_BELOW_TURNS * catToMouse + CAT_BETA_BELOW_TURNS * diffDistance;
			}
		}
	// }
	// if (isMouseTree) {
	// 	result *= -1;
	// }
//	printf ("Result is %d\n", result);
	// return 0;
}

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTurn, int isMouseTree) {
	if(isAdjacent(mousePoint, catPoint)) {
		if (isMouseTree) {
			return MIN_EVALUATION + 100 - numTurns;
		} else {
			return MAX_EVALUATION - 100 + numTurns;
		}
	} else if(isAdjacent(mousePoint, cheesePoint)) {
		if (isMouseTree) {
			return MAX_EVALUATION - 100 + numTurns;
		} else {
			return MIN_EVALUATION + 100 - numTurns;
		}
	}
		
	return innerEvaluate(board, catPoint, mousePoint, cheesePoint, numTurns, isMouseTurn, isMouseTree);
}

