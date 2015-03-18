#include "GameLogicService.h"
#include "MoveLogicService.h"
#include "GameModel.h"
#include "GameConfigModel.h"
#include <stdio.h>
#include <stdlib.h>


// /* Helper function that receives a pointer to the game and initailizes it - fill the board with empty slots and init the flags. */
// void initGame(Connect4Game *game) {
// 	// Using initBoard to initialize the game board
// 	initBoard(game->board);
// 	// Initializing rest of the game fields
// 	game->isUserTurn = 1;
// 	game->isGameOver = 0;
// 	game->numberSteps = -1;
// }
//
// /* Inintializing a new game received in the pointer given.
// 	Returns 1 if the initialization has succeeded, 0 otherwise. */
// int startGame(Connect4Game *game) {
// 	// Creating a new board using the createBoard function
// 	game->board = createBoard();
// 	if (game->board == NULL) {
// 		// Board creation has failed - 0 is returned.
// 		return 0;
// 	}
// 	// Using initGame to initialize the game
// 	initGame(game);
// 	return 1;
// }
//
// /* Receiving a pointer to an existing game and restarting it by setting all the flags to initial values and clear the board. */
// void restartGame(Connect4Game *game) {
// 	initGame(game);
// }

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
	
	game->isMouseTurn = !game->isMouseTurn;
	return 1;
}


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

GameModel *createGameFromConfigAndWorldFile(GameConfigurationModel *gameConfig, WorldFileData *worldFileData) {
	GameModel *result = createGame(gameConfig);
	initGameFromWorldFile(result, worldFileData);
	return result;
}
