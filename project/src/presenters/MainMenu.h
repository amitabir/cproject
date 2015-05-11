#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <SDL.h>
#include "GUIState.h"

/* Starts the main menu: creates the model and view, and drawing the view. */
void startMainMenu(GUIState* mainMenuState, void* initData);

/* Handles the logical event by for the main menu window
   Returns the next state ID. */
StateId presenterHandleEventMainMenu(void* model, void* viewState, void* logicalEvent);

/* The stop for the main menu is a little different from other stop methods, as the next window might not be selection window. 
	Thus we need a more delicate separation between the possible next states.
	Returns the initialization data for the next state. */
void* stopMainMenu(GUIState* state, StateId nextStateId);


#endif /* MAIN_MENU_H_ */
