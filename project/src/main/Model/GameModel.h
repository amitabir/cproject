#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_
#include "GameConfigModel.h"
#include "BoardPoint.h"
#include "Constants.h"

/* WinnerType enum which represents if the mouse wins, the cat wins, there's a draw or no winner yet. */
typedef enum {
	CAT_WINS,
	MOUSE_WINS, 
	DRAW,
	NO_WIN
} WinnerType;

/* The GameModel struct defines the game model and all necessary fields to describe it. */
typedef struct game_model {
	GameConfigurationModel *gameConfig;
	WinnerType winType;
	char **board;
	BoardPoint catPoint;
	BoardPoint mousePoint;
	BoardPoint cheesePoint;
	int isMouseTurn;
	int numTurns;
	int isGameOver;
	int isPaused;
	char *validMsg;
} GameModel;

/* This function creates a two dimensional char array of size BOARD_ROWS*BOARD_COLS by dynamical
 allocation and sets it to contain '#' which is an empty slot. */
char** createBoard();

/* This function receives a two dimensional char array of size BOARD_ROWS*BOARD_COLS and frees it. */
void freeBoard(char **board);

GameModel *createEmptyGame();

GameModel *createGame(GameConfigurationModel *gameConfig);

void setBoardTile(GameModel *game, char tile, int row, int col);

void setCatPoint(GameModel *game, int row, int col);

void setMousePoint(GameModel *game, int row, int col);

void setCheesePoint(GameModel *game, int row, int col);

void setIsMouseTurn(GameModel *game, int isMouseTurn);

void setNumMovesLeft(GameModel *game, int numTurns);

void makeCatMove(GameModel *game, MoveDirection direction);

void makeMouseMove(GameModel *game, MoveDirection direction);

void checkGameOver(GameModel *game);

void freeGame(GameModel *game);

#endif /* GAME_MODEL_H_ */
