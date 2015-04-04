#ifndef CHOOSE_SKILL_H_
#define CHOOSE_SKILL_H_

#include <SDL.h>
#include "GUIState.h"

void startChooseSkill(GUIState* mainMenuState, void* initData);
void* viewTranslateEventChooseSkill(void* viewState, SDL_Event* event);
StateId presenterHandleEventChooseSkill(void* model, void* viewState, void* logicalEvent);
void* stopChooseSkill(GUIState* state, StateId nextStateId);

#endif /* CHOOSE_SKILL_H_ */
