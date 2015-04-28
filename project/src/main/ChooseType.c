#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/WidgetFactory.h"
#include "GUI/UITree.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "ChooseType.h"


#define BUTTONS_NUMBER 3

#define CAT_TITLE_POSX 55
#define CAT_TITLE_POSY 25
#define MOUSE_TITLE_POSX 45
#define MOUSE_TITLE_POSY 25 

const char *CHOOSE_TYPE_BUTTONS_IMAGES[] = {"images/Buttons/Human.bmp", "images/Buttons/Machine.bmp", "images/Buttons/Back.bmp"};
const char *CHOOSE_TYPE_MARKED_BUTTONS_IMAGES[] = {"images/Buttons/HumanMarked.bmp", "images/Buttons/MachineMarked.bmp", "images/Buttons/BackMarked.bmp"};

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

int getButtonIdByPlayerType(int isHuman) {
	if (isHuman) {
		return BUTTON_HUMAN_TYPE;
	} else {
		return BUTTON_MACHINE_TYPE;
	}
}

void setMarkedButtonByConfig(SelectionModel *model, int isCatWindow) {
	if (isCatWindow) {
		model->markedButtonIndex = getButtonIdByPlayerType(model->gameConfig->isCatHuman);
	} else {
		model->markedButtonIndex = getButtonIdByPlayerType(model->gameConfig->isMouseHuman);
	}
}

void startChooseType(GUIState* chooseTypeState, void* initData) {
	int isCatWindow = isCatSelectionWindow(chooseTypeState->stateId);
	if (isCatWindow) {
		chooseTypeState->viewState = createSelectionWindowView(CAT_LABEL_TITLE, CAT_TITLE_POSX, CAT_TITLE_POSY, BUTTONS_NUMBER, 
				CHOOSE_TYPE_BUTTONS_IMAGES, CHOOSE_TYPE_MARKED_BUTTONS_IMAGES);
	} else {
		chooseTypeState->viewState = createSelectionWindowView(MOUSE_LABEL_TITLE, MOUSE_TITLE_POSX, MOUSE_TITLE_POSY, BUTTONS_NUMBER, 
				CHOOSE_TYPE_BUTTONS_IMAGES, CHOOSE_TYPE_MARKED_BUTTONS_IMAGES);
	}
	if (chooseTypeState->viewState == NULL) {
		isError = 1;
		return;
	}
	
	SelectionModel *model = createSelectionModelByState(chooseTypeState->stateId, initData);
	if (model == NULL) {
		isError = 1;
		return;
	}
	chooseTypeState->model = model;
		
	setMarkedButtonByConfig(model, isCatWindow);
	markButton((Widget *) chooseTypeState->viewState, &(model->markedButtonIndex), model->markedButtonIndex);	
	isError = drawUITree((Widget *) chooseTypeState->viewState);
}


void* viewTranslateEventChooseType(void* viewState, SDL_Event* event) {
	return viewTranslateEventSelectionWindow(viewState, event);
}

void updateConfig(SelectionModel *selectionModel, int isCatWindow, int isHuman) {
	if (isCatWindow) {
		selectionModel->gameConfig->isCatHuman = isHuman;
	} else {
		selectionModel->gameConfig->isMouseHuman = isHuman;
	}
}

StateId handleButtonSelectedChooseType(void* model, Widget *window, int buttonId) {
	SelectionModel *selectionModel = (SelectionModel *) model;	
	int isCatWindow = isCatSelectionWindow(selectionModel->stateId);
	switch (buttonId) {
		case BUTTON_HUMAN_TYPE:
			updateConfig(selectionModel, isCatWindow, 1);
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

StateId presenterHandleEventChooseType(void* model, void* viewState, void* logicalEvent) {
	SelectionModel *selectionModel = (SelectionModel *) model;		
	return presenterHandleEventSelectionWindow(model, (Widget *) viewState, logicalEvent, &(selectionModel->markedButtonIndex), 
					handleButtonSelectedChooseType, selectionModel->stateId, BUTTONS_NUMBER);
}
