#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"

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

/* This function receives a pointer to the board and frees it first by going through all of the rows and freeing
the columns and at the end freeing the board pointer */
void freeBoard(char **board) {
	int i;
	for (i = 0; i < BOARD_ROWS ; i++) {
		free(board[i]);	
	}
	free(board);
}

