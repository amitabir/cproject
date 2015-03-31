#include <stdlib.h>
#include <stdio.h>
#include "GameConfigModel.h"

#define DEFAUL_SKILL_LEVEL 1
#define DEFAULT_IS_HUMAN 0
#define DEFAULT_WORLD_INDEX 1

GameConfigurationModel *createGameConfigDefault() {
	return createGameConfig(DEFAULT_IS_HUMAN, DEFAUL_SKILL_LEVEL, DEFAULT_IS_HUMAN, DEFAUL_SKILL_LEVEL, DEFAULT_WORLD_INDEX);
}

GameConfigurationModel *createGameConfig(int isCatHuman, int catDifficulty,	int isMouseHuman, int mouseDifficulty, int worldIndex) {
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
	gameConfig->worldIndex = worldIndex;
	return gameConfig;
}

void freeConfig(GameConfigurationModel *gameConfig) {
	free(gameConfig);
}
