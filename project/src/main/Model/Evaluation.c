#include "Evaluation.h"
#include "../Utils/MiniMax.h"
#include "BoardUtils.h"

// TODO remove
#include <stdio.h>

#define CANT_REACH_CHEESE_FACTOR 12

#define CAT_ALPHA_BELOW_TURNS 10
#define CAT_BETA_BELOW_TURNS 3
#define CAT_GAMMA_BELOW_TURNS 1

#define CAT_ALPHA_ABOVE_TURNS 5
#define CAT_BETA_ABOVE_TURNS 4
#define CAT_GAMMA_ABOVE_TURNS 1

#define MOUSE_ALPHA_BELOW_TURNS 10
#define MOUSE_BETA_BELOW_TURNS 3
#define MOUSE_GAMMA_BELOW_TURNS 1

#define MOUSE_ALPHA_ABOVE_TURNS 5
#define MOUSE_BETA_ABOVE_TURNS 4
#define MOUSE_GAMMA_ABOVE_TURNS 1

/* This function is called by the getScoreForState function to calculate the algorithm on the game state. The function receives
the same parameters as the getScoreForState function and returns the algorithm result when finished. */
int innerEvaluate(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTree) {
	if (isMouseTree) {
//		printf("Evaluating for Mouse \n");
	} else {
//		printf("Evaluating for Cat \n");
	}
	
	int result;
	int numTurnsLeftForMouse = (numTurns + 1) / 2;
	
	int mouseToCheese =  calcRealDistance(board, mousePoint, cheesePoint, catPoint, 1);
	int catToMouse = calcRealDistance(board, catPoint, mousePoint, catPoint, 0);
	int mouseToCheeseNoCat = calcRealDistance(board, mousePoint, cheesePoint, catPoint, 0);
	int catToCheese = calcRealDistance(board, catPoint, cheesePoint, catPoint, 0);
	
	
//	printf("Mouse to Cheese = %d\n", mouseToCheese);
//	printf("Mouse to Cheese no Cat = %d\n", mouseToCheeseNoCat);
//	printf("Cat to mouse = %d\n", catToMouse);
//	printf("Cat to Cheese = %d\n", catToCheese);
	
	if (mouseToCheese == CANNOT_REACH_RESULT && mouseToCheeseNoCat != CANNOT_REACH_RESULT) {
		// The cat is blocking the way completely
		printf("The cat is blocking the way completely! \n");
		if (numTurnsLeftForMouse < 5) {
			return -CANT_REACH_CHEESE_FACTOR * catToMouse;
		} else {
			if (isMouseTree) {
					result = -MOUSE_ALPHA_ABOVE_TURNS * mouseToCheeseNoCat + MOUSE_GAMMA_ABOVE_TURNS * catToMouse;
			} else {
					result = -CAT_ALPHA_ABOVE_TURNS * catToMouse + CAT_BETA_ABOVE_TURNS * 15 - CAT_GAMMA_ABOVE_TURNS * catToCheese;
			}
		}
	} else {
	
		if (numTurnsLeftForMouse <= mouseToCheese) {
//			printf("Mouse Can NOT Reach Cheese! \n");
			result = -CANT_REACH_CHEESE_FACTOR * catToMouse;
		} else {
			int diffDistance = mouseToCheese - mouseToCheeseNoCat;
//			printf("Mouse Can Reach Cheese! \n");
			if (isMouseTree) {
				if (numTurnsLeftForMouse < 5) {
					result = -MOUSE_ALPHA_BELOW_TURNS * mouseToCheese - MOUSE_BETA_BELOW_TURNS * diffDistance + MOUSE_GAMMA_BELOW_TURNS * catToMouse;
				} else {
					result = -MOUSE_ALPHA_ABOVE_TURNS * mouseToCheese - MOUSE_BETA_ABOVE_TURNS * diffDistance + MOUSE_GAMMA_ABOVE_TURNS * catToMouse;
				}
			} else {
				if (numTurnsLeftForMouse < 5) {
					result = -CAT_ALPHA_BELOW_TURNS * catToMouse + CAT_BETA_BELOW_TURNS * diffDistance - CAT_GAMMA_BELOW_TURNS * catToCheese;
				} else {
					result = -CAT_ALPHA_ABOVE_TURNS * catToMouse + CAT_BETA_ABOVE_TURNS * diffDistance - CAT_GAMMA_ABOVE_TURNS * catToCheese;
				}
			}
		}
	}
	if (isMouseTree) {
		result *= -1;
	}
//	printf ("Result is %d\n", result);
	return result;
}

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint, int numTurns, int isMouseTree) {
	if(isAdjacent(mousePoint, catPoint)){
		return MAX_EVALUATION;
	} else if(isAdjacent(mousePoint, cheesePoint)){
		return MIN_EVALUATION;
	}
	
	board[cheesePoint.row][cheesePoint.col] = CHEESE_TILE;
	
	return innerEvaluate(board, catPoint, mousePoint, cheesePoint, numTurns, isMouseTree);
}

