#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_
#include "GameConfigModel.h"
#include "BoardPoint.h"
#include "Constants.h"

typedef enum {
	CAT_WINS,
	MOUSE_WINS, 
	DRAW,
	NO_WIN
} WinnerType;

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

char** createBoard();

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
