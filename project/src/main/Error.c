#include <string.h>
#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/DrawBoard.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Events.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "GUIState.h"
#include "LogicalEvents.h"
#include "Constants.h"


#define BUTTONS_NUMBER 1

static char *TITLE_LABLE_TEXT = "Cannot save invalid world!";

typedef enum {
	BUTTON_BACK
} ButtonId;

Widget* createErrorView(char *errorMsg) {
	Widget *window = NULL, *panel = NULL, *titleLabel = NULL, *errorMsgLabel = NULL, *backButton = NULL;

	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200, 200, 400, 600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	titleLabel = createLabel(0, 100, 0, 300, 50);
	setText(titleLabel, TITLE_LABLE_TEXT, 10, 5);
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	errorMsgLabel = createLabel(0, 100, 60, 300, 50);
	setText(errorMsgLabel,errorMsg, 10, 5);
	setBgColor(errorMsgLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, errorMsgLabel);
	
	backButton = createButton(BUTTON_BACK, 150, 160, 200, 70, colorKey, "Back", 5, 10, "images/buttonReg.bmp","images/buttonMarked.bmp");
	addWidget(panel, backButton);
	
	return window;
}

void startError(GUIState* errorState, void* initData) {	
	SelectionModel *model = createSelectionModelByState(errorState->stateId, initData);	
	errorState->model = model;
	errorState->viewState = createErrorView(model->game->validMsg);
	
	markButton((Widget *) errorState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	draw_board((Widget *) errorState->viewState);
}

void* viewTranslateEventError(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

StateId handleButtonSelectedError(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	switch (buttonId) {
		case BUTTON_BACK:
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

StateId presenterHandleEventError(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedError, selectionModel->stateId, BUTTONS_NUMBER);
}

void* stopError(GUIState* state, StateId nextStateId) {
	SelectionModel *selectionModel = (SelectionModel *) state->model;	
	return selectionModel->previousStateModel;
}
