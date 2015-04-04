#ifndef EDIT_GAME_H_
#define EDIT_GAME_H_

#include <SDL.h>
#include "GUIState.h"

typedef struct edit_world_model {
	StateId stateId;
	GameModel *game;
	BoardPoint markedPoint;
	char *errorMsg;
} EditGameModel;

void startEditGame(GUIState* editGameState, void* initData);
void* viewTranslateEventEditGame(void* viewState, SDL_Event* event);
StateId presenterHandleEventEditGame(void* model, void* viewState, void* logicalEvent);
void* stopEditGame(GUIState* gui, StateId nextStateId);

#endif /* EDIT_GAME_H_ */
