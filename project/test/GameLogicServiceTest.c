#include <stdio.h>
#include <stdlib.h>
#include "../src/main/WorldFilesService.h"
#include "../src/main/MoveLogicService.h"
#include "../src/main/GameLogicService.h"
#include "../src/main/GameConfigModel.h"
#include "../src/main/GameModel.h"
#include <assert.h>

int main() {
	WorldFileData *readWorld = NULL;
	int isValid, i, isMouseTurn = 0;
	readWorld = (WorldFileData*) malloc(sizeof(WorldFileData));
	readWorld->board = (char**) malloc(7*sizeof(char*));
	for (i =0; i < 7; i++) {
		readWorld->board[i] =  (char*) malloc(7*sizeof(char));
	}
	readWorldFromFile(1, readWorld);
	printf("World was read from file! \n");
	
	GameConfigurationModel *config = createGameConfig(1, 5, 0, 4, 1);
	GameModel *game = createGameFromConfigAndWorldFile(config, readWorld);
	
	assert(game->isMouseTurn == 1 && "Mouse should be the first player");
	assert(game->numTurns == 20 && "Should be 20 Turns to the game");
	assert(game->catPoint.row == 6 && game->catPoint.col == 6  && "Cat point should be (6,6)");
	assert(game->mousePoint.row == 6 && game->mousePoint.col == 0  && "Mouse point should be (6,0)");
	assert(game->cheesePoint.row == 0 && game->cheesePoint.col == 3  && "Cheese point should be (0,3)");
	assert(game->gameConfig->catDifficulty == 5 && "Cat difficulty should be 5");
	assert(game->gameConfig->mouseDifficulty == 4 && "Mouse difficulty should be 4");
	assert(game->isGameOver == 0 && "Game shouldn't be over");
	printf("Game is valid! \n");
	
	makeCatMove(game, UP);
	assert(game->catPoint.row == 5 && game->catPoint.col == 6  && "Cat point should be (5,6)");
	makeCatMove(game, LEFT);
	assert(game->catPoint.row == 5 && game->catPoint.col == 5  && "Cat point should be (5,5)");
	makeCatMove(game, DOWN);
	assert(game->catPoint.row == 6 && game->catPoint.col == 5  && "Cat point should be (6,5)");
	makeCatMove(game, RIGHT);
	assert(game->catPoint.row == 6 && game->catPoint.col == 6  && "Cat point should be (6,6)");
	makeCatMove(game, RIGHT); // Invalid move - should be ignored
	assert(game->catPoint.row == 6 && game->catPoint.col == 6  && "Cat point should be (6,6)");
	makeCatMove(game, DOWN); // Invalid move - should be ignored
	assert(game->catPoint.row == 6 && game->catPoint.col == 6  && "Cat point should be (6,6)");
	
	makeMouseMove(game, UP);
	assert(game->mousePoint.row == 5 && game->mousePoint.col == 0  && "Mouse point should be (5,6)");
	makeMouseMove(game, DOWN);
	assert(game->mousePoint.row == 6 && game->mousePoint.col == 0  && "Mouse point should be (5,5)");
	
	while (!game->isGameOver) {
		isMouseTurn = game->isMouseTurn;
		isValid = handleMachineMove(game);
		assert(isValid == 1 && "Handle machine move should be handled successfully");
		if (isMouseTurn) {
			printf("Mouse moved to: (%d, %d) \n", game->mousePoint.row, game->mousePoint.col);
		} else {
			printf("Cat moved to: (%d, %d) \n", game->catPoint.row, game->catPoint.col);
		}
	}
	
}
