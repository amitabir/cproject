#include "GameLogic.h"
#include "MoveLogic.h"
#include <stdio.h>
#include <stdlib.h>

/* This function uses the isColumnFull function to get the answer to is colIndex column is full */
int isGameColumnFull(Connect4Game *game, int colIndex) {
	return isColumnFull(game->board, colIndex);
}

/* This function gows over on all of the columns of the board and check if each column is full. If at least one
is empty then a 0 is returned, otherwise 1 is returned. Also updates the isGameOver flag of the game to indicate that the game is over. */
int checkBoardFull(Connect4Game *game) {
	int colIndex;
	// the loop that runs on all the columns
	for (colIndex = 0; colIndex < BOARD_COLS; colIndex++) {
		if(!isGameColumnFull(game, colIndex)) {
			// The column is not full - 0 must be returned
			return 0;
		}
	}
	// Updating that the game is over
	game->isGameOver = 1;
	// The board is full - 1 must be returned
	return 1;
}

/* This function goes throgh the rows of column colIndex until it reaches the first empty one
(could be the first). Then a Disc is inserted in the desired location. At the end gameWon function
is used to check if the game is over and if so the game is updated.*/
void addDisc(Connect4Game *game, int colIndex) {
	// Find first empty slot in the given column
	int rowIndex = 0;
	while (game->board[rowIndex][colIndex] != NO_DISC) {
		rowIndex++;
	}
	// Add disc according to the current turn
	game->board[rowIndex][colIndex] = game->isUserTurn ? USER_DISC : COMP_DISC;
	
	// Check for win  or full board- update game properties
	if (gameWon(game->board)) {
		game->isGameOver = 1;
	}
}

/* This function dynamically allocates the game board (two dimensional array). 
   Returns NULL pointer if the malloc has failed. */
int** createBoard() {
        int **board;
        int i;
			
        if ((board = (int**)malloc(BOARD_ROWS * sizeof(int*))) == NULL) {
                perror("Error: standard function malloc has failed");
                return NULL;
        }

        for (i = 0; i < BOARD_ROWS; i++) {
                if ((board[i] = (int*)malloc(BOARD_COLS * sizeof(int))) == NULL) {
                    perror("Error: standard function malloc has failed");
					free(board);
                    return NULL;
                }
        }
        return board;
}

/* This function receives an int wich represent the one of three : user disc, computer disc or no disc.
A char that suits the type is returned. */
char getBoardChar(int type) {
	switch (type) {
		case USER_DISC:
			return 'O';
		case COMP_DISC:
			return 'X';
		default:
			return ' ';
	}
}

/* This function prints the board to graphically show the user how the game progresses. It uses constant definitions
   to print the correct symbol for every slot in the graphical view. */
void printBoard(Connect4Game *game) {
	int i,j;
	for (i = BOARD_ROWS-1; i >= 0; i--) {
		printf("| ");
		for (j = 0; j < BOARD_COLS; j++) {
			printf("%c ", getBoardChar(game->board[i][j]));
		}
		printf("|\n");
	}
	for (i = 0; i < NUM_OF_DASHES; i++) {
		printf("-");
	}
	printf("\n  ");
	for (j = 0; j < BOARD_COLS; j++) {
		printf("%d", j+1);
		if (j != BOARD_COLS - 1) {
			printf(" ");
		}
	}
	printf("  \n");
}

// Init board with NO_DISC for all slots
void initBoard(int **board) {
	int i,j;
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			board[i][j] = NO_DISC;
		}
	}
}

// Set number of steps to calculate when determining computer's move or user move suggestion.
void setNumberSteps(Connect4Game *game, int numberSteps) {
	game->numberSteps = numberSteps;
}

// Retruns true if the number of steps property has been set.
int isNumberStepsSet(Connect4Game *game) {
	return game->numberSteps != -1;
}

/* Helper function that receives a pointer to the game and initailizes it - fill the board with empty slots and init the flags. */
void initGame(Connect4Game *game) {
	// Using initBoard to initialize the game board
	initBoard(game->board);
	// Initializing rest of the game fields
	game->isUserTurn = 1;
	game->isGameOver = 0;
	game->numberSteps = -1;
}

/* Inintializing a new game received in the pointer given.
	Returns 1 if the initialization has succeeded, 0 otherwise. */
int startGame(Connect4Game *game) {
	// Creating a new board using the createBoard function
	game->board = createBoard();
	if (game->board == NULL) {
		// Board creation has failed - 0 is returned.
		return 0;
	}
	// Using initGame to initialize the game
	initGame(game);
	return 1;
}

/* Receiving a pointer to an existing game and restarting it by setting all the flags to initial values and clear the board. */
void restartGame(Connect4Game *game) {
	initGame(game);
}

/* By using the function findBestMove the best move for the user is found and returned*/
int findBestUserMove(Connect4Game *game) {
	return findBestMove(game->board, game->numberSteps, game->isUserTurn);
}

/* This function first changes the game field isUserTurn such so it is the computer's turn. Then it
uses the findBestMove function to find the computer's move and executes it. */
int makeComputerMove(Connect4Game *game) {
	// Changing it to be the computer's turn
	game->isUserTurn = 0;
	// The best move is found
	int bestMoveIndex = findBestMove(game->board, game->numberSteps, game->isUserTurn);
	if (bestMoveIndex == -1) { // some fatal error occured
		return 0;
	}
	// Printing to the user the computer move
	printf("Computer move: add disc to column [%d].\n", bestMoveIndex + 1);
	// Adding the computer's disc in the right place
	addDisc(game, bestMoveIndex);
	// It is now again the user's turn
	game->isUserTurn = 1;
	return 1;
}

/* This function receives a pointer to the board and frees it first by going through all of the rows and freeing
the columns and at the end freeing the board pointer */
void freeBoard(int **board) {
	int i;
	for (i = 0; i < BOARD_ROWS ; i++) {
		free(board[i]);	
	}
	free(board);
}

/* Freeing the game by first using the freeBoard function to free the board and then freeing the game */
void freeGame(Connect4Game *game) {
	if (game->board != NULL) {
		freeBoard(game->board);
	}
	free(game);
}
