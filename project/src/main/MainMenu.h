#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <SDL.h>
#include "GUIState.h"

void startMainMenu(GUIState* mainMenuState, void* initData);
void* viewTranslateEventMainMenu(void* viewState, SDL_Event* event);
StateId presenterHandleEventMainMenu(void* model, void* viewState, void* logicalEvent);
void* stopMainMenu(GUIState* state, StateId nextStateId);


#endif /* MAIN_MENU_H_ */
