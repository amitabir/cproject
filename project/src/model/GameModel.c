#include <stdlib.h>
#include <stdio.h>
#include "GameModel.h"
#include "../services/MoveLogicService.h"
#include "../services/BoardUtils.h"

// Default number of turns for every game
#define DEFAULT_NUM_TURNS 20 

// Default value for game over
#define DEFAULT_GAME_OVER 0

// Default value for game puased
#define DEFAULT_GAME_PAUSED 0

// Creates an empty game - see header for doc.
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

// Creates a game from a configuration - see header for doc.
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

// Sets a board tile on the game board - see header for doc.
void setBoardTile(GameModel *game, char tile, int row, int col) {
	game->board[row][col] = tile;
}

// Sets the cat point position on the board - see header for doc.
void setCatPoint(GameModel *game, int row, int col) {
	game->catPoint.row = row;
	game->catPoint.col = col;
}

// Sets the mouse point position on the board - see header for doc.
void setMousePoint(GameModel *game, int row, int col) {
	game->mousePoint.row = row;
	game->mousePoint.col = col;
}

// Sets the cheese point position on the board - see header for doc.
void setCheesePoint(GameModel *game, int row, int col) {
	game->cheesePoint.row = row;
	game->cheesePoint.col = col;
}

// Sets the current player turn - 1 for mouse turn, 0 for the cat - - see header for doc.
void setIsMouseTurn(GameModel *game, int isMouseTurn) {
	game->isMouseTurn = isMouseTurn;
}

// Sets the number of turns left for the game - see header for doc.
void setNumMovesLeft(GameModel *game, int numTurns) {
	game->numTurns = numTurns;
}

/* A helper method for moving a point in the given direction. If the move is invalid, the move is ignored.
	Also updates the number of turns left and the current player turn. */
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

// Check if the game is over and updates game flags accordingly - see header for doc.
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

// Move the cat position on the grid - see header for doc.
void makeCatMove(GameModel *game, MoveDirection direction) {
	makeMove(game, &(game->catPoint), direction);
}

// Move the mouse position on the grid - see header for doc.
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
