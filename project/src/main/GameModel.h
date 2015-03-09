#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_
#include "GameConfigModel.h"

typedef enum {
	CAT_WINS,
	MOUSE_WINS, 
	TIE
} WinnerType;

typedef struct game_model {
	GameConfigModel gameConfig;
	WinnerType winType;
	char **board;
	int isMouseTurn;
	int numMovesLeft;
	int isGameOver;
	int isGamePaused;
} GameModel;


#endif /* GAME_MODEL_H_ */
