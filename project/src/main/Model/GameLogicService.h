#ifndef GAME_LOGIC_SERVICE_H_
#define GAME_LOGIC_SERVICE_H_
#include "Constants.h"
#include "GameModel.h"
#include "WorldFilesService.h"


int handleMachineMove(GameModel *game);

void initGameFromWorldFile(GameModel *game, WorldFileData *worldFileData);

GameModel *createGameFromConfig(GameConfigurationModel *gameConfig);

GameModel *createGameFromConfigAndWorldFile(GameConfigurationModel *gameConfig, WorldFileData *worldFileData);

int resetGameFromWorldFile(GameModel *game);

int updateConfigForGame(GameModel *gameModel, GameConfigurationModel *newConfig);

WorldFileData *createWorldDataFromGame(GameModel *game);

int checkGameValidSetMsg(GameModel *game);

#endif /* GAME_LOGIC_SERVICE_H_ */
