#include <stdlib.h>
#include <stdio.h>
#include "BoardUtils.h"
#include "../model/Constants.h"
#include "../main/ListUtils.h"

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

/* This function receives two BoardPoint pointers, an origin point and a destination point and a MoveDirection and puts
inside the destination point the moved origin point by the MoveDirection. */
void getMovedPointDist(BoardPoint *origPoint, BoardPoint *destPoint, MoveDirection direction) {
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

/* This function receives the gaming board, a BoardPoint pointer and a moveDirection and returns a BoardPoint pointer to the moved original
point moved by MoveDirection. */
BoardPoint *makeValidMove(char **board, BoardPoint *point, MoveDirection direction) {
        BoardPoint *newPoint = (BoardPoint *) malloc(sizeof(BoardPoint));
        getMovedPointDist(point, newPoint, direction);
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

/* This function receives a two dimensional char array and creates a new copy of it and returns it. */
char** copyBoard(char **board) {
	char **boardCopy = createBoard();
	if (boardCopy == NULL){
		return NULL;
	}
	int i,j;
	for(i = 0; i < BOARD_ROWS; i++){
		for(j = 0; j < BOARD_COLS; j++){
			boardCopy[i][j] = board[i][j];
		}
	}
	return boardCopy;
}

/* This function receives the gaming board and a BoardPoint which represents the cat position. Every point around the cat is set
 to be wall if possible, i.e. is in the board. */
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

// Calculates shortest distance betwen origin and destination - see header for doc.
int calcShortestDistance(char **board, BoardPoint origin, BoardPoint destination, BoardPoint catPoint, BoardPoint cheesePoint, int isMouse) { 
	int result = CANNOT_REACH_RESULT;
	// Firts copy the board
	char **boardCopy = copyBoard(board);
	
	// Set the cheese tile in the board.
	boardCopy[cheesePoint.row][cheesePoint.col] = CHEESE_TILE;
	
	// The mouse can't go anywhere near the cat, so we replace the cat with 3x3 walls.
	if (isMouse) {
		surroundCatWithWalls(boardCopy, catPoint);
	}
	
	// Create the graph nodes
	BoardPoint *point;
	BoardPoint *originCopy = (BoardPoint *) malloc(sizeof(BoardPoint));
	originCopy->row = origin.row;
	originCopy->col = origin.col;
	originCopy->dist = 0;
	int found = 0;
	
	// Initialized the queue for the BFS algorithm
	ListRef queue = newList(originCopy);
	ListRef queueHead = queue;
	
	// Extract the head of the queue, check adjacent nodes and mark their shortest distance
	while(queue != NULL && !isEmpty(queue) && !found){
		point = (BoardPoint *) headData(queue);
		boardCopy[point->row][point->col] = WALL_TILE; // Mark the point as visited

		int moveDirection;
		// A valid move means there is an edge in the graph
		for (moveDirection = 0; moveDirection < 4; moveDirection++) {
			BoardPoint *movedPoint = makeValidMove(boardCopy, point, moveDirection);
			if(movedPoint != NULL) {
				// Check if we have reached the destination
				if (isAdjacent(*movedPoint, destination)) {
					result = movedPoint->dist;
					found = 1;
					free(movedPoint);
					break;
				}
				boardCopy[movedPoint->row][movedPoint->col] = WALL_TILE; // Mark the point as visited
				append(queue, movedPoint);
			}
		}
		queue = tail(queue);
	}
	// Free resources
	freeBoard(boardCopy);
	destroyList(queueHead, free);
	return result;
}

/* This function receives a pointer to the board and frees it first by going through all of the rows and freeing
the columns and at the end freeing the board pointer */
void freeBoard(char **board) {
	int i;
	for (i = 0; i < BOARD_ROWS ; i++) {
		if (board[i] != NULL) {
			free(board[i]);	
		}
	}
	free(board);
}

