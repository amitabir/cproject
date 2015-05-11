#ifndef LOAD_GAME_H_
#define LOAD_GAME_H_

#include <SDL.h>
#include "GUIState.h"

/* Starts the world selection window: creates the model and view, and drawing the view. */
void startWorldSelection(GUIState* mainMenuState, void* initData);

/* Handles the logical event by for the world selection window
   Returns the next state ID. */
StateId presenterHandleEventWorldSelection(void* model, void* viewState, void* logicalEvent);

/* Stops the world selection window, releasing all the resources.
	Returns the initialization data for the next state. */
void* stopWorldSelection(GUIState* state, StateId nextStateId);

#endif /* LOAD_GAME_H_ */
