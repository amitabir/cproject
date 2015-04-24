#include "MainMenu.h"
#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/UITree.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"

#define BUTTONS_NUMBER 5

const char WINDOW_CAPTION[] = "Cat And Mouse";

typedef enum {
	BUTTON_NEW_GAME,
	BUTTON_LOAD_GAME,
	BUTTON_CREATE_GAME,
	BUTTON_EDIT_GAME,
	BUTTON_QUIT
} ButtonId;

void handleWidgetFailed(Widget *window) {
	freeWidget(window);
}

Widget* createSelectionButton(Widget *window, Widget *parent, ButtonId buttonId, int posX, int posY, int width, int height, Color colorKey,
	 	char *text, int textPosX, int textPosY) {
	Widget *button = createButton(buttonId, posX, posY, width, height, colorKey, text, textPosX, textPosY, 
			"images/buttonReg.bmp", "images/buttonMarked.bmp");
	if (button == NULL) {
		handleWidgetFailed(window);
		return NULL;
	}
	addWidget(parent, button);
	return button;
}

Widget* createMainMenuView() {
	Widget *window = NULL, *panel = NULL, *buttonsPanel = NULL, *titleLabel = NULL;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200,100,400,600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	titleLabel = createLabel(0, 95, 0, 200, 70);
	setText(titleLabel, "Cat and Mouse", 20, 20);
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	buttonsPanel = createPanel(0, 0,100, 400, 470);
	setBgColor(buttonsPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, buttonsPanel);
	
	char *buttonNames[] = {"New Game", "Load Game", "Create Game", "Edit Game", "Quit"};
	int buttonIdx;
	for (buttonIdx = 0; buttonIdx < BUTTONS_NUMBER; buttonIdx++) {
		if (createSelectionButton(window, buttonsPanel, buttonIdx, 95, buttonIdx*100, 200, 70, colorKey, buttonNames[buttonIdx], 50, 15) == NULL) {
			return NULL;
		}
	}
	// if (createSelectionButton(window, buttonsPanel, BUTTON_NEW_GAME, 95, 0, 200, 70, colorKey, "New Game", 50, 15) == NULL) {
// 		return NULL;
// 	}
//
// 	if (createSelectionButton(window, buttonsPanel, BUTTON_LOAD_GAME, 95, 100, 200, 70, colorKey, "Load Game", 50, 15) == NULL) {
// 		return NULL;
// 	}
//
// 	if (createSelectionButton(window, buttonsPanel, BUTTON_CREATE_GAME, 95, 200, 200, 70, colorKey, "Create Game", 40, 20) == NULL) {
// 		return NULL;
// 	}
//
// 	if (createSelectionButton(window, buttonsPanel, BUTTON_EDIT_GAME, 95, 300, 200, 70, colorKey, "Edit Game", 50, 20) == NULL) {
// 		return NULL;
// 	}
//
// 	if (createSelectionButton(window, buttonsPanel, BUTTON_QUIT, 95, 400, 200, 70, colorKey, "Quit", 80, 20) == NULL) {
// 		return NULL;
// 	}
	return window;
}

void startMainMenu(GUIState* mainMenuState, void* initData) {
	mainMenuState->viewState = createMainMenuView();
	if (mainMenuState->viewState == NULL) {
		isError = 1;
		return;
	}
	SelectionModel *model = createSelectionModelByState(mainMenuState->stateId, initData);
	mainMenuState->model = model;

	markButton((Widget *) mainMenuState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);
 	isError = drawUITree((Widget *) mainMenuState->viewState);
}

void* viewTranslateEventMainMenu(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

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

StateId presenterHandleEventMainMenu(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;	
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedMainMenu, MAIN_MENU, BUTTONS_NUMBER);
}

void* stopMainMenu(GUIState* state, StateId nextStateId) {
	if (state->viewState != NULL) {
		freeWidget((Widget *) state->viewState);
	}
	if (nextStateId == GAME_EDITOR) {
		return NULL;
	}
	if (nextStateId == QUIT) {
		if (state->model != NULL) {
			freeSelectionModel((SelectionModel *) state->model, 1, 1);
		}
		return NULL;
	}
	return state->model;
}
