#include "GUIState.h"
#include "GUI/DrawBoard.h"
#include "LogicalEvents.h"
#include "GUI/Events.h"

SelectionModel *createSelectionModel(StateId stateId, SelectionModel *previousStateModel, GameConfigurationModel *previousConfig, GameModel *game) {
	SelectionModel *selectionModel = NULL;
	selectionModel = (SelectionModel *) malloc(sizeof(SelectionModel));
	selectionModel->stateId = stateId;
	selectionModel->previousStateModel = previousStateModel;
	if (previousConfig != NULL) {
		selectionModel->gameConfig = createGameConfig(previousConfig->isCatHuman, previousConfig->catDifficulty,
			 		previousConfig->isMouseHuman, previousConfig->mouseDifficulty, previousConfig->worldIndex);
	} else {
		selectionModel->gameConfig = createGameConfigDefault();
	}
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

void markButton(Widget *window, int *markButtonPtr, int newButtonToMark) {
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, 1);
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
				return createLogicalEvent(NO_EVENT);
			} else if (isMarkable(widget)) {
				int *clickedIndexPtr = (int *)malloc(sizeof(int));
				*clickedIndexPtr = getId(widget);
				LogicalEvent *widgetLogicalEvent = createLogicalEventWithParams(MARK_AND_SELECT_BUTTON, clickedIndexPtr);
				return widgetLogicalEvent;
			} else {
				int *clickedIndexPtr = (int *)malloc(sizeof(int));
				*clickedIndexPtr = getId(widget);
				LogicalEvent *widgetLogicalEvent = createLogicalEventWithParams(SELECT_BUTTON, clickedIndexPtr);
				return widgetLogicalEvent;
			}
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
                case SDLK_TAB: 
					return createLogicalEvent(MARK_NEXT_BUTTON);
                case SDLK_RETURN:
					return createLogicalEvent(SELECT_MARKED_BUTTON);
				default:
					 return createLogicalEvent(NO_EVENT);
			}
		default:
			return createLogicalEvent(NO_EVENT);
	}
}

StateId presenterHandleEventSelectionWindow(void* model, Widget *window, void* logicalEvent, int *markButtonPtr, 
				StateId (*handleButtonSelected)(void *model, Widget *window, int buttonId), StateId sameStateId, int buttonsNumber) {
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	int *clickedBtnId;
	
	switch (logicalEventPtr->type) {
		case MARK_NEXT_BUTTON:
			markButton(window, markButtonPtr, (*markButtonPtr + 1) % buttonsNumber);
			draw_board(window);
			break;
		case SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			return handleButtonSelected(model, window, *clickedBtnId);
		case SELECT_MARKED_BUTTON:
			return handleButtonSelected(model, window, *markButtonPtr);
		case MARK_AND_SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			markButton(window, markButtonPtr, *clickedBtnId);
			draw_board(window);
			return handleButtonSelected(model, window, *clickedBtnId);
		case QUIT_PRESSED:
			return QUIT;
		default:
			break;
	}
	// TODO free logical event
	return sameStateId;
}
