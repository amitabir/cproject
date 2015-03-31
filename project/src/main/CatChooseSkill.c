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


#define BUTTONS_NUMBER 3

static char *CAT_LABEL_TITLE = "Choose Cat Skill Level:";
static char *MOUSE_LABEL_TITLE = "Choose Mouse Skill Level:";

typedef enum {
	BUTTON_SKILL_LEVEL,
	BUTTON_DONE,
	BUTTON_BACK,
	BUTTON_SKILL_UP,
	BUTTON_SKILL_DOWN
} ButtonId;

int isCatSkillSelectionWindow(StateId stateId) {
	if (stateId == CAT_CHOOSE_SKILL) {
		return 1;
	}
	return 0;
}

Widget* createCatChooseSkillView(int isCatWindow) {
	Widget *window = NULL, *buttonSkillLevel = NULL, *buttonDone = NULL, *buttonBack = NULL, *buttonSkillUp = NULL, *buttonSkillDown = NULL,
		 *panel = NULL, *buttonsPanel = NULL, *titleLabel = NULL;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200,100,400,600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	if (isCatWindow) {
		titleLabel = createLabel(0, 20, 0, 300, 70);
		setText(titleLabel, CAT_LABEL_TITLE, 5, 20);
	} else {
		titleLabel = createLabel(0, 20, 0, 300, 70);
		setText(titleLabel, MOUSE_LABEL_TITLE, 5, 20);
	}
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	buttonsPanel = createPanel(0, 0,100,400, 470);
	setBgColor(buttonsPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, buttonsPanel);
	
	buttonSkillLevel = createButton(BUTTON_SKILL_LEVEL, 85, 0, 160 ,70, colorKey, NULL, 0, 0, "images/buttonReg.bmp","images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonSkillLevel);

	buttonDone = createButton(BUTTON_DONE, 85, 100, 200, 70, colorKey, "Done", 45, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonDone);
	
	buttonBack = createButton(BUTTON_BACK, 85, 200, 200, 70, colorKey, "Back", 35, 20, "images/buttonReg.bmp", "images/buttonMarked.bmp");
	addWidget(buttonsPanel, buttonBack);
	
	buttonSkillUp = createButton(BUTTON_SKILL_UP, 245, 0, 40, 35, colorKey, NULL, 0, 0, "images/smallUp.bmp", NULL);
	setMarkable(buttonSkillUp, 0);
	addWidget(buttonsPanel, buttonSkillUp);
	
	buttonSkillDown = createButton(BUTTON_SKILL_DOWN, 245, 35, 40, 35, colorKey, NULL, 0, 0, "images/smallDown.bmp", NULL);
	setMarkable(buttonSkillDown, 0);
	addWidget(buttonsPanel, buttonSkillDown);
	
	return window;
}

char *skillToStr(int skill) {
	char *skillStr = (char *) malloc(2 * sizeof(char));
	sprintf(skillStr, "%d", skill);
	return skillStr;
}

void updateSkillButton(Widget *window, int skillNumber) {
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, 1);
	Widget *skillButton;
	skillButton = getChildAtindex(buttonsPanel, BUTTON_SKILL_LEVEL);
	setText(skillButton, skillToStr(skillNumber), 45, 20);
}

void startCatChooseSkill(GUIState* catChooseSkillState, void* initData) {
	int isCatWindow = isCatSkillSelectionWindow(catChooseSkillState->stateId);
	int skillLevel;
	SelectionModel *model = createSelectionModelByState(catChooseSkillState->stateId, initData);	
	catChooseSkillState->model = model;
	catChooseSkillState->viewState = createCatChooseSkillView(isCatWindow);
	
	if (isCatWindow) {
		skillLevel = model->gameConfig->catDifficulty;
	} else {
		skillLevel = model->gameConfig->mouseDifficulty;
	}
	updateSkillButton((Widget *) catChooseSkillState->viewState, skillLevel);
	markButton((Widget *) catChooseSkillState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	draw_board((Widget *) catChooseSkillState->viewState);
}

void* viewTranslateEventCatChooseSkill(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

void handleSkillUp(SelectionModel *selectionModel, Widget *window, int isCatWindow) {
	if (isCatWindow) {
		if (selectionModel->gameConfig->catDifficulty < MAX_DIFFICULTY) {
			selectionModel->gameConfig->catDifficulty++;
			updateSkillButton(window, selectionModel->gameConfig->catDifficulty);
		}
	} else {
		if (selectionModel->gameConfig->mouseDifficulty < MAX_DIFFICULTY) {
			selectionModel->gameConfig->mouseDifficulty++;
			updateSkillButton(window, selectionModel->gameConfig->mouseDifficulty);
		}
	}
}

void handleSkillDown(SelectionModel *selectionModel, Widget *window, int isCatWindow) {
	if (isCatWindow) {
		if (selectionModel->gameConfig->catDifficulty > MIN_DIFFICULTY) {
			selectionModel->gameConfig->catDifficulty--;
			updateSkillButton(window, selectionModel->gameConfig->catDifficulty);
		}
	} else {
		if (selectionModel->gameConfig->mouseDifficulty > MIN_DIFFICULTY) {
			selectionModel->gameConfig->mouseDifficulty--;
			updateSkillButton(window, selectionModel->gameConfig->mouseDifficulty);
		}
	}
}
StateId handleButtonSelectedCatChooseSkill(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	int isCatWindow = isCatSkillSelectionWindow(selectionModel->stateId);	
	switch (buttonId) {
		case BUTTON_DONE:
			if (isCatWindow) {
				return MOUSE_CHOOSE;
			} else {
				return GAME_PLAY;
			}
			break;
		case BUTTON_SKILL_UP:
			if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				handleSkillUp(selectionModel, window, isCatWindow);
				draw_board(window);
			}
			break;
		case BUTTON_SKILL_DOWN:
				if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				handleSkillDown(selectionModel, window, isCatWindow);
				draw_board(window);	
			}	
			break;
		case BUTTON_BACK:
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

StateId presenterHandleEventCatChooseSkill(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedCatChooseSkill, selectionModel->stateId, BUTTONS_NUMBER);
}

void* stopCatChooseSkill(GUIState* state, StateId nextStateId) {
	SelectionModel *selectionModel = (SelectionModel *) state->model;		
	
	if (nextStateId == selectionModel->previousStateModel->stateId) {
		return selectionModel->previousStateModel;
	} else {
		return selectionModel;
	}
	// TODO think about freeing the previous data when back isn't clicked
}
