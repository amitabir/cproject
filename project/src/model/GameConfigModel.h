#ifndef GAME_CONFIG_MODEL_H_
#define GAME_CONFIG_MODEL_H_

/* A model for the game configuration */

/* A struct for holding game configuration data */
typedef struct game_conf_model {
	int isCatHuman; // 1 if the cat is human, 0 otherwise.
	int catDifficulty; // The cat difficulty (skill level) in case the cat is a machine
	int isMouseHuman; // 1 if the mouse is human, 0 otherwise.
	int mouseDifficulty; // The mouse difficulty (skill level) in case the mouse is a machine
	int worldIndex; // The world index for the game.
} GameConfigurationModel;

/* Creates a new configuration model with default paremeters: all players human and skill is 0.
   Returns the created configuaration struct, or NULL if some error occured. */
GameConfigurationModel *createGameConfigDefault(); 

/* Creates a new configuration model with default paremeters: all players human and skill is 0.
   Returns the created configuaration struct, or NULL if some error occured. */
GameConfigurationModel *createGameConfig(int isCatHuman, int catDifficulty,	int isMouseHuman, int mouseDifficulty, int worldIndex);

/* Free the configuration model */
void freeConfig(GameConfigurationModel *gameConfig);

#endif /* GAME_CONFIG_MODEL_H_ */
