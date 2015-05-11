#include "../gui/UITree.h"
#include "../gui/WidgetFactory.h"
#include "../gui/GUIConstants.h"
#include "SelectionWindow.h"
#include "MainMenu.h"

#define BUTTONS_NUMBER 5

const char *MAIN_MENU_BUTTONS_IMAGES[] = {"images/Buttons/NewGame.bmp", "images/Buttons/LoadGame.bmp", "images/Buttons/CreateGame.bmp", "images/Buttons/EditGame.bmp", "images/Buttons/Quit.bmp"};
const char *MAIN_MENU_MARKED_BUTTONS_IMAGES[] = {"images/Buttons/NewGameMarked.bmp", "images/Buttons/LoadGameMarked.bmp", "images/Buttons/CreateGameMarked.bmp", "images/Buttons/EditGameMarked.bmp", "images/Buttons/QuitMarked.bmp"};

typedef enum {
	BUTTON_NEW_GAME,
	BUTTON_LOAD_GAME,
	BUTTON_CREATE_GAME,
	BUTTON_EDIT_GAME,
	BUTTON_QUIT
} ButtonId;

// Starts the main menu window - see header for doc.
void startMainMenu(GUIState* mainMenuState, void* initData) {
	mainMenuState->viewState = createSelectionWindowView(NULL, 0, 0, BUTTONS_NUMBER, MAIN_MENU_BUTTONS_IMAGES, MAIN_MENU_MARKED_BUTTONS_IMAGES);
	if (mainMenuState->viewState == NULL) {
		isError = 1;
		return;
	}
	SelectionModel *model = createSelectionModelByState(mainMenuState->stateId, initData);
	if (model == NULL) {
		isError = 1;
		return;
	}
	mainMenuState->model = model;

	markButton((Widget *) mainMenuState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);
 	isError = drawUITree((Widget *) mainMenuState->viewState);
}

// Handles button selected events according to the buttonID, just pass to the next state.
StateId handleButtonSelectedMainMenu(void* model, Widget *window, int buttonId) {	
	switch (buttonId) {
		case BUTTON_NEW_GAME:
			return CAT_CHOOSE;
		case BUTTON_LOAD_GAME:
			return LOAD_GAME;
		case BUTTON_CREATE_GAME:
			return GAME_EDITOR;
		case BUTTON_EDIT_GAME:
			return EDIT_GAME;
		case BUTTON_QUIT:
			return QUIT;
		default:
			break;
	}
	return MAIN_MENU;
}

// By passing the handleButtonSelectedMainMenu to the general logic in SelectionWindow, the specific behaviour for this window will be considered.
StateId presenterHandleEventMainMenu(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;	
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedMainMenu, MAIN_MENU, BUTTONS_NUMBER);
}

// Stop the window and freeing resources.
void* stopMainMenu(GUIState* state, StateId nextStateId) {
	// Free the widgets
	if (state->viewState != NULL) {
		freeWidget((Widget *) state->viewState);
	}
	
	// The game editor does not need the selection model
	if (nextStateId == GAME_EDITOR) {
		freeSelectionModel((SelectionModel *) state->model, 1, 1);
		return NULL;
	}
	
	if (nextStateId == QUIT) {
		if (state->model != NULL) {
			freeSelectionModel((SelectionModel *) state->model, 1, 1);
		}
		return NULL;
	}
	
	// Returns the state model for the next state
	return state->model;
}
