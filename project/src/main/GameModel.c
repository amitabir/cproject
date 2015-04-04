#include <stdlib.h>
#include <stdio.h>
#include "GameModel.h"
#include "GameConfigModel.h"
#include "WorldFilesService.h"
#include "MoveLogicService.h"

#define DEFAULT_NUM_TURNS 20
#define DEFAULT_GAME_OVER 0
#define DEFAULT_GAME_PAUSED 0

/* This function dynamically allocates the game board (two dimensional char array). 
   Returns NULL pointer if the malloc has failed. */
char** createBoard() {
        char **board;
        int i, j;
			
        if ((board = (char**)malloc(BOARD_ROWS * sizeof(char*))) == NULL) {
                perror("Error: standard function malloc has failed");
                return NULL;
        }

        for (i = 0; i < BOARD_ROWS; i++) {
                if ((board[i] = (char*)malloc(BOARD_COLS * sizeof(char))) == NULL) {
                    perror("Error: standard function malloc has failed");
					free(board);
                    return NULL;
                }
        }
		
		// Init board with empty tiles
		for (i = 0; i < BOARD_ROWS; i++) {
			for (j = 0; j < BOARD_COLS; j++) {
				board[i][j] = EMPTY_TILE;
			}
		}
		
        return board;
}

GameModel *createEmptyGame() {
	GameModel *game;
	
	// Create the game struct
    if ((game = (GameModel*) malloc(sizeof(GameModel))) == NULL) {
		// Malloc has failed and the user is notified
		perror("Error: standard function malloc has failed");
		return NULL;
	}
	
	// Create a new board using the createBoard function
	game->board = createBoard();
	if (game->board == NULL) {
		// Board creation has failed - 0 is returned.
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

GameModel *createGame(GameConfigurationModel *gameConfig) {
	GameModel *game = createEmptyGame();
	game->gameConfig = gameConfig; // TODO Maybe we should copy here
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
		
		WinnerType winType = hasWinner(game->board, game->catPoint, game->mousePoint, game->cheesePoint, game->numTurns);
		if (winType != NO_WIN) {
			game->winType = winType;
			game->isGameOver = 1;
		} else if (game->numTurns == 0) {
			game->winType = DRAW;
			game->isGameOver = 1;
		}
	}
}

void makeCatMove(GameModel *game, MoveDirection direction) {
	makeMove(game, &(game->catPoint), direction);
}

void makeMouseMove(GameModel *game, MoveDirection direction) {
	makeMove(game, &(game->mousePoint), direction);
}

/* This function receives a pointer to the board and frees it first by going through all of the rows and freeing
the columns and at the end freeing the board pointer */
void freeBoard(char **board) {
	int i;
	for (i = 0; i < BOARD_ROWS ; i++) {
		free(board[i]);	
	}
	free(board);
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
