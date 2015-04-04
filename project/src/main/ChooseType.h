#ifndef CHOOSE_TYPE_H_
#define CHOOSE_TYPE_H_

#include <SDL.h>
#include "GUIState.h"
#include "GameConfigModel.h"

void startChooseType(GUIState* chooseTypeState, void* initData);
void* viewTranslateEventChooseType(void* viewState, SDL_Event* event);
StateId presenterHandleEventChooseType(void* model, void* viewState, void* logicalEvent);
void* stopChooseType(GUIState* gui, StateId nextStateId);

#endif /* CHOOSE_TYPE_H_ */
