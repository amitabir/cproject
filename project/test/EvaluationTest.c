#include <stdio.h>
#include <stdlib.h>
#include "../src/model/Constants.h"
#include "../src/services/BoardPoint.h"
#include "../src/services/BoardUtils.h"
#include "../src/main/MiniMax.h"
#include "../src/services/Evaluation.h"
#include <assert.h>

int main() {
	int isMouseTurn = 1;
	int mousePlayer = 1;
	BoardPoint catPoint = {4, 4};
	BoardPoint mousePoint = {0,0};
	BoardPoint cheesePoint = {3,0};
	
	char **board = createBoard();

	board[3][3] = WALL_TILE;
	board[3][4] = WALL_TILE;
	board[3][5] = WALL_TILE;
	board[3][6] = WALL_TILE;
	
	board[4][0] = WALL_TILE;
	board[4][1] = WALL_TILE;
	
	
	mousePoint.row = 0;
	mousePoint.col = 1;
	int score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 18, !isMouseTurn, mousePlayer);
	printf("Evalution result for mouse moving RIGHT is: %d \n", score);
	
	mousePoint.row = 1;
	mousePoint.col = 0;
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 18, !isMouseTurn, mousePlayer);
	printf("Evalution result for mouse moving DOWN is: %d \n", score);
	
	// Cat moving DOWN once
	catPoint.row = 4;
	catPoint.col = 5;
	
	
	printf("NEXT TURN !!!! \n");
	
	mousePoint.row = 1;
	mousePoint.col = 1;
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 16, !isMouseTurn, mousePlayer);
	printf("Evalution result for mouse moving RIGHT is: %d \n", score);
	
	mousePoint.row = 0;
	mousePoint.col = 0;
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 16, !isMouseTurn, mousePlayer);
	printf("Evalution result for mouse moving UP is: %d \n", score);
	
	mousePoint.row = 2;
	mousePoint.col = 0;
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 16, !isMouseTurn, mousePlayer);
	printf("Evalution result for mouse moving DOWN is: %d \n", score);
	
	// printf("##################\n");
	// catPoint.row = 0;
	// catPoint.col = 6;
	//
	// mousePoint.row = 0;
	// mousePoint.col = 1;
	// score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 4, !isMouseTurn, mousePlayer);
	// printf("Evalution result for mouse moving RIGHT is: %d \n", score);
	//
	// mousePoint.row = 1;
	// mousePoint.col = 0;
	// score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 4, !isMouseTurn, mousePlayer);
	// printf("Evalution result for mouse moving DOWN is: %d \n", score);
	
}
