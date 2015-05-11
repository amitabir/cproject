#ifndef GAME_PLAY_H_
#define GAME_PLAY_H_

/* The state for the game play window */

#include <SDL.h>
#include "GUIState.h"

/* Starts the game play window, creating the model and view and drawing the widgets. */
void startGamePlay(GUIState* mainMenuState, void* initData);

/* Translates SDL event into logical event. Returns the logical event.  */
void* viewTranslateEventGamePlay(void* viewState, SDL_Event* event);

/* Handles logical events for the game window. Returns the next state ID.  */
StateId presenterHandleEventGamePlay(void* model, void* viewState, void* logicalEvent);

/* The stop for the game play behaves differently for each state change. 
	When quitting or returning to the main menu - free the game and exit.
	When going back to the configuration, create the correct previous state for the selection window.
	Returns the initialization data for the next state. */
void* stopGamePlay(GUIState* gui, StateId nextStateId);

#endif /* GAME_PLAY_H_ */
