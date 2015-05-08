#ifndef GAME_LOGIC_SERVICE_H_
#define GAME_LOGIC_SERVICE_H_

/* This service is responsible for handling a game - handling turns, init games and so on */

#include "../model/Constants.h"
#include "../model/GameModel.h"
#include "WorldFilesService.h"

/* Handles a turn for the machine - finds the best move direction according to the set difficulty and makes the move accordingly.
	Returns 0 on success, 1 if some error occured. */
int handleMachineMove(GameModel *game);

/* Inits a game from world file data - initializing the game's board and players position according to the data in the WorldfileData struct. */
void initGameFromWorldFile(GameModel *game, WorldFileData *worldFileData);

/* Re-initilizes the game from the world file index which is saved in the game's configuration. The method reads the world file again,
 and initializes the board and players accordingly. */
int resetGameFromWorldFile(GameModel *game);

/* Creates a game from configuration - the configuration model contains the worldIndex, so the correct world file is read and prased,
	and the game initializes from the world file. 
   Returns the created game or NULL if some error occured.  */
GameModel *createGameFromConfig(GameConfigurationModel *gameConfig);

/* Updates the game configuration - replaces it with the new configuration (copying it, not setting it as it is). 
	Returns 0 on success, 1 if some error occurs. */
int updateConfigForGame(GameModel *gameModel, GameConfigurationModel *newConfig);

/* Creates a new WorldFileData struct from a given game, in order to save it to a world file.
   Returns the created world data or NULL if some error occured.  */
WorldFileData *createWorldDataFromGame(GameModel *game);

/* Validates the game - check if there is no cat, cheese or mouse missing. If it is missing, sets a validation message in the game.
 Returns 1 if the game is valid, 0 otherwise. */
int checkGameValidSetMsg(GameModel *game);


#endif /* GAME_LOGIC_SERVICE_H_ */
