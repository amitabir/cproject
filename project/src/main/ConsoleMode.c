#include <stdio.h>
#include "ConsoleMode.h"
#include "../model/Constants.h"
#include "../services/Evaluation.h"
#include "../services/GameLogicService.h"

/* This function receives an int which represents if it is the mouse's turn. The function parses the stdi from the user into game details -
 the number of turns left, whose turn is it to play next and the board. Then the score function is activated on the received game state and
an int represents the score. The return value is 1 iff 'q\n' was given by the user or some error occured, and otherwise 0 is returned.
 Uses the isError pointer to mark if some error occured during the console mode run. */
int consoleModeRepeat(int isMousePlayer, int *isError) {
	WorldFileData *worldData = createEmptyWorldFileData();
	if (parseWorldFile(stdin, 0, worldData) != 0) {
		*isError = 1;
		return 1;
	}
	if (worldData->numTurns != 0) {
		GameModel *gameModel = createEmptyGame();
		initGameFromWorldFile(gameModel, worldData);
		freeWorldFileData(worldData);
		
		int score = getScoreForState(gameModel->board, gameModel->catPoint, gameModel->mousePoint, gameModel->cheesePoint,
			 gameModel->numTurns, gameModel->isMouseTurn, isMousePlayer);
		printf("%d \n", score);
		freeGame(gameModel);
	} else {
		return 1;
	}
	
	*isError = 0;
	return 0;
}

/* This function calls the consoleModeRepeat function as long as the user has nor entered 'q\n', i.e. didn't request to quit console mode. */
int runConsoleMode(int isMousePlayer) {
	int quit = 0;
	int isError;
	while(!quit) {
		quit = consoleModeRepeat(isMousePlayer, &isError);
	}
	return isError;
}
