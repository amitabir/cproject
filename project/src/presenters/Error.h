#ifndef ERROR_H_
#define ERROR_H_

/* This is an error state in case of error while saving game after editing */

#include <SDL.h>
#include "GUIState.h"

// Starts the error window, creating the model and drawing the widgets. 
void startError(GUIState* mainMenuState, void* initData);

/* Handles the logical event given and updates the view/model if needed.
   Returns the next state ID. */
StateId presenterHandleEventError(void* model, void* viewState, void* logicalEvent);

/* Stops the error window.
   Returns the next state initiliazation data. */
void* stopError(GUIState* state, StateId nextStateId);

#endif /* ERROR_H_ */
