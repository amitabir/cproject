#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/DrawBoard.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Events.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "GUIState.h"
#include "LogicalEvents.h"
#include "CatChoose.h"


#define BUTTONS_NUMBER 3

static char *CAT_LABEL_TITLE = "Choose Your Cat:";
static char *MOUSE_LABEL_TITLE = "Choose Your Mouse:";


typedef enum {
	BUTTON_HUMAN_TYPE,
	BUTTON_MACHINE_TYPE,
	BUTTON_BACK
} ButtonId;

int isCatSelectionWindow(StateId stateId) {
	if (stateId == CAT_CHOOSE) {
		return 1;
	}
	return 0;
}

Widget* createCatChooseView(int isCatWindow) {
	Widget *window = NULL, *buttonHuman = NULL, *buttonMachine = NULL, *buttonBack = NULL, *panel = NULL, *buttonsPanel = NULL, *titleLabel = NULL;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200,100,400,600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	
	if (isCatWindow) {
		titleLabel = createLabel(0, 95, 0, 200, 70);
		setText(titleLabel, CAT_LABEL_TITLE, 5, 20);
	} else {
		titleLabel = createLabel(0, 95, 0, 300, 70);
		setText(titleLabel, MOUSE_LABEL_TITLE, 5, 20);
	}
	
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	buttonsPanel = createPanel(0, 0, 100, 400, 470);
	setBgColor(buttonsPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, buttonsPanel);
	
	buttonHuman = createButton(BUTTON_HUMAN_TYPE, 85, 0, 200, 70, colorKey, "Human", 45, 20, "images/buttonReg.bmp","images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonHuman);

	buttonMachine = createButton(BUTTON_MACHINE_TYPE, 85, 100, 200, 70, colorKey, "Machine", 45, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonMachine);
	
	buttonBack = createButton(BUTTON_BACK, 85, 200, 200, 70, colorKey, "Back", 35, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonBack);
	
	return window;
}

void startCatChoose(GUIState* catChooseState, void* initData) {
	catChooseState->viewState = createCatChooseView(isCatSelectionWindow(catChooseState->stateId));
	SelectionModel *model = createSelectionModelByState(catChooseState->stateId, initData);
	catChooseState->model = model;
		
	markButton((Widget *) catChooseState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	draw_board((Widget *) catChooseState->viewState);
}


void* viewTranslateEventCatChoose(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

void updateConfig(SelectionModel *selectionModel, int isCatWindow, int isHuman) {
	if (isCatWindow) {
		selectionModel->gameConfig->isCatHuman = isHuman;
	} else {
		selectionModel->gameConfig->isMouseHuman = isHuman;
	}
}

StateId handleButtonSelectedCatChoose(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;	
	int isCatWindow = isCatSelectionWindow(selectionModel->stateId);
	switch (buttonId) {
		case BUTTON_HUMAN_TYPE:
			updateConfig(selectionModel, isCatWindow, 1);
			if (isCatWindow) {
				return MOUSE_CHOOSE;
			} else {
				return GAME_PLAY;
			}
			break;
		case BUTTON_MACHINE_TYPE:
			updateConfig(selectionModel, isCatWindow, 0);
			if (isCatWindow) {
				return CAT_CHOOSE_SKILL;
			} else {
				return MOUSE_CHOOSE_SKILL;
			}
		case BUTTON_BACK:
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

StateId presenterHandleEventCatChoose(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;		
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedCatChoose, selectionModel->stateId, BUTTONS_NUMBER);
}

void* stopCatChoose(GUIState* state, StateId nextStateId) {
	SelectionModel *selectionModel = (SelectionModel *) state->model;		
	
	if (nextStateId == selectionModel->previousStateModel->stateId) {
		return selectionModel->previousStateModel;
	} else {
		return selectionModel;
	}
	// TODO think about freeing the previous data when back isn't clicked
}
