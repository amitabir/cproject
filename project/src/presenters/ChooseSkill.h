#ifndef CHOOSE_SKILL_H_
#define CHOOSE_SKILL_H_

#include <SDL.h>
#include "GUIState.h"

// Starts the skill selection window, creating the model and drawing the widgets. 
void startChooseSkill(GUIState* mainMenuState, void* initData);

/* Handles the logical event given and updates the view/model if needed.
	 Returns the next state ID. */
StateId presenterHandleEventChooseSkill(void* model, void* viewState, void* logicalEvent);

/* Stops the choose skill window.
	 Returns the next state initiliazation data. */
void* stopChooseSkill(GUIState* state, StateId nextStateId);

#endif /* CHOOSE_SKILL_H_ */
