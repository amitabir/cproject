#include <stdio.h>
#include <stdlib.h>
#include "GameLogicService.h"
#include "MoveLogicService.h"
#include "../model/GameModel.h"
#include "../model/Constants.h"
#include "../model/GameConfigModel.h"

// Handles machine move - see header for doc.
int handleMachineMove(GameModel *game) {
	int numberSteps;
	MoveDirection bestMove;
	
	if (game->isMouseTurn) {
		numberSteps = game->gameConfig->mouseDifficulty;
	} else {
		numberSteps = game->gameConfig->catDifficulty;
	}
	
	if(!findBestMoveDirection(game->board, game->numTurns, game->catPoint, game->mousePoint, game->cheesePoint,
		 	game->isMouseTurn, numberSteps, &bestMove)) {
		return 0;
	}
	
	if (game->isMouseTurn) {
		makeMouseMove(game, bestMove);
	} else {
		makeCatMove(game, bestMove);
	}
	
	return 1;
}

// A helper method to set the data from the character representation of the world file to the actual game model struct.
void handleTile(GameModel *game, char currTile, int i, int j) {
	switch(currTile) {
		case EMPTY_TILE:
		case WALL_TILE:
			setBoardTile(game, currTile, i, j);
			break;
		case CAT_TILE:
			setCatPoint(game, i, j);
			setBoardTile(game, EMPTY_TILE, i, j);
			break;
		case MOUSE_TILE:
			setMousePoint(game, i, j);
			setBoardTile(game, EMPTY_TILE, i, j);
			break;
		case CHEESE_TILE:
			setCheesePoint(game, i, j);
			setBoardTile(game, EMPTY_TILE, i, j);
			break;
		default:
			break;
	}
}

// Inits a game from the given worldFileData - see header for doc.
void initGameFromWorldFile(GameModel *game, WorldFileData *worldFileData) {
	char currTile;
	int i,j;
	
	setIsMouseTurn(game, worldFileData->isMouseStarts);
	setNumMovesLeft(game, worldFileData->numTurns);
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			currTile = worldFileData->board[i][j];
			handleTile(game, currTile, i, j);
		}
	}
}

// Reset a game from world file - see header for doc.
int resetGameFromWorldFile(GameModel *game) {
	WorldFileData *worldData = NULL;
	
	worldData = createEmptyWorldFileData();
	if (worldData == NULL) {
		return 1;
	}
	readWorldFromFile(game->gameConfig->worldIndex, worldData);
	initGameFromWorldFile(game, worldData);
	freeWorldFileData(worldData);
	
	game->isGameOver = 0;
	game->isPaused = 0;
	return 0;
}

// Creates a game from its configuration - see header for doc.
GameModel *createGameFromConfig(GameConfigurationModel *gameConfig) {
	WorldFileData *worldData = NULL;
	GameModel *result = NULL;
	
	result = createGame(gameConfig);
	if (result == NULL) {
		return NULL;
	}
	
	worldData = createEmptyWorldFileData();
	if (worldData == NULL) {
		return NULL;
	}
	
	readWorldFromFile(gameConfig->worldIndex, worldData);
	initGameFromWorldFile(result, worldData);
	freeWorldFileData(worldData);
	return result;
}

// Updates the configuration of the game - see header for doc.
int updateConfigForGame(GameModel *gameModel, GameConfigurationModel *newConfig) {
	free(gameModel->gameConfig);
	gameModel->gameConfig = createGameConfig(newConfig->isCatHuman, newConfig->catDifficulty,
		 		newConfig->isMouseHuman, newConfig->mouseDifficulty, newConfig->worldIndex);
	if (gameModel->gameConfig == NULL) {
		return 1;
	}
	return 0;
}

// Creates a WorldFileData from the given name in order to be saved to a file - see header for doc.
WorldFileData *createWorldDataFromGame(GameModel *game) {
	WorldFileData *worldData = NULL;
	int i, j;

	worldData = createEmptyWorldFileData();
	if (worldData == NULL) {
		return NULL;
	}
	worldData->isMouseStarts = game->isMouseTurn;
	worldData->numTurns = game->numTurns;
	
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			worldData->board[i][j] = game->board[i][j];
		}
	}
	
	worldData->board[game->catPoint.row][game->catPoint.col] = CAT_TILE;
	worldData->board[game->mousePoint.row][game->mousePoint.col] = MOUSE_TILE;
	worldData->board[game->cheesePoint.row][game->cheesePoint.col] = CHEESE_TILE;
	
	return worldData;
}

// Validation for the game - see header for doc.
int checkGameValidSetMsg(GameModel *game) {
	if (isEmptyPoint(game->catPoint)) {
		game->validMsg = "Cat is missing";
		return 0;
	} else if (isEmptyPoint(game->mousePoint)) {
		game->validMsg = "Mouse is missing";
		return 0;
	} else if (isEmptyPoint(game->cheesePoint)) {
		game->validMsg = "Cheese is missing";
		return 0;
	}
	return 1;
}
