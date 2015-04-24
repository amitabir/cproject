#ifndef SELECTION_WINDOW_H_
#define SELECTION_WINDOW_H_

#include <SDL.h>
#include "GUIState.h"
#include "GUI/Widget.h"
#include "Model/GameConfigModel.h"
#include "Model/GameModel.h"

typedef struct selection_model {
	StateId stateId;
	GameConfigurationModel *gameConfig;
	int markedButtonIndex;
	GameModel *game;
	struct selection_model *previousStateModel;
} SelectionModel;

SelectionModel *createSelectionModel(StateId stateId, SelectionModel *previousStateModel, GameConfigurationModel *previousConfig, GameModel *game);
SelectionModel *createSelectionModelByState(StateId stateId, void *initData);
void freeSelectionModel(SelectionModel *selectionModel, int freePrevious, int shouldFreeGame);
void markButton(Widget *window, int *markButtonPtr, int newButtonToMark);
void* viewTranslateEventSelectionWindow(void* viewState, SDL_Event* event);
StateId presenterHandleEventSelectionWindow(void* model, Widget *window, void* logicalEvent, int *markButtonPtr, 
StateId (*handleButtonSelected)(void *model, Widget *window, int buttonId), StateId sameStateId, int buttonsNumber);
void* stopSelectionWindow(GUIState* state, StateId nextStateId);

#endif /* SELECTION_WINDOW_H_ */
