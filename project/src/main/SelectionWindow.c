#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "GUI/UITree.h"
#include "Model/GameModel.h"
#include "GUI/GUIConstants.h"

const char WINDOW_CAPTION[] = "Cat And Mouse";
const char LOGO_IMAGE_FILE_NAME[] = "images/GameLogo.bmp";

const char UP_ARROW_BUTTON_IMAGE[] = "images/Buttons/UpArrow.bmp";
const char DOWN_ARROW_BUTTON_IMAGE[] =  "images/Buttons/DownArrow.bmp";

SelectionModel *createSelectionModel(StateId stateId, SelectionModel *previousStateModel, GameConfigurationModel *previousConfig, GameModel *game) {
	SelectionModel *selectionModel = NULL;
	if ((selectionModel = (SelectionModel *) malloc(sizeof(SelectionModel))) == NULL) {
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	selectionModel->stateId = stateId;
	selectionModel->previousStateModel = previousStateModel;
	if (previousConfig != NULL) {
		selectionModel->gameConfig = createGameConfig(previousConfig->isCatHuman, previousConfig->catDifficulty,
			 		previousConfig->isMouseHuman, previousConfig->mouseDifficulty, previousConfig->worldIndex);
	} else {
		selectionModel->gameConfig = createGameConfigDefault();
	}
	
	// If configuration creation failed, free the pointer and return NULL.
	if (selectionModel->gameConfig == NULL) {
		free(selectionModel);
		return NULL;
	}
	
	// Set default parameters for the model
	selectionModel->markedButtonIndex = 0;
	selectionModel->game = game;
	return selectionModel;
}

SelectionModel *createSelectionModelByState(StateId stateId, void *initData) {
	if (initData == NULL) {
		return createSelectionModel(stateId, NULL, NULL, NULL);
	} else {		
		SelectionModel *previousStateModel = (SelectionModel *) initData;
		if (previousStateModel->stateId == stateId) {
			// Restore previous state
			return initData;
		} else { // Arrived from another state
			return createSelectionModel(stateId, previousStateModel, previousStateModel->gameConfig, previousStateModel->game);
		}
	}
}

void freeSelectionModel(SelectionModel *selectionModel, int freePrevious, int shouldFreeGame) {
	if (selectionModel->gameConfig != NULL) {
		freeConfig(selectionModel->gameConfig);
	}
	
	if (selectionModel->previousStateModel != NULL && freePrevious) {
		freeSelectionModel(selectionModel->previousStateModel, 1, shouldFreeGame);
	}
	
	if (selectionModel->game != NULL && shouldFreeGame) {
		freeGame(selectionModel->game);
	}
	
	free(selectionModel);
}

void markButton(Widget *window, int *markButtonPtr, int newButtonToMark) {
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, getChildrenNum(panel) - 1);
	Widget *button = getChildAtindex(buttonsPanel, *markButtonPtr);
	
	if (button != NULL) {
		setMarked(button, 0);
	}
	*markButtonPtr = newButtonToMark;
	button = getChildAtindex(buttonsPanel, newButtonToMark);
	if (button != NULL) {		
		setMarked(button, 1);
	}
}

void* viewTranslateEventSelectionWindow(void* viewState, SDL_Event* event) {
	Widget *widget;
	
	switch (event->type) {
		case SDL_QUIT:
			return createLogicalEvent(QUIT_PRESSED);
		case SDL_MOUSEBUTTONUP:
			widget = findWidgetFromTree(event->button.x, event->button.y, (Widget *) viewState);
			if (!isClickable(widget)) {
				return createLogicalEvent(IRRELEVANT_EVENT);
			} else if (isMarkable(widget)) {
				return createSelectedButtonEventForId(MARK_AND_SELECT_BUTTON, getId(widget));
			} else {
				return createSelectedButtonEventForId(SELECT_BUTTON, getId(widget));
			}
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
                case SDLK_TAB: 
					return createLogicalEvent(MARK_NEXT_BUTTON);
                case SDLK_RETURN:
					return createLogicalEvent(SELECT_MARKED_BUTTON);
				default:
					 return createLogicalEvent(IRRELEVANT_EVENT);
			}
		default:
			return createLogicalEvent(IRRELEVANT_EVENT);
	}
}

StateId presenterHandleEventSelectionWindow(void* model, Widget *window, void* logicalEvent, int *markButtonPtr, 
				StateId (*handleButtonSelected)(void *model, Widget *window, int buttonId), StateId sameStateId, int buttonsNumber) {
	StateId result;
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	int *clickedBtnId;
	switch (logicalEventPtr->type) {
		case MARK_NEXT_BUTTON:
			markButton(window, markButtonPtr, (*markButtonPtr + 1) % buttonsNumber);
			isError = drawUITree(window);
			result = sameStateId;
			break;
		case SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			result = handleButtonSelected(model, window, *clickedBtnId);
			break;
		case SELECT_MARKED_BUTTON:
			result = handleButtonSelected(model, window, *markButtonPtr);
			break;
		case MARK_AND_SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			markButton(window, markButtonPtr, *clickedBtnId);
			isError = drawUITree(window);
			result = handleButtonSelected(model, window, *clickedBtnId);
			break;
		case QUIT_PRESSED:
			result = QUIT;
			break;
		default:
			result = sameStateId;
	}
	freeLogicalEvent(logicalEvent);
	return result;
}

void* stopSelectionWindow(GUIState* state, StateId nextStateId) {
	// Free the window and all its widgets (only if created).
	if (state->viewState != NULL) {
		freeWidget((Widget *) state->viewState);
	}
	
	// If the model was not created - nothing to do, return NULL pointer.
	if (state->model == NULL) {
		return NULL;
	}
	
	SelectionModel *selectionModel = (SelectionModel *) state->model;
	
	if (nextStateId == QUIT) {
		if (selectionModel != NULL) {
			freeSelectionModel(selectionModel, 1, 1);
		}
	}
	
	if (nextStateId == selectionModel->previousStateModel->stateId && nextStateId != GAME_PLAY) {
		freeSelectionModel((SelectionModel *) state->model, 0, 0);
		return selectionModel->previousStateModel;
	} else {
		return selectionModel;
	}
}

Widget* createSelectionButton(Widget *parent, int buttonId, int posX, int posY, int width, int height,
	 	const char* buttonImage, const char* buttonMarkedImage) {
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	Widget *button = createButton(buttonId, posX, posY, width, height, colorKey, NULL, 0, 0, buttonImage, buttonMarkedImage);
	if (button == NULL) {
		return NULL;
	}
	
	addWidget(parent, button);
	return button;
}

Widget* createSelectionWindowView(char *titleText, int textPosx, int textPosY, int buttonsNumber, const char *buttonImages[],
	 		const char *buttonMarkedImages[]) {
	Widget *window = NULL, *panel = NULL, *buttonsPanel = NULL, *logoLabel = NULL, *titleLabel = NULL;
	int buttonIdx;
	
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	
	panel = createPanel(MAIN_PANEL_POSX, MAIN_PANEL_POSY, MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT, bgColor);
	addWidget(window, panel);
	
	logoLabel = createLabel(LOGO_LABEL_POSX, LOGO_LABEL_POSY, LOGO_LABEL_WIDTH, LOGO_LABEL_HEIGHT);
	if (setImage(logoLabel, LOGO_IMAGE_FILE_NAME) != 0) {
		freeWidget(window);
		return NULL;
	}
	addWidget(panel, logoLabel);
	
	int paddingForButtonsPanel = 0;
	if (titleText != NULL) {
		titleLabel = createLabel(TITLE_LABEL_POSX, TITLE_LABEL_POSY, TITLE_LABEL_WIDTH, TITLE_LABEL_HEIGHT);
		setText(titleLabel, titleText, textPosx, textPosY);
		setBgColor(titleLabel, createColor(0xFF,0xFF,0x11));
		addWidget(panel, titleLabel);
		paddingForButtonsPanel += TITLE_LABEL_HEIGHT + PADDING_AFTER_TITLE;
	}
	
	buttonsPanel =  createPanel(BUTTONS_PANEL_POSX, BUTTONS_PANEL_POSY + paddingForButtonsPanel, BUTTONS_PANEL_WIDTH,
		 	BUTTONS_PANEL_HEIGHT, bgColor);
	addWidget(panel, buttonsPanel);
	
	for (buttonIdx = 0; buttonIdx < buttonsNumber; buttonIdx++) {
		if (createSelectionButton(buttonsPanel, buttonIdx, BUTTON_POSX, BASE_BUTTON_POSY * buttonIdx, BUTTON_WIDTH,
			 		BUTTON_HEIGHT, buttonImages[buttonIdx], buttonMarkedImages[buttonIdx]) == NULL) {
			freeWidget(window);
			return NULL;
		}
	}
		
	return window;
}

int addUpDownArrows(Widget *window, int buttonId, int buttonUpId, int buttonDownId) {
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, getChildrenNum(panel) - 1);
	Widget *button = getChildAtindex(buttonsPanel, buttonId);
	
	Widget *buttonUp = createSelectionButton(button, buttonUpId, BUTTON_UP_POSX, BUTTON_UP_POSY, BUTTON_UP_WIDTH,
		 		BUTTON_UP_HEIGHT, UP_ARROW_BUTTON_IMAGE, NULL);
	if (buttonUp == NULL) {
		return 1;
	}
	setMarkable(buttonUp, 0);
	
	Widget *buttonDown = createSelectionButton(button, buttonDownId, BUTTON_DOWN_POSX, BUTTON_DOWN_POSY,
		 	BUTTON_DOWN_WIDTH, BUTTON_DOWN_HEIGHT, DOWN_ARROW_BUTTON_IMAGE, NULL);
	if (buttonDown == NULL) {
		return 1;
	}
	setMarkable(buttonDown, 0);
	
	return 0;
}
