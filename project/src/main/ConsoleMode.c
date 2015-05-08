#include "ConsoleMode.h"
#include "../model/Constants.h"
#include "../services/Evaluation.h"
#include "../services/GameLogicService.h"

/* This function receives an int which represents if it is the mouse's turn. The function parses the stdi from the user into game details -
 the number of turns left, whose turn is it to play next and the board. Then the score function is activated on the received game state and
an int represents the score. The return value is 1 iff 'q\n' was given by the user and otherwise 0 is returned. */
int consoleModeRepeat(int isMouseTurn) {
	WorldFileData *worldData = createEmptyWorldFileData();
	int result = parseWorldFile(stdin, 0, worldData);
	if (!result) {
		return 1;
	}
	printf("Finished Parsing! \n");
	GameModel *gameModel = createEmptyGame();
	initGameFromWorldFile(gameModel, worldData);
	freeWorldFileData(worldData);
		
	int score = getScoreForState(gameModel->board, gameModel->catPoint, gameModel->mousePoint, gameModel->cheesePoint,
		 gameModel->numTurns, gameModel->isMouseTurn,isMouseTurn);
	if(!isMouseTurn){
		score *= -1;
	}
	printf("%d \n", score);
	freeGame(gameModel);
	
	return 0;
}

/* This function calls the consoleModeRepeat function as long as the user has nor entered 'q\n', i.e. didn't request to quit console mode. */
int consoleMode(int isMouseTurn) {
	int quit = 0;
	while(!quit) {
		quit = consoleModeRepeat(isMouseTurn);
	}
	return 1;
}
