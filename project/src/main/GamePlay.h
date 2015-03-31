#ifndef GAME_PLAY_H_
#define GAME_PLAY_H_

#include <SDL.h>
#include "GUIState.h"

void startGamePlay(GUIState* mainMenuState, void* initData);
void* viewTranslateEventGamePlay(void* viewState, SDL_Event* event);
StateId presenterHandleEventGamePlay(void* model, void* viewState, void* logicalEvent);
void* stopGamePlay(GUIState* gui, StateId nextStateId);

#endif /* GAME_PLAY_H_ */
