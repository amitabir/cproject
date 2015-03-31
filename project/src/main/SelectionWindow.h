#ifndef SELECTION_WINDOW_H_
#define SELECTION_WINDOW_H_

#include <SDL.h>
#include "GUIState.h"

typedef struct selection_view_state {
	Widget *window;
	char *windowCaption;
	char *labelText;
	Widget* (*createButtonsPanel)();
	int (*getButtonsNumber)();
} SelectionViewState;
	
typedef struct selection_model {
	void *model;
	void* (*createModel)(void *initData);
	StateId (*handleButtonSelected)(void *model, Widget *window);
	void *previousStateData;
	int markedButtonId;
	StateId stateId;
} SelectionModel;

void startSelectionWindow(GUIState* state, void* initData);
void* viewTranslateEventSelectionWindow(void* viewState, SDL_Event* event);
StateId presenterHandleEventSelectionWindow(void* model, void* viewState, void* logicalEvent);
void* stopSelectionWindow(GUIState* state);


#endif /* SELECTION_WINDOW_H_ */
