#include <string.h>
#include "../gui/UITree.h"
#include "../gui/WidgetFactory.h"
#include "SelectionWindow.h"
#include "../services/WorldFilesService.h"
#include "../services/GameLogicService.h"
#include "../model/Constants.h"
#include "LogicalEvents.h"
#include "WorldSelection.h"


#define BUTTONS_NUMBER 3

#define WORLD_IMAGE_NAME_LENGTH 26
#define WORLD_MARKED_IMAGE_NAME_LENGTH 32

#define TITLE_POSX 90
#define TITLE_POSY 5

static char *LOAD_GAME_LABEL_TITLE = "Load Game";
static char *EDIT_GAME_LABEL_TITLE = "Edit Game";
static char *SAVE_GAME_LABEL_TITLE = "Save Game";

const char *WORLD_SELECTION_BUTTONS_IMAGES[] = {NULL, "images/Buttons/Done.bmp", "images/Buttons/Back.bmp"};
const char *WORLD_SELECTION_MARKED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/DoneMarked.bmp", "images/Buttons/BackMarked.bmp"};

const char *WORLD_IMAGE_NAME = "images/Buttons/World%d.bmp";
const char *WORLD_MARKED_IMAGE_NAME = "images/Buttons/World%dMarked.bmp";

// An indicator for whether the game was saved.
int saved = 0;

typedef enum {
	BUTTON_WORLD_INDEX,
	BUTTON_DONE,
	BUTTON_BACK,
	BUTTON_WORLD_UP,
	BUTTON_WORLD_DOWN
} ButtonId;

// Update the image for the world button according to the given worldIndex.
int updateWorldIndexButton(Widget *window, int worldIndex) {
	char worldIndexImageFileName[WORLD_IMAGE_NAME_LENGTH], worldIndexMarkedImageFileName[WORLD_MARKED_IMAGE_NAME_LENGTH];
	Widget *panel = getChildAtindex(window, MAIN_PANEL_INDEX_IN_WINDOW);
	Widget *buttonsPanel = getChildAtindex(panel, getChildrenNum(panel) - 1);
	Widget *worldIndexButton = getChildAtindex(buttonsPanel, BUTTON_WORLD_INDEX);
	sprintf(worldIndexImageFileName, WORLD_IMAGE_NAME, worldIndex);
	sprintf(worldIndexMarkedImageFileName, WORLD_MARKED_IMAGE_NAME, worldIndex);
		
	if (setImage(worldIndexButton, worldIndexImageFileName) != 0 || setMarkedImage(worldIndexButton, worldIndexMarkedImageFileName) != 0) {		
		return 1;
	}
	return 0;
}

// Starts the world selection window - see header for doc.
void startWorldSelection(GUIState* worldSelectionState, void* initData) {
	char* title = NULL;
	Widget *window;
	// Choose the correct title according to the state ID.
	switch(worldSelectionState->stateId) {
		case LOAD_GAME: title = LOAD_GAME_LABEL_TITLE; break;
		case EDIT_GAME:	title = EDIT_GAME_LABEL_TITLE; break;
		case SAVE_GAME:	title = SAVE_GAME_LABEL_TITLE; break;
		default: break;
	}
	window = createSelectionWindowView(title, TITLE_POSX, TITLE_POSY, BUTTONS_NUMBER, WORLD_SELECTION_BUTTONS_IMAGES,
		 	WORLD_SELECTION_MARKED_BUTTONS_IMAGES);
	
	if (window == NULL || addUpDownArrows(window, BUTTON_WORLD_INDEX, BUTTON_WORLD_UP, BUTTON_WORLD_DOWN) != 0) {
		isError = 1;
		return;
	}
	
	worldSelectionState->viewState = window;
	SelectionModel *model = createSelectionModelByState(worldSelectionState->stateId, initData);	
	if (model == NULL) {
		isError = 1;
		return;
	}
	worldSelectionState->model = model;
	saved = 0;
	
	if (updateWorldIndexButton((Widget *) worldSelectionState->viewState, model->gameConfig->worldIndex) != 0) {
		isError = 1;
		return;
	}
	markButton((Widget *) worldSelectionState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	isError = drawUITree((Widget *) worldSelectionState->viewState);
}

// Handles the case when the world index should change by one up, returns 0 on sucess.
int handleWorldIndexUp(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex < MAX_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex++;
		if (updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex) != 0) {
			return 1;
		}
	}
	return 0;
}

// Handles the case when the world index should change by one down, returns 0 on sucess.
int handleWorldIndexDown(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex > MIN_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex--;
		if (updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex) != 0) {
			return 1;
		}
	}
	return 0;
}

// Handles save game action. Creates a WorldFileData struct, fill it with the game data and writes it to the right file using the worldIndex.
// On error, updates the isError flag.
void handleSaveGame(SelectionModel *selectionModel) {
	WorldFileData *worldData = NULL;
	
	worldData = createWorldDataFromGame(selectionModel->game);
	updateConfigForGame(selectionModel->game, selectionModel->gameConfig);
	if (writeWorldToFile(selectionModel->gameConfig->worldIndex, worldData) != 0) {
		isError = 1;
	}
	freeWorldFileData(worldData);
	
	saved = 1;
}

/* Handles world up or down: isUp is 1 for up and 0 for down, and shouldMark specify if we should mark the world index widget, 
	Since when we push the arrows keys we shouldn't mark it, only when clicking with the mouse. */
int handleWorldUpDown(SelectionModel *selectionModel, Widget* window, int isUp, int shouldMark) {
	int result;
	if (selectionModel->markedButtonIndex == BUTTON_WORLD_INDEX) {
		if (isUp) {
			result = handleWorldIndexUp(selectionModel, window);
		} else {
			result = handleWorldIndexDown(selectionModel, window);
		}
		if (result != 0) {
			return 1;
		}
		return drawUITree(window);
	} else if (shouldMark) {
		markButton(window, &(selectionModel->markedButtonIndex), BUTTON_WORLD_INDEX);
		return drawUITree(window);
	}
	return 0;
}

// Handles the button selected event according to the given buttonId.
StateId handleButtonSelectedWorldSelection(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	switch (buttonId) {
		case BUTTON_DONE:
			switch(selectionModel->stateId) {
				case LOAD_GAME:
					return CAT_CHOOSE;
				case EDIT_GAME:
					return GAME_EDITOR;
				case SAVE_GAME:
					handleSaveGame(selectionModel);
					return GAME_EDITOR;
				default: break;
			}
			break;
		case BUTTON_WORLD_UP:
			if (handleWorldUpDown(selectionModel, window, 1, 1) != 0) {
				isError = 1;
				return selectionModel->stateId;
			}
			break;
		case BUTTON_WORLD_DOWN:
			if (handleWorldUpDown(selectionModel, window, 0, 1) != 0) {
				isError = 1;
				return selectionModel->stateId;
			}
			break;
		case BUTTON_BACK:
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

// Handle logical events, using handleButtonSelectedWorldSelection - see header for doc
StateId presenterHandleEventWorldSelection(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	Widget *window = (Widget *) viewState;
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	
	// If we got UP_PRESSED or DOWN_PRESSED - handle special logic
	if (logicalEventPtr->type == UP_PRESSED) {
		if (handleWorldUpDown(selectionModel, window, 1, 0) != 0) {
			isError = 1;
			return selectionModel->stateId;
		}
	} else if (logicalEventPtr->type == DOWN_PRESSED) {
		if (handleWorldUpDown(selectionModel, window, 0, 0) != 0) {
			isError = 1;
			return selectionModel->stateId;
		}
	}
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedWorldSelection, selectionModel->stateId, BUTTONS_NUMBER);
}

// Stops the world seelection window - see header for doc.
void* stopWorldSelection(GUIState* state, StateId nextStateId) {
	if (state->viewState != NULL) {
		freeWidget((Widget *) state->viewState);
	}
	
	if (state->model == NULL) {
		return NULL;
	}
	SelectionModel *selectionModel = (SelectionModel *) state->model;	
	
	
	if (nextStateId == QUIT) {
		freeSelectionModel(selectionModel, 1, 1);
	}
	
	/* In the case Editor->Save->Editor, we have two cases:
		1) The game was saved.
		2) The user pushed the back button, the game was not saved.
	   The behaviour in these two cases is different, so we must know if the game was saved or not */
	if (nextStateId == selectionModel->previousStateModel->stateId && !saved) {
		freeSelectionModel((SelectionModel *) state->model, 0, 0);
		return selectionModel->previousStateModel;
	} else {
		return selectionModel;
	}
}
