#include "Evaluation.h"
#include "MiniMax.h"
#include "BoardPoint.h"

// TODO remove
#include <stdio.h>

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint) {
	if(isAdjacent(mousePoint, catPoint)){
		return MAX_EVALUATION;
	} else if(isAdjacent(mousePoint, cheesePoint)){
		return MIN_EVALUATION;
	}
	board[cheesePoint.row][cheesePoint.col] = CHEESE_TILE;
	float catToMouseReal, mouseToCheeseReal, catToMouseOpt, mouseToCheeseOpt, catToCheeseReal, mouse, cat, catAndMouse;
	catToMouseReal = calcRealDistance(board, catPoint, mousePoint,0);
//	printf("Cat to mouse real = %f\n", catToMouseReal);
	mouseToCheeseReal =  calcRealDistance(board, mousePoint, cheesePoint, 1);
//	printf("Mouse to Cheese real = %f\n", mouseToCheeseReal);
	catToCheeseReal =  calcRealDistance(board, catPoint, cheesePoint, 1);
//	printf("Cat to cheese real = %f\n", catToCheeseReal);
	catToMouseOpt = calcOptDistance(catPoint, mousePoint);
//	printf("Cat to mouse opt = %f\n", catToMouseOpt);
	mouseToCheeseOpt = calcOptDistance(mousePoint, cheesePoint);
//	printf("Mouse to cheese opt = %f\n", mouseToCheeseOpt);
	mouse = mouseToCheeseReal - mouseToCheeseOpt;
	cat = catToMouseReal - catToMouseOpt;
	catAndMouse = 4*mouseToCheeseReal - 4*catToMouseReal - catToCheeseReal;
//	printf("result = %f\n", mouse - cat + catAndMouse);
	int result = (int) mouse - cat + catAndMouse;
//	printf("result int = %d\n", -result);
	return result;
}

