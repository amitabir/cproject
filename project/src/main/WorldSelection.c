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

static char *LOAD_GAME_LABEL_TITLE = "Load Game";
static char *EDIT_GAME_LABEL_TITLE = "Edit Game";
static char *SAVE_GAME_LABEL_TITLE = "Save Game";

int saved = 0;

typedef enum {
	BUTTON_WORLD_INDEX,
	BUTTON_DONE,
	BUTTON_BACK,
	BUTTON_WORLD_UP,
	BUTTON_WORLD_DOWN
} ButtonId;

Widget* createLoadGameView(StateId stateId) {
	Widget *window = NULL, *buttonWorldIndex = NULL, *buttonDone = NULL, *buttonBack = NULL, *buttonWorldUp = NULL, *buttonWorldDown = NULL,
		 *panel = NULL, *buttonsPanel = NULL, *titleLabel = NULL;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200,100,400,600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	titleLabel = createLabel(0, 20, 0, 300, 70);
	
	switch(stateId) {
		case LOAD_GAME:	setText(titleLabel, LOAD_GAME_LABEL_TITLE, 5, 20); break;
		case EDIT_GAME:	setText(titleLabel, EDIT_GAME_LABEL_TITLE, 5, 20); break;
		case SAVE_GAME:	setText(titleLabel, SAVE_GAME_LABEL_TITLE, 5, 20); break;
		default: break;
	}
	
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	
	buttonsPanel = createPanel(0, 0,100,400, 470);
	setBgColor(buttonsPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, buttonsPanel);
	
	buttonWorldIndex = createButton(BUTTON_WORLD_INDEX, 85, 0, 160 ,70, colorKey, NULL, 0, 0, "images/buttonReg.bmp","images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonWorldIndex);

	buttonDone = createButton(BUTTON_DONE, 85, 100, 200, 70, colorKey, "Done", 45, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonDone);
	
	buttonBack = createButton(BUTTON_BACK, 85, 200, 200, 70, colorKey, "Back", 35, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonBack);
	
	buttonWorldUp = createButton(BUTTON_WORLD_UP, 245, 0, 40, 35, colorKey, NULL, 0, 0, "images/smallUp.bmp", NULL);
	setMarkable(buttonWorldUp, 0);
	addWidget(buttonsPanel, buttonWorldUp);
	
	buttonWorldDown = createButton(BUTTON_WORLD_DOWN, 245, 35, 40, 35, colorKey, NULL, 0, 0, "images/smallDown.bmp", NULL);
	setMarkable(buttonWorldDown, 0);
	addWidget(buttonsPanel, buttonWorldDown);
	
	return window;
}

void updateWorldIndexButton(Widget *window, int worldIndex) {
	char worldIndexStr[8];
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, 1);
	Widget *worldIndexButton = getChildAtindex(buttonsPanel, BUTTON_WORLD_INDEX);
	sprintf(worldIndexStr, "World %d", worldIndex);
	setText(worldIndexButton, worldIndexStr, 20, 20);
}

void startLoadGame(GUIState* loadGameState, void* initData) {
	SelectionModel *model = createSelectionModelByState(loadGameState->stateId, initData);	
	loadGameState->model = model;
	loadGameState->viewState = createLoadGameView(loadGameState->stateId);
	
	updateWorldIndexButton((Widget *) loadGameState->viewState, model->gameConfig->worldIndex);
	markButton((Widget *) loadGameState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	drawUITree((Widget *) loadGameState->viewState);
}

void* viewTranslateEventLoadGame(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

void handleWorldIndexUp(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex < MAX_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex++;
		updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex);
	}
}

void handleWorldIndexDown(SelectionModel *selectionModel, Widget *window) {
	if (selectionModel->gameConfig->worldIndex > MIN_WORLD_INDEX) {
		selectionModel->gameConfig->worldIndex--;
		updateWorldIndexButton(window, selectionModel->gameConfig->worldIndex);
	}
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
				handleWorldIndexUp(selectionModel, window);
				drawUITree(window);
			}
			break;
		case BUTTON_WORLD_DOWN:
				if (selectionModel->markedButtonIndex == BUTTON_WORLD_INDEX) {
				handleWorldIndexDown(selectionModel, window);
				drawUITree(window);	
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
