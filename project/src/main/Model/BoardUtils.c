#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"
#include "BoardUtils.h"
#include "../Utils/ListUtils.h"

/* This function dynamically allocates the game board (two dimensional char array). 
   Returns NULL pointer if the malloc has failed. */
char** createBoard() {
        char **board;
        int i, j;
			
        if ((board = (char**)malloc(BOARD_ROWS * sizeof(char*))) == NULL) {
                perror("Error: standard function malloc has failed");
                return NULL;
        }

        for (i = 0; i < BOARD_ROWS; i++) {
                if ((board[i] = (char*)malloc(BOARD_COLS * sizeof(char))) == NULL) {
                    perror("Error: standard function malloc has failed");
					free(board);
                    return NULL;
                }
        }
		
		// Init board with empty tiles
		for (i = 0; i < BOARD_ROWS; i++) {
			for (j = 0; j < BOARD_COLS; j++) {
				board[i][j] = EMPTY_TILE;
			}
		}
		
        return board;
}

void getMovedPoint2(BoardPoint *origPoint, BoardPoint *destPoint, MoveDirection direction) {
	destPoint->row = origPoint->row;
	destPoint->col = origPoint->col;
	destPoint->dist = origPoint->dist + 1;
        switch(direction) {
                case UP:
                        destPoint->row--;
                        break;
                case DOWN:
                        destPoint->row++;
                        break;
                case LEFT:
                        destPoint->col--;
                        break;
                case RIGHT:
                        destPoint->col++;
                        break;
                default:
                        break;
      	}
}

int isCatAround(char **board, BoardPoint point){
	int i = point.row, j = point.col;
	if(board[i+1][j] == CAT_TILE || board[i-1][j] == CAT_TILE || board[i][j+1] == CAT_TILE || board[i][j-1] == CAT_TILE){
		return 1;
	}
	return 0;
}

BoardPoint *makeValidMove(char **board, BoardPoint *point, MoveDirection direction) {
        BoardPoint *newPoint = (BoardPoint *) malloc(sizeof(BoardPoint));
        getMovedPoint2(point, newPoint, direction);
        if (newPoint->row >= BOARD_ROWS || newPoint->row < 0 || newPoint->col >= BOARD_COLS || newPoint->col < 0) {
			free(newPoint);
			return NULL;
        }

        if (board[newPoint->row][newPoint->col] == WALL_TILE || board[newPoint->row][newPoint->col] == CHEESE_TILE) {
			free(newPoint);
			return NULL;
        }

        return newPoint;
}


float calcOptDistance(BoardPoint point1, BoardPoint point2){
	return abs(point1.col - point2.col) + abs(point1.row - point2.row);
}

void printBoard(char **board) {
	int i,j;
	for(i = 0; i < BOARD_ROWS; i++) {
		for(j = 0; j < BOARD_COLS; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

char** copyBoard(char **board) {
	char **boardCopy = createBoard();
	if(boardCopy == NULL){
		//TODO
	}
	int i,j;
	for(i = 0; i < BOARD_ROWS; i++){
		for(j = 0; j < BOARD_COLS; j++){
			boardCopy[i][j] = board[i][j];
// 			if(!isMouse && board[i][j] == CHEESE_TILE){
// //				printf("Cheese!\n");
// 				boardCopy[i][j] = WALL_TILE;
// 			}
		}
	}
	return boardCopy;
}

void surroundCatWithWalls(char **board, BoardPoint catPoint) {
	int i,j;
	for (i = catPoint.row - 1; i <= catPoint.row + 1; i++) {
		for (j = catPoint.col - 1; j <= catPoint.col + 1; j++) {
			if (i >= 0 && i < BOARD_ROWS && j >=0 && j < BOARD_COLS) {
				board[i][j] = WALL_TILE;
			}
		}
	}
}

int calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, BoardPoint catPoint, int isMouse) { 
	int result = CANNOT_REACH_RESULT;
	char **boardCopy = copyBoard(board);
	
	if (isMouse) {
		surroundCatWithWalls(boardCopy, catPoint);
	}
	
	BoardPoint *point;
	BoardPoint *originCopy = (BoardPoint *) malloc(sizeof(BoardPoint));
	originCopy->row = origin.row;
	originCopy->col = origin.col;
	originCopy->dist = 0;
	int found = 0;
	ListRef queue = newList(originCopy);
	ListRef queueHead = queue;
	while(queue != NULL && !isEmpty(queue) && !found){
		point = (BoardPoint *) headData(queue);
		boardCopy[point->row][point->col] = WALL_TILE;

		int moveDirection;
		for (moveDirection = 0; moveDirection < 4; moveDirection++) {
			BoardPoint *movedPoint = makeValidMove(boardCopy, point, moveDirection);
			if(movedPoint != NULL) {
				if (isAdjacent(*movedPoint, destination)) {
					result = movedPoint->dist;
					found = 1;
					free(movedPoint);
					break;
				}
				boardCopy[movedPoint->row][movedPoint->col] = WALL_TILE;
				// printf("\n\n\n\n");
// 				printBoard(boardCopy);
				append(queue, movedPoint);
			}
		}
		queue = tail(queue);
	}
	freeBoard(boardCopy);
	destroyList(queueHead, free);
	return result;
}

/* This function receives a pointer to the board and frees it first by going through all of the rows and freeing
the columns and at the end freeing the board pointer */
void freeBoard(char **board) {
	int i;
	for (i = 0; i < BOARD_ROWS ; i++) {
		free(board[i]);	
	}
	free(board);
}

