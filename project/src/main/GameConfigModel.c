#include <stdlib.h>
#include <stdio.h>
#include "GameConfigModel.h"

GameConfigurationModel *createGameConfig(int isCatHuman, int catDifficulty,	int isMouseHuman, int mouseDifficulty) {
	GameConfigurationModel *gameConfig;
	
	// Create the game configuration struct
    if ((gameConfig = (GameConfigurationModel *) malloc(sizeof(GameConfigurationModel))) == NULL) {
		// Malloc has failed and the user is notified
		perror("Error: standard function malloc has failed");
		return NULL;
	}
	
	gameConfig->isCatHuman = isCatHuman;
	gameConfig->catDifficulty = catDifficulty;
	gameConfig->isMouseHuman = isMouseHuman;
	gameConfig->mouseDifficulty = mouseDifficulty;
	return gameConfig;
}

void freeConfig(GameConfigurationModel *gameConfig) {
	free(gameConfig);
}
