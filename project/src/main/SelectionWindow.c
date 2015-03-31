#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/DrawBoard.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Events.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "GUIState.h"
#include "LogicalEvents.h"

Widget* createSelectionWindowView(SelectionViewState viewState) {
	Widget *window = NULL, *buttonsPanel = NULL, *panel = NULL;
buttonsPanel	
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, viewState->windowCaption);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	panel = createPanel(0, 200, 100, 400, 600);
	setBgColor(panel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, panel);
	
	titleLabel = createLabel(0, 95, 0, 200, 70);
	setText(titleLabel, viewState->labelText, 20, 20);
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(panel, titleLabel);
	
	buttonsPanel = viewState->createButtonsPanel();
	addWidget(panel, buttonsPanel)
	
	return window;
}

void markButton(Widget *window, SelectionModel *selectionModel, int buttonIndex) {
	Widget *panel = getChildAtindex(window, 0);
	Widget *buttonsPanel = getChildAtindex(panel, 1);
	Widget *button = getChildAtindex(buttonsPanel, catChooseModel->markedButtonIndex);
	if (button != NULL) {
		setMarked(button, 0);
	}
	selectionModel->markedButtonIndex = buttonIndex;
	button = getChildAtindex(buttonsPanel, catChooseModel->markedButtonIndex);
	if (button != NULL) {
		setMarked(button, 1);
	}
	draw_board(window);
}

void startSelectionWindow(GUIState* state, void* initData) {
	// Create View
	SelectionViewState *viewState = (SelectionViewState *) state->viewState;
	viewState->window = createSelectionWindowView(viewState);
	
	// Create Model
	SelectionModel *selectionModel = (SelectionModel *) initData;
	SelectionModel *selectionModel = (SelectionModel *) state->model;
	
	if (initData->previousState != NULL) {
		SelectionModel *previousModel = (SelectionModel *) initData->previousState;
		selectionModel->model = selectionModel->createModel(previousModel->model);
		selectionModel->previousState = previousModel->previousState;
		selectionModel->markedButtonId = previousModel->markedButtonId;
	} else {
		selectionModel->model = selectionModel->createModel(NULL);
		selectionModel->previousState = NULL;
		selectionModel->markedButtonId = 0;
	}
	
	markButton(viewState->window, selectionModel, selectionModel->markedButtonId);	
	draw_board(viewState->window);
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
			} else {
				int *clickedIndexPtr = (int *)malloc(sizeof(int));
				*clickedIndexPtr = getId(widget);
				LogicalEvent *widgetLogicalEvent = createLogicalEventWithParams(MARK_AND_SELECT_BUTTON, clickedIndexPtr);
				return widgetLogicalEvent;
			}
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
                case SDLK_TAB: 
					return createLogicalEvent(MARK_NEXT_BUTTON);
					break;
                case SDLK_RETURN:
					return createLogicalEvent(SELECT_MARKED_BUTTON);
					break;
				default:
					 return createLogicalEvent(NO_EVENT);
			}
		default:
			return createLogicalEvent(NO_EVENT);
	}
}

StateId presenterHandleEventCatChoose(void* model, void* viewState, void* logicalEvent) {
	SelectionViewState *viewState = (SelectionViewState *) state->viewState;	
	SelectionModel *selectionModel = (SelectionModel *) initData;
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	int *clickedBtnIndex;
	
	switch (logicalEventPtr->type) {
		case MARK_NEXT_BUTTON:
			markButton(viewState->window, selectionModel, (selectionModel->markedButtonId + 1) % viewState->getButtonsNumber());
			break;
		case SELECT_MARKED_BUTTON:
			return selectionModel->handleButtonSelected(selectionModel->model, viewState->window);
		case MARK_AND_SELECT_BUTTON:
			clickedBtnIndex = (int *) logicalEventPtr->eventParams;
			markButton(viewState, model, *clickedBtnIndex);
			return selectionModel->handleButtonSelected(selectionModel->model, viewState->window);
		case QUIT_PRESSED:
			return QUIT;
		default:
			break;
	}
	// TODO free logical event
	return selectionModel->stateId;
}

void* stopSelectionWindow(GUIState* state) {
	// TODO think about freeing the previous data when back isn't clicked
	return state->model;
}
