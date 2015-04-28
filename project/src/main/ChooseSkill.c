#include <string.h>
#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/UITree.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "Model/Constants.h"


#define BUTTONS_NUMBER 3

#define CAT_TITLE_POSX 25
#define CAT_TITLE_POSY 25
#define MOUSE_TITLE_POSX 14
#define MOUSE_TITLE_POSY 25 

#define SKILL_IMAGE_NAME_LENGTH 26
#define SKILL_MARKED_IMAGE_NAME_LENGTH 32

static char *CAT_LABEL_TITLE = "Choose Cat Skill Level:";
static char *MOUSE_LABEL_TITLE = "Choose Mouse Skill Level:";

const char *CHOOSE_SKILL_BUTTONS_IMAGES[] = {NULL, "images/Buttons/Done.bmp", "images/Buttons/Back.bmp"};
const char *CHOOSE_SKILL_MARKED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/DoneMarked.bmp", "images/Buttons/BackMarked.bmp"};

const char *SKILL_IMAGE_NAME = "images/Buttons/Skill%d.bmp";
const char *SKILL_MARKED_IMAGE_NAME = "images/Buttons/Skill%dMarked.bmp";

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

int updateSkillButton(Widget *window, int skillNumber) {
	char skillFileName[SKILL_IMAGE_NAME_LENGTH], skillMarkedFileName[SKILL_MARKED_IMAGE_NAME_LENGTH];
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, getChildrenNum(panel) - 1);
	Widget *skillButton;
	skillButton = getChildAtindex(buttonsPanel, BUTTON_SKILL_LEVEL);
	sprintf(skillFileName, SKILL_IMAGE_NAME, skillNumber);
	sprintf(skillMarkedFileName, SKILL_MARKED_IMAGE_NAME, skillNumber);
		
	if (setImage(skillButton, skillFileName) != 0 || setMarkedImage(skillButton, skillMarkedFileName) != 0) {		
		return 1;
	}
	return 0;
}

void startChooseSkill(GUIState* chooseSkillState, void* initData) {	
	int skillLevel;
	int isCatWindow = isCatSkillSelectionWindow(chooseSkillState->stateId);
	Widget *window = NULL;
	
	if (isCatWindow) {
		window = createSelectionWindowView(CAT_LABEL_TITLE, CAT_TITLE_POSX, CAT_TITLE_POSY, BUTTONS_NUMBER,
			 		CHOOSE_SKILL_BUTTONS_IMAGES, CHOOSE_SKILL_MARKED_BUTTONS_IMAGES);
	} else {
		window = createSelectionWindowView(MOUSE_LABEL_TITLE, MOUSE_TITLE_POSX, MOUSE_TITLE_POSY, BUTTONS_NUMBER,
			 		CHOOSE_SKILL_BUTTONS_IMAGES, CHOOSE_SKILL_MARKED_BUTTONS_IMAGES);
	}
	
	if (window == NULL || addUpDownArrows(window, BUTTON_SKILL_LEVEL, BUTTON_SKILL_UP, BUTTON_SKILL_DOWN) != 0) {
		isError = 1;
		return;
	}
	
	chooseSkillState->viewState = window;
	SelectionModel *model = createSelectionModelByState(chooseSkillState->stateId, initData);	
	chooseSkillState->model = model;
	
	if (isCatWindow) {
		skillLevel = model->gameConfig->catDifficulty;
	} else {
		skillLevel = model->gameConfig->mouseDifficulty;
	}
	
	if (updateSkillButton(window, skillLevel) != 0) {
		isError = 1;
		return;
	}
	
	markButton(window, &(model->markedButtonIndex), model->markedButtonIndex);	
	drawUITree(window);
}

void* viewTranslateEventChooseSkill(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

int handleSkillUp(SelectionModel *selectionModel, Widget *window, int isCatWindow) {
	if (isCatWindow) {
		if (selectionModel->gameConfig->catDifficulty < MAX_DIFFICULTY) {
			selectionModel->gameConfig->catDifficulty++;
			if (updateSkillButton(window, selectionModel->gameConfig->catDifficulty) != 0) {
				return 1;
			}
		}
	} else {
		if (selectionModel->gameConfig->mouseDifficulty < MAX_DIFFICULTY) {
			selectionModel->gameConfig->mouseDifficulty++;
			if (updateSkillButton(window, selectionModel->gameConfig->mouseDifficulty) != 0) {
				return 1;
			}
		}
	}
	return 0;
}

int handleSkillDown(SelectionModel *selectionModel, Widget *window, int isCatWindow) {
	if (isCatWindow) {
		if (selectionModel->gameConfig->catDifficulty > MIN_DIFFICULTY) {
			selectionModel->gameConfig->catDifficulty--;
			if (updateSkillButton(window, selectionModel->gameConfig->catDifficulty) != 0) {
				return 1;
			}
		}
	} else {
		if (selectionModel->gameConfig->mouseDifficulty > MIN_DIFFICULTY) {
			selectionModel->gameConfig->mouseDifficulty--;
			if (updateSkillButton(window, selectionModel->gameConfig->mouseDifficulty) != 0) {
				return 1;
			}
		}
	}
	return 0;
}

StateId handleButtonSelectedChooseSkill(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	int isCatWindow = isCatSkillSelectionWindow(selectionModel->stateId);	
	switch (buttonId) {
		case BUTTON_DONE:
			if (isCatWindow) {
				if (selectionModel->game == NULL) {
					return MOUSE_CHOOSE;
				} else {
					return GAME_PLAY;
				}
			} else {
				return GAME_PLAY;
			}
			break;
		case BUTTON_SKILL_UP:
			if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				if (handleSkillUp(selectionModel, window, isCatWindow) != 0) {
					isError = 1;
					return selectionModel->stateId;
				}
				isError = drawUITree(window);
			}
			break;
		case BUTTON_SKILL_DOWN:
			if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				if (handleSkillDown(selectionModel, window, isCatWindow) != 0) {
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

StateId presenterHandleEventChooseSkill(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow((SelectionModel *) model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedChooseSkill, selectionModel->stateId, BUTTONS_NUMBER);
}
