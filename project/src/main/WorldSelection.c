#include <string.h>
#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/UITree.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "Model/WorldFilesService.h"
#include "Model/GameLogicService.h"
#include "Model/Constants.h"
#include "WorldSelection.h"


#define BUTTONS_NUMBER 3

#define WORLD_IMAGE_NAME_LENGTH 26
#define WORLD_MARKED_IMAGE_NAME_LENGTH 32

#define TITLE_POSX 90
#define TITLE_POSY 25

static char *LOAD_GAME_LABEL_TITLE = "Load Game";
static char *EDIT_GAME_LABEL_TITLE = "Edit Game";
static char *SAVE_GAME_LABEL_TITLE = "Save Game";

const char *WORLD_SELECTION_BUTTONS_IMAGES[] = {NULL, "images/Buttons/Done.bmp", "images/Buttons/Back.bmp"};
const char *WORLD_SELECTION_MARKED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/DoneMarked.bmp", "images/Buttons/BackMarked.bmp"};

const char *WORLD_IMAGE_NAME = "images/Buttons/World%d.bmp";
const char *WORLD_MARKED_IMAGE_NAME = "images/Buttons/World%dMarked.bmp";

int saved = 0;

typedef enum {
	BUTTON_WORLD_INDEX,
	BUTTON_DONE,
	BUTTON_BACK,
	BUTTON_WORLD_UP,
	BUTTON_WORLD_DOWN
} ButtonId;

int updateWorldIndexButton(Widget *window, int worldIndex) {
	char worldIndexImageFileName[WORLD_IMAGE_NAME_LENGTH], worldIndexMarkedImageFileName[WORLD_MARKED_IMAGE_NAME_LENGTH];
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, getChildrenNum(panel) - 1);
	Widget *worldIndexButton = getChildAtindex(buttonsPanel, BUTTON_WORLD_INDEX);
	sprintf(worldIndexImageFileName, WORLD_IMAGE_NAME, worldIndex);
	sprintf(worldIndexMarkedImageFileName, WORLD_MARKED_IMAGE_NAME, worldIndex);
		
	if (setImage(worldIndexButton, worldIndexImageFileName) != 0 || setMarkedImage(worldIndexButton, worldIndexMarkedImageFileName) != 0) {		
		return 1;
	}
	return 0;
}

void startLoadGame(GUIState* loadGameState, void* initData) {
	char* title = NULL;
	Widget *window;
	switch(loadGameState->stateId) {
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
	
	loadGameState->viewState = window;
	SelectionModel *model = createSelectionModelByState(loadGameState->stateId, initData);	
	if (model == NULL) {
		isError = 1;
		return;
	}
	loadGameState->model = model;
	
	if (updateWorldIndexButton((Widget *) loadGameState->viewState, model->gameConfig->worldIndex) != 0) {
		isError = 1;
		return;
	}
	markButton((Widget *) loadGameState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	isError = drawUITree((Widget *) loadGameState->viewState);
}

void* viewTranslateEventLoadGame(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

int handleWorldIndexUp(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex < MAX_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex++;
		if (updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex) != 0) {
			return 1;
		}
	}
	return 0;
}

int handleWorldIndexDown(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex > MIN_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex--;
		if (updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex) != 0) {
			return 1;
		}
	}
	return 0;
}

void handleSaveGame(SelectionModel *selectionModel) {
	WorldFileData *worldData = NULL;
	
	worldData = createWorldDataFromGame(selectionModel->game);
	updateConfigForGame(selectionModel->game, selectionModel->gameConfig);
	writeWorldToFile(selectionModel->gameConfig->worldIndex, worldData);
	freeWorldFileData(worldData);
	
	saved = 1;
}

StateId handleButtonSelectedLoadGame(void* model, Widget *window, int buttonId) {
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
			if (selectionModel->markedButtonIndex == BUTTON_WORLD_INDEX) {
				if (handleWorldIndexUp(selectionModel, window) != 0) {
					isError = 1;
					return selectionModel->stateId;
				}
				isError = drawUITree(window);
			}
			break;
		case BUTTON_WORLD_DOWN:
				if (selectionModel->markedButtonIndex == BUTTON_WORLD_INDEX) {
				if (handleWorldIndexDown(selectionModel, window) != 0) {
					isError = 1;
					return selectionModel->stateId;
				}
				isError = drawUITree(window);	
			}	
			break;
		case BUTTON_BACK:
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

StateId presenterHandleEventLoadGame(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedLoadGame, selectionModel->stateId, BUTTONS_NUMBER);
}


void* stopLoadGame(GUIState* state, StateId nextStateId) {
	freeWidget((Widget *) state->viewState);
	SelectionModel *selectionModel = (SelectionModel *) state->model;
	
	if (nextStateId == QUIT) {
		freeSelectionModel((SelectionModel *) state->model, 1, 1);
	}
	
	if (nextStateId == selectionModel->previousStateModel->stateId && !saved) {		
		freeSelectionModel((SelectionModel *) state->model, 0, 0);
		return selectionModel->previousStateModel;
	} else {
		return selectionModel;
	}
}
