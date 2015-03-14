#ifndef GAME_LOGIC_SERVICE_H_
#define GAME_LOGIC_SERVICE_H_
#include "Constants.h"
#include "GameModel.h"
#include "WorldFilesService.h"


int handleMachineMove(GameModel *game);

void initGameFromWorldFile(GameModel *game, WorldFileData *worldFileData);

#endif /* GAME_LOGIC_SERVICE_H_ */
