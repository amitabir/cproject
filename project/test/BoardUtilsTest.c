#include "../src/services/BoardPoint.h"
#include "../src/services/BoardUtils.h"
#include <assert.h>

int main() {
	int i;
	char **board = createBoard();
	BoardPoint mouse = {0, 0};
	BoardPoint cat = {6,6};
	BoardPoint cheese = {3,3};
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == 5 && "Distance should be 5");
	assert(calcShortestDistance(board, cat, cheese, cat, cheese, 0) == 5 && "Distance should be 5");
	assert(calcShortestDistance(board, mouse, cat, cat, cheese, 0) == 11 && "Distance should be 11");
		
	board[2][3] = WALL_TILE;
	board[3][2] = WALL_TILE;
	board[2][2] = WALL_TILE;
	
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == 7 && "Distance should be 7");
	
	board[4][2] = WALL_TILE;
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == 7  && "Distance should be 7");
	
	board[2][4] = WALL_TILE;
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == 9 && "Distance should be 9");
	
	// Reset Board
	board = createBoard();
	cat.row = 2;
	cat.col = 2;
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == 7 && "Distance should be 7"); // Cat is blocking the way
	
	cat.row = 6;
	cat.col = 6;
	// Setting a row of walls
	for (i = 0; i < BOARD_COLS; i++) {
		board[2][i] = WALL_TILE;
	} 
	
	// Now they are both blocked
	assert(calcShortestDistance(board, mouse, cheese, cat, cheese, 1) == CANNOT_REACH_RESULT && "Cannot reach cheese");
	assert(calcShortestDistance(board, cat, mouse, cat, cheese, 0) == CANNOT_REACH_RESULT && "Cannot reach cat");
	
	printf("Success! \n");
}
