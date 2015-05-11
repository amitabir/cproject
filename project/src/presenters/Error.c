#include <string.h>
#include "../gui/UITree.h"
#include "../gui/WidgetFactory.h"
#include "../gui/GUIConstants.h"
#include "SelectionWindow.h"
#include "../model/Constants.h"
#include "LogicalEvents.h"

// Number of buttons in this selection window
#define BUTTONS_NUMBER 1

// Positions and sizes of the panels in the error page, which is a little bit different from the other selection windows.
#define ERROR_PANEL_WIDTH MAIN_PANEL_WIDTH
#define ERROR_PANEL_HEIGHT 300
#define ERROR_PANEL_POSX 200
#define ERROR_PANEL_POSY 200

#define ERROR_TITLE_LABEL_WIDTH 300
#define ERROR_TITLE_LABEL_HEIGHT 40
#define ERROR_TITLE_LABEL_POSX (ERROR_PANEL_WIDTH - ERROR_TITLE_LABEL_WIDTH) / 2
#define ERROR_TITLE_LABEL_POSY 0

#define ERROR_TITLE_LABEL_TEXT_POSX 5
#define ERROR_TITLE_LABEL_TEXT_POSY 5

#define ERROR_LABEL_WIDTH 200
#define ERROR_LABEL_HEIGHT 40
#define ERROR_LABEL_POSX (ERROR_PANEL_WIDTH - ERROR_LABEL_WIDTH) / 2
#define ERROR_LABEL_POSY 60

#define ERROR_LABEL_TEXT_POSX 8
#define ERROR_LABEL_TEXT_POSY 0

const char *TITLE_LABLE_TEXT = "Cannot save invalid world!";
const char *BACK_IMAGE = "images/Buttons/Back.bmp";
const char *BACK_MARKED_IMAGE = "images/Buttons/BackMarked.bmp";


// ButtonId enum for recongnizing the buttons when clicked.
typedef enum {
	BUTTON_BACK
} ButtonId;

// Creates the error view - the window and its widgets.
Widget* createErrorView(char *errorMsg) {
	Widget *window = NULL, *panel = NULL, *titleLabel = NULL, *errorMsgLabel = NULL;
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	setBgColor(window, bgColor);
	
	panel = createPanel(ERROR_PANEL_POSX, ERROR_PANEL_POSY, ERROR_PANEL_WIDTH, ERROR_PANEL_HEIGHT, bgColor);
	addWidget(window, panel);
	
	titleLabel = createLabel(ERROR_TITLE_LABEL_POSX, ERROR_TITLE_LABEL_POSY, ERROR_TITLE_LABEL_WIDTH, ERROR_TITLE_LABEL_HEIGHT);
	setText(titleLabel, TITLE_LABLE_TEXT, ERROR_TITLE_LABEL_TEXT_POSX, ERROR_TITLE_LABEL_TEXT_POSY);
	setBgColor(titleLabel, bgColor);
	addWidget(panel, titleLabel);
	
	errorMsgLabel = createLabel(ERROR_LABEL_POSX, ERROR_LABEL_POSY, ERROR_LABEL_WIDTH, ERROR_LABEL_HEIGHT);
	setText(errorMsgLabel, errorMsg, ERROR_LABEL_TEXT_POSX, ERROR_LABEL_TEXT_POSY);
	setBgColor(errorMsgLabel, bgColor);
	addWidget(panel, errorMsgLabel);
	
	if (createSelectionButton(panel, BUTTON_BACK, BUTTON_POSX, BASE_BUTTON_POSY, BUTTON_WIDTH,
		 		BUTTON_HEIGHT, BACK_IMAGE, BACK_MARKED_IMAGE) == NULL) {
		freeWidget(window);
		return NULL;
	}
	
	return window;
}

// Starts the error state window - see header for doc.
void startError(GUIState* errorState, void* initData) {	
	SelectionModel *model = createSelectionModelByState(errorState->stateId, initData);	
	errorState->model = model;
	errorState->viewState = createErrorView(model->game->validMsg);
	
	markButton((Widget *) errorState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	drawUITree((Widget *) errorState->viewState);
}

// Handles buttons selected events according to the buttonId, returns the next state ID.
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

// Handles logical events - see header for doc.
StateId presenterHandleEventError(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedError, selectionModel->stateId, BUTTONS_NUMBER);
}

// Stops the error window - see header for doc.
void* stopError(GUIState* state, StateId nextStateId) {
	SelectionModel *selectionModel = (SelectionModel *) state->model;	
	return selectionModel->previousStateModel;
}
