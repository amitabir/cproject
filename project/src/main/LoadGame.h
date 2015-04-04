#ifndef LOAD_GAME_H_
#define LOAD_GAME_H_

#include <SDL.h>
#include "GUIState.h"

void startLoadGame(GUIState* mainMenuState, void* initData);
void* viewTranslateEventLoadGame(void* viewState, SDL_Event* event);
StateId presenterHandleEventLoadGame(void* model, void* viewState, void* logicalEvent);
void* stopLoadGame(GUIState* state, StateId nextStateId);

#endif /* LOAD_GAME_H_ */
