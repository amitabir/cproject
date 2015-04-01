#include "Evaluation.h"
#include "MiniMax.h"
#include "BoardPoint.h"

// TODO remove
#include <stdio.h>

#define INT_MIN -32768
#define INT_MAX 32769

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint) {
	if(isAdjacent(mousePoint, catPoint)){
		return INT_MAX;
	} else if(isAdjacent(mousePoint, cheesePoint)){
		return INT_MIN;
	}
	/*float catToMouseReal, mouseToCheeseReal, catToMouseOpt, mouseToCheeseOpt, catToCheeseReal, mouse, cat, catAndMouse;
	catToMouseReal = calcRealDistance(board, catPoint, mousePoint,0);
	mouseToCheeseReal =  calcRealDistance(board, mousePoint, cheesePoint, 1);
	catToCheeseReal =  calcRealDistance(board, catPoint, cheesePoint, 0);
	catToMouseOpt = calcOptDistance(catPoint, mousePoint);
	mouseToCheeseOpt = calcOptDistance(mousePoint, cheesePoint);
	mouse = mouseToCheeseReal - mouseToCheeseOpt;
	cat = catToMouseReal - catToMouseOpt;
	catAndMouse = mouseToCheeseReal - catToMouseReal - catToCheeseReal;
	return mouse - cat + 3*catAndMouse;*/
}

