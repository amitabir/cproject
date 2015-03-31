#ifndef CAT_CHOOSE_H_
#define CAT_CHOOSE_H_

#include <SDL.h>
#include "GUIState.h"
#include "GameConfigModel.h"

void startCatChoose(GUIState* mainMenuState, void* initData);
void* viewTranslateEventCatChoose(void* viewState, SDL_Event* event);
StateId presenterHandleEventCatChoose(void* model, void* viewState, void* logicalEvent);
void* stopCatChoose(GUIState* gui, StateId nextStateId);

#endif /* CAT_CHOOSE_H_ */
