#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "Constants.h"

/* This header file is the interface fo game operations, such as start, restart, addDisc and so on. */

#define NUM_OF_DASHES 17

/* The game struct - where the magic happens. The struct has 4 fields - 
a) a pointer to a two dimensional int array which represents the board - **board
b) an int isUserTurn to represent if this is the user's turn or the computer's turn
c) an int isGameOver to represent if the game is over
d) an int numberOfSteps to represent the number of steps forward to take to account while calculating the best move */
typedef struct Game {
	int **board;
	int isUserTurn;
	int isGameOver;
	int numberSteps;
} Connect4Game;

/* This function receives a poiner to the game and then prints the game board as requaired */
void printBoard(Connect4Game *game);

/* This function receives a pointer to the game and an int to represent a column index.
If the column represented by colIndex is full then 1 is returned, otherwise 0 is returned. */
int isGameColumnFull(Connect4Game *game, int colIndex);

/* This function receives a pointer to the game. If the board is full then the isGameOver field 
of the game is updated and 1 is returnes, otherwise 0 is returned.*/
int checkBoardFull(Connect4Game *game);

/* This function receives a pointer to the game and an int to represent a column index.
A disc is inserted in the right column by using the game indicator to whose turn it is.
The game board is updated. */
void addDisc(Connect4Game *game, int col_index);

/* This function receives a pointer to the game and an int to represent the number of steps forward to take to account
while calculating the best move. The game field to represent this value is changed but nothing is returned. */
void setNumberSteps(Connect4Game *game, int numberSteps);

/* This function receives a pointer to the game and reurns 1 if and only if the field numberSteps is initialized */
int isNumberStepsSet(Connect4Game *game);

/* This function receives a pointer to the game, initializes and starts it. If the board creation has failed a 0 is
returned and otherwise 1 is returned. */
int startGame(Connect4Game *game);

/* This function receives a pointer to the game and restarts it. After the execution of this method a new game can be started. */
void restartGame(Connect4Game *game);

/* This function receives a pointer to the game and frees the game and everything associated with it */
void freeGame(Connect4Game *game);

/* This function receives a pointer to the game and calculates the best move for the user to make.
The number of column of the recommended move is returned. */
int findBestUserMove(Connect4Game *game);

/* This function receives a pointer to the game and make the computer move. If no error has occured then 0 is returned, otherwise 1 is returned */
int makeComputerMove(Connect4Game *game);

#endif /* GAMELOGIC_H_ */
