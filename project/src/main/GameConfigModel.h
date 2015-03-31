#ifndef GAME_CONFIG_MODEL_H_
#define GAME_CONFIG_MODEL_H_

typedef struct game_conf_model {
	int isCatHuman;
	int catDifficulty;
	int isMouseHuman;
	int mouseDifficulty;
	int worldIndex;
} GameConfigurationModel;

GameConfigurationModel *createGameConfigDefault(); // ALL defaults
GameConfigurationModel *createGameConfig(int isCatHuman, int catDifficulty,	int isMouseHuman, int mouseDifficulty, int worldIndex);

#endif /* GAME_CONFIG_MODEL_H_ */
