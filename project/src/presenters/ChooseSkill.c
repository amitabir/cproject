#include <string.h>
#include "../gui/UITree.h"
#include "../gui/WidgetFactory.h"
#include "../model/Constants.h"
#include "SelectionWindow.h"

// Number of buttons in this selection window
#define BUTTONS_NUMBER 3

// Position for the title lables
#define CAT_TITLE_POSX 25
#define CAT_TITLE_POSY 5
#define MOUSE_TITLE_POSX 14
#define MOUSE_TITLE_POSY 5 

// Max length for images file names
#define SKILL_IMAGE_NAME_LENGTH 26
#define SKILL_MARKED_IMAGE_NAME_LENGTH 32

// Titles for window
static char *CAT_LABEL_TITLE = "Choose Cat Skill Level:";
static char *MOUSE_LABEL_TITLE = "Choose Mouse Skill Level:";

const char *CHOOSE_SKILL_BUTTONS_IMAGES[] = {NULL, "images/Buttons/Done.bmp", "images/Buttons/Back.bmp"};
const char *CHOOSE_SKILL_MARKED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/DoneMarked.bmp", "images/Buttons/BackMarked.bmp"};

const char *SKILL_IMAGE_NAME = "images/Buttons/Skill%d.bmp";
const char *SKILL_MARKED_IMAGE_NAME = "images/Buttons/Skill%dMarked.bmp";

// An enum for the button id to recognize the button when clicked
typedef enum {
	BUTTON_SKILL_LEVEL,
	BUTTON_DONE,
	BUTTON_BACK,
	BUTTON_SKILL_UP,
	BUTTON_SKILL_DOWN
} ButtonId;

// Returns 1 if the current skill selection window is for the cat, 1 otherwise (mouse)/
int isCatSkillSelectionWindow(StateId stateId) {
	if (stateId == CAT_CHOOSE_SKILL) {
		return 1;
	}
	return 0;
}

// Update the skill button image according to the new skillNumber given. Returns 0 on sucess, 1 otherwise.
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

// Start method for the choose skill window. See header file.
void startChooseSkill(GUIState* chooseSkillState, void* initData) {	
	int skillLevel;
	int isCatWindow = isCatSkillSelectionWindow(chooseSkillState->stateId);
	Widget *window = NULL;
	
	// Behave differently for cat/mouse skill selection (another title)
	if (isCatWindow) {
		window = createSelectionWindowView(CAT_LABEL_TITLE, CAT_TITLE_POSX, CAT_TITLE_POSY, BUTTONS_NUMBER,
			 		CHOOSE_SKILL_BUTTONS_IMAGES, CHOOSE_SKILL_MARKED_BUTTONS_IMAGES);
	} else {
		window = createSelectionWindowView(MOUSE_LABEL_TITLE, MOUSE_TITLE_POSX, MOUSE_TITLE_POSY, BUTTONS_NUMBER,
			 		CHOOSE_SKILL_BUTTONS_IMAGES, CHOOSE_SKILL_MARKED_BUTTONS_IMAGES);
	}
	
	// stop executing in case of errors
	if (window == NULL || addUpDownArrows(window, BUTTON_SKILL_LEVEL, BUTTON_SKILL_UP, BUTTON_SKILL_DOWN) != 0) {
		isError = 1;
		return;
	}
	
	// Create the model
	chooseSkillState->viewState = window;
	SelectionModel *model = createSelectionModelByState(chooseSkillState->stateId, initData);	
	chooseSkillState->model = model;
	
	// Update the skill button according to the difficulty in the configuration
	if (isCatWindow) {
		skillLevel = model->gameConfig->catDifficulty;
	} else {
		skillLevel = model->gameConfig->mouseDifficulty;
	}
	if (updateSkillButton(window, skillLevel) != 0) {
		isError = 1;
		return;
	}
	
	// Mark the current marked button and draw the widgets.
	markButton(window, &(model->markedButtonIndex), model->markedButtonIndex);	
	drawUITree(window);
}

// Handles the case when the skill should be updated by 1 up. Rerturns 0 on sucess, 1 otherwise.
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

// Handles the case when the skill should be updated by 1 down. Rerturns 0 on sucess, 1 otherwise.
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

// Handles selected button according to the given buttonId. 
StateId handleButtonSelectedChooseSkill(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	int isCatWindow = isCatSkillSelectionWindow(selectionModel->stateId);	
	switch (buttonId) {
		case BUTTON_DONE:
			if (isCatWindow) {
				// Move to mouse windows if no game is set, meaning we are not in the middle of a game. 
				if (selectionModel->game == NULL) {
					return MOUSE_CHOOSE;
				} else {
					return GAME_PLAY;
				}
			} else {
				// After mouse skill selection we always move to game play.
				return GAME_PLAY;
			}
			break;
		case BUTTON_SKILL_UP:
			// Update skill by 1 up.
			if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				if (handleSkillUp(selectionModel, window, isCatWindow) != 0) {
					isError = 1;
					return selectionModel->stateId;
				}
				isError = drawUITree(window);
			}
			break;
		case BUTTON_SKILL_DOWN:
			// Update skill by 1 down.
			if (selectionModel->markedButtonIndex == BUTTON_SKILL_LEVEL) {
				if (handleSkillDown(selectionModel, window, isCatWindow) != 0) {
					isError = 1;
					return selectionModel->stateId;
				}
				isError = drawUITree(window);
			}	
			break;
		case BUTTON_BACK:
			// Go back to previose state
			return selectionModel->previousStateModel->stateId;
		default:
			break;
	}
	return selectionModel->stateId;
}

// Handle logical event by calling using the specific handleButtonSelectedChooseSkill method.
StateId presenterHandleEventChooseSkill(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;
	return presenterHandleEventSelectionWindow((SelectionModel *) model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedChooseSkill, selectionModel->stateId, BUTTONS_NUMBER);
}
