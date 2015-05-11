#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_

/* The game model for the whole application */

#include "GameConfigModel.h"
#include "../services/BoardPoint.h"


/* WinnerType enum which represents if the mouse wins, the cat wins, there's a draw or no winner yet. */
typedef enum {
	CAT_WINS,
	MOUSE_WINS, 
	DRAW,
	NO_WIN
} WinnerType;

/* The GameModel struct defines the game model and all necessary fields to describe it. */
typedef struct game_model {
	GameConfigurationModel *gameConfig; // The configuration model for the game
	WinnerType winType; // If there is a winner - contains the win type (cat/mouse/draw)
	char **board; // The board representing the grid with the walls, the cheese/cat/mouse are represented as BoardPoints.
	BoardPoint catPoint; // A board point representing the cat current position on the grid.
	BoardPoint mousePoint; // A board point representing the mouse current position on the grid.
	BoardPoint cheesePoint; // A board point representing the cheese current (and fixed) position on the grid.
	int isMouseTurn; // A flag specifing if the current turn is the mouse's turn.
	int numTurns; // Number of turn left to the end of the game.
	int isGameOver; // A flag specifying if the game is over.
	int isPaused; // A flag specifying if the game is paused.
	char *validMsg; // A validation message if some content is missing the game (used for game editing).
} GameModel;

/* This function creates a two dimensional char array of size BOARD_ROWS*BOARD_COLS by dynamical
 allocation and sets it to contain '#' which is an empty slot. */
char** createBoard();

/* This function receives a two dimensional char array of size BOARD_ROWS*BOARD_COLS and frees it. */
void freeBoard(char **board);

/* Creates an empty game with all default properties.
	 Returns the created game or NULL on error. */
GameModel *createEmptyGame();

/* Creates an a game and initializing it with a configuration
	 Returns the created game or NULL on error. */
GameModel *createGame(GameConfigurationModel *gameConfig);

/* Sets a board tile on the board. */
void setBoardTile(GameModel *game, char tile, int row, int col);

/* Sets the cat point for the game. */
void setCatPoint(GameModel *game, int row, int col);

/* Sets the mouse point for the game. */
void setMousePoint(GameModel *game, int row, int col);

/* Sets the cheese point for the game. */
void setCheesePoint(GameModel *game, int row, int col);

/* Sets the current turn player for the game. */
void setIsMouseTurn(GameModel *game, int isMouseTurn);

/* Sets the number of moves left for the game. */
void setNumMovesLeft(GameModel *game, int numTurns);

/* Move the cat position in the given direction. */
void makeCatMove(GameModel *game, MoveDirection direction);

/* Move the mouse position in the given direction. */
void makeMouseMove(GameModel *game, MoveDirection direction);

/* Check if game is over and update isGameOver flag */
void checkGameOver(GameModel *game);

/* Free the game model and all its pointers */
void freeGame(GameModel *game);

#endif /* GAME_MODEL_H_ */
