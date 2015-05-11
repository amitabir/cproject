#ifndef CHOOSE_TYPE_H_
#define CHOOSE_TYPE_H_

#include <SDL.h>
#include "GUIState.h"

// Starts the choose type window, creating the model and drawing the widgets. 
void startChooseType(GUIState* chooseTypeState, void* initData);

/* Handles the logical event given and updates the view/model if needed.
   Returns the next state ID. */
StateId presenterHandleEventChooseType(void* model, void* viewState, void* logicalEvent);

/* Stops the choose type window.
   Returns the next state initiliazation data. */
void* stopChooseType(GUIState* gui, StateId nextStateId);

#endif /* CHOOSE_TYPE_H_ */
