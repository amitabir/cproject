#include <stdio.h>
#include <stdlib.h>
#include "../src/main/Model/Constants.h"
#include "../src/main/Model/BoardPoint.h"
#include "../src/main/Model/BoardUtils.h"
#include "../src/main/Utils/MiniMax.h"
#include "../src/main/Model/Evaluation.h"
#include <assert.h>

int main() {
// 	GameConfigurationModel *config = createGameConfig(1, 5, 0, 4);
// 	GameModel *game = createGame(config);
//
// 	for (i = 0; i < BOARD_ROWS; i++) {
// 		for (j = 0; j < BOARD_COLS; j++) {
// 			setBoardTile(game, EMPTY_TILE, i, j);
// 		}
// 	}
//
// 	setCatPoint(game, 0, 0);
// 	setMousePoint(game, 0, 6);
// 	setCheesePoint(game, 6, 3);
	
	BoardPoint catPoint, mousePoint, cheesePoint;
	catPoint.row = 0;
	catPoint.col = 0;
	mousePoint.row = 0;
	mousePoint.col = 6;
	cheesePoint.row = 6;
	cheesePoint.col = 3;
	
	char **board = createBoard();
	board[5][4] = WALL_TILE;
	board[5][3] = WALL_TILE;
	board[6][4] = WALL_TILE;
	
	catPoint.row = 1;
	catPoint.col = 0;
	int score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 19, 0);
	printf("Evalution result for moving right is: %d \n", score);
	
	catPoint.row = 0;
	catPoint.col = 1;
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 19, 0);
	printf("Evalution result for moving down is: %d \n", score);
	
	// catPoint.row = 0;
	// catPoint.col = 5;
	// score = getScoreForState((char**) board, catPoint, mousePoint, cheesePoint);
	// assert(score == MAX_EVALUATION && "Cat should be the winner");
	//
	//
	// catPoint.row = 0;
	// catPoint.col = 0;
	// mousePoint.row = 6;
	// mousePoint.col = 2;
	// score = getScoreForState((char**) board, catPoint, mousePoint, cheesePoint);
	// assert(score == MIN_EVALUATION && "Mouse should be the winner");
	//
	// catPoint.row = 6;
	// catPoint.col = 1;
	// mousePoint.row = 6;
	// mousePoint.col = 2;
	// score = getScoreForState((char**) board, catPoint, mousePoint, cheesePoint);
	// assert(score == MAX_EVALUATION && "Cat should be the winner");
}
