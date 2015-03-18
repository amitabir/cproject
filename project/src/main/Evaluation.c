#include "Evaluation.h"
#include "MiniMax.h"
#include "BoardPoint.h"

// TODO remove
#include <stdio.h>

// Mouse is min player, cat is max player
int getScoreForState(char **board, BoardPoint catPoint, BoardPoint mousePoint, BoardPoint cheesePoint) {
	float catToMouse, mouseToCheese;
	catToMouse = calcDistance(catPoint, mousePoint);
	mouseToCheese = calcDistance(mousePoint, cheesePoint);
	
	if (catToMouse == 1.0) {
		return MAX_EVALUATION;
	} else if (mouseToCheese == 1.0) {
		return MIN_EVALUATION;
	} else {
		return (int) 10 * mouseToCheese - 10 * catToMouse;
	}
}

