#include <stdlib.h>
#include <stdio.h>
#include "GameConfigModel.h"
#include "Constants.h"

#define DEFAULT_IS_HUMAN 1
#define DEFAULT_DIFFICLTY 5

// Creates a new default configuration - see header for doc.
GameConfigurationModel *createGameConfigDefault() {
	return createGameConfig(DEFAULT_IS_HUMAN, DEFAULT_DIFFICLTY, DEFAULT_IS_HUMAN, DEFAULT_DIFFICLTY, MIN_WORLD_INDEX);
}

// Creates a new configuration using the given parameters - see header for doc.
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

// Free configuration - see header for doc.
void freeConfig(GameConfigurationModel *gameConfig) {
	free(gameConfig);
}
