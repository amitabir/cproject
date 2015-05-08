#ifndef GAME_EDITOR_H_
#define GAME_EDITOR_H_

/* This presenter is for the game edit/creation windows. */

#include <SDL.h>
#include "GUIState.h"
#include "../services/BoardPoint.h"
#include "../model/GameModel.h"

// A model for the create/edit game windows. 
typedef struct game_editor_model {
	StateId stateId; // The state ID of the current GUI state.
	GameModel *game; // The game pointer which is being edited
	BoardPoint markedPoint; // The marked point on the board.
	char *errorMsg; // Error message when the game is inavlid.
} GameEditorModel;

/* Starts the game editor - creating the model and view. */
void startEditGame(GUIState* editGameState, void* initData);

/* Translates SDL events to logical events, returns the logical event */
void* viewTranslateEventEditGame(void* viewState, SDL_Event* event);

/* Handles the logical events for the editor, returns the next state ID. */
StateId presenterHandleEventEditGame(void* model, void* viewState, void* logicalEvent);

/* Stops the editor, returns the intiialziation data for the next state. */
void* stopEditGame(GUIState* gui, StateId nextStateId);

#endif /* GAME_EDITOR_H_ */
