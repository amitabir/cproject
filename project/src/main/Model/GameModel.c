#include <stdlib.h>
#include <stdio.h>
#include "GameModel.h"
#include "GameConfigModel.h"
#include "WorldFilesService.h"
#include "MoveLogicService.h"
#include "BoardUtils.h"

#define DEFAULT_NUM_TURNS 20
#define DEFAULT_GAME_OVER 0
#define DEFAULT_GAME_PAUSED 0

GameModel *createEmptyGame() {
	GameModel *game;
	
	// Create the game struct
    if ((game = (GameModel*) malloc(sizeof(GameModel))) == NULL) {
		// Malloc has failed and the user is notified
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	
	// Create a new board using the createBoard function
	game->board = createBoard();
	if (game->board == NULL) {
		free(game);
		return NULL;
	}
	
	game->catPoint = createEmptyPoint();
	game->mousePoint = createEmptyPoint();
	game->cheesePoint = createEmptyPoint();
	game->isGameOver = DEFAULT_GAME_OVER;
	game->isPaused = DEFAULT_GAME_PAUSED;
	game->numTurns = DEFAULT_NUM_TURNS;
	game->gameConfig = NULL;
	
	return game;
}

GameModel *createGame(GameConfigurationModel *origGameConfig) {
	GameModel *game = createEmptyGame();
	GameConfigurationModel *gameConfig = createGameConfig(origGameConfig->isCatHuman, origGameConfig->catDifficulty,
		 		origGameConfig->isMouseHuman, origGameConfig->mouseDifficulty, origGameConfig->worldIndex);
	if (gameConfig == NULL) {
		freeGame(game);
		return NULL;
	}
	game->gameConfig = gameConfig;	
	return game;
}

void setBoardTile(GameModel *game, char tile, int row, int col) {
	game->board[row][col] = tile;
}

void setCatPoint(GameModel *game, int row, int col) {
	game->catPoint.row = row;
	game->catPoint.col = col;
}

void setMousePoint(GameModel *game, int row, int col) {
	game->mousePoint.row = row;
	game->mousePoint.col = col;
}

void setCheesePoint(GameModel *game, int row, int col) {
	game->cheesePoint.row = row;
	game->cheesePoint.col = col;
}

void setIsMouseTurn(GameModel *game, int isMouseTurn) {
	game->isMouseTurn = isMouseTurn;
}

void setNumMovesLeft(GameModel *game, int numTurns) {
	game->numTurns = numTurns;
}

void makeMove(GameModel *game, BoardPoint *point, MoveDirection direction) {
	BoardPoint newPoint;

	if (isMoveValid(game->board, game->cheesePoint, *point, direction)) {
		newPoint = getMovedPoint(*point, direction);
		point->row = newPoint.row;
		point->col = newPoint.col;
		
		game->numTurns--;
		game->isMouseTurn = !game->isMouseTurn;
		
		checkGameOver(game);
	}
}

void checkGameOver(GameModel *game) {
	WinnerType winType = hasWinner(game->board, game->catPoint, game->mousePoint, game->cheesePoint, game->numTurns);
	if (winType != NO_WIN) {
		game->winType = winType;
		game->isGameOver = 1;
	} else if (game->numTurns == 0) {
		game->winType = DRAW;
		game->isGameOver = 1;
	}
}

void makeCatMove(GameModel *game, MoveDirection direction) {
	makeMove(game, &(game->catPoint), direction);
}

void makeMouseMove(GameModel *game, MoveDirection direction) {
	makeMove(game, &(game->mousePoint), direction);
}

/* Freeing the game by first using the freeBoard function to free the board and then freeing the game configuration struct and the game itself */
void freeGame(GameModel *game) {
	if (game->board != NULL) {
		freeBoard(game->board);
	}
	if (game->gameConfig != NULL) {
		free(game->gameConfig);
	}
	free(game);
}
