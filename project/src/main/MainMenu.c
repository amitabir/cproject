#include "MainMenu.h"
#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/DrawBoard.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Events.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "GUIState.h"
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

Widget* createMainMenuView() {
	Widget *window = NULL, *buttonNewGame = NULL, *buttonLoadGame = NULL, *buttonCreateGame = NULL, *buttonEditGame = NULL,
		 *buttonQuitGame = NULL, *panel = NULL, *buttonsPanel = NULL, *titleLabel = NULL;
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
	
	buttonsPanel = createPanel(0, 0,100,400, 470);
	setBgColor(buttonsPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, buttonsPanel);
	
	buttonNewGame = createButton(BUTTON_NEW_GAME, 95, 0, 200, 70, colorKey, "New Game", 50, 15, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonNewGame);

	buttonLoadGame = createButton(BUTTON_LOAD_GAME, 95, 100, 200, 70, colorKey, "Load Game", 50, 15, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonLoadGame);
	
	buttonCreateGame = createButton(BUTTON_CREATE_GAME, 95, 200, 200, 70, colorKey, "Create Game", 40, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonCreateGame);
	
	buttonEditGame = createButton(BUTTON_EDIT_GAME, 95, 300, 200, 70, colorKey, "Edit Game", 50, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonEditGame);
	
	buttonQuitGame = createButton(BUTTON_QUIT, 95, 400, 200, 70, colorKey, "Quit", 80, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonQuitGame);	
	return window;
}

void startMainMenu(GUIState* mainMenuState, void* initData) {
	mainMenuState->viewState = createMainMenuView();
	SelectionModel *model = createSelectionModelByState(mainMenuState->stateId, initData);	
	mainMenuState->model = model;
		
	markButton((Widget *) mainMenuState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	draw_board((Widget *) mainMenuState->viewState);
}

void* viewTranslateEventMainMenu(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

StateId handleButtonSelectedMainMenu(void* model, Widget *window, int buttonId) {	
	switch (buttonId) {
		case BUTTON_NEW_GAME:
			return CAT_CHOOSE;
		case BUTTON_LOAD_GAME:
			printf("LOAD GAME! \n");
			break;
		case BUTTON_CREATE_GAME:
			printf("CREATE GAME! \n");
			break;
		case BUTTON_EDIT_GAME:
			printf("EDIT GAME! \n");
			break;
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
	return state->model;
}
