#ifndef ERROR_H_
#define ERROR_H_

#include <SDL.h>
#include "GUIState.h"

void startError(GUIState* mainMenuState, void* initData);
void* viewTranslateEventError(void* viewState, SDL_Event* event);
StateId presenterHandleEventError(void* model, void* viewState, void* logicalEvent);
void* stopError(GUIState* state, StateId nextStateId);

#endif /* ERROR_H_ */
