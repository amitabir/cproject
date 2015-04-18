#ifndef GAME_EDITOR_H_
#define GAME_EDITOR_H_

#include <SDL.h>
#include "GUIState.h"

typedef struct game_editor_model {
	StateId stateId;
	GameModel *game;
	BoardPoint markedPoint;
	char *errorMsg;
} GameEditorModel;

void startEditGame(GUIState* editGameState, void* initData);
void* viewTranslateEventEditGame(void* viewState, SDL_Event* event);
StateId presenterHandleEventEditGame(void* model, void* viewState, void* logicalEvent);
void* stopEditGame(GUIState* gui, StateId nextStateId);

#endif /* GAME_EDITOR_H_ */
