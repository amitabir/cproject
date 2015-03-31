#ifndef CAT_CHOOSE_SKILL_H_
#define CAT_CHOOSE_SKILL_H_

#include <SDL.h>
#include "GUIState.h"

void startCatChooseSkill(GUIState* mainMenuState, void* initData);
void* viewTranslateEventCatChooseSkill(void* viewState, SDL_Event* event);
StateId presenterHandleEventCatChooseSkill(void* model, void* viewState, void* logicalEvent);
void* stopCatChooseSkill(GUIState* state, StateId nextStateId);

#endif /* CAT_CHOOSE_SKILL_H_ */
