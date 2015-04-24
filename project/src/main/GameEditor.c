#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/UITree.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "Model/BoardPoint.h"
#include "Model/Constants.h"
#include "Model/GameModel.h"
#include "Model/WorldFilesService.h"
#include "GameEditor.h"
#include "Model/GameLogicService.h"
#include "GeneralGameWindow.h"


#define GRID_WIDTH 600
#define GRID_HEIGHT 650
#define GRID_X_POS 200
#define GRID_Y_POS 150
#define GRID_CELL_WIDTH GRID_WIDTH / BOARD_ROWS
#define GRID_CELL_HEIGHT GRID_HEIGHT / BOARD_COLS

typedef enum {
	BUTTON_SAVE_WORLD,
	BUTTON_MAIN_MENU,
	BUTTON_QUIT,
	BUTTON_PLACE_MOUSE,
	BUTTON_PLACE_CAT,
	BUTTON_PLACE_CHEESE,
	BUTTON_PLACE_WALL,
	BUTTON_PLACE_EMPTY,
} ButtonId;

Widget* createEditGameView(GameEditorModel *editModel) {
	Widget *window = NULL;
	
	// Top panel widgets
	Widget *topPanel = NULL, *titleLabel = NULL, *saveWorldButton = NULL, *mainMenuButton = NULL, *quitButton = NULL;
	
	// Sidebar widgets
	Widget *sidePanel = NULL, *placeMouseButton = NULL, *placeCatButton = NULL, *placeCheeseButton = NULL,
		 	*placeWallButton = NULL, *placeEmptyButton = NULL;
	
	// Grid area
	Widget *gridPanel = NULL, *gridButton = NULL, *markLabel = NULL;
	
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	topPanel = createPanel(0, 0, 0, 800, 150);
	setBgColor(topPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, topPanel);
	
	titleLabel = createLabel(0, 350, 20, 300, 50);
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	if (editModel->game->gameConfig != NULL) {
		char worldIndexStr[8];
		sprintf(worldIndexStr, "World %d", editModel->game->gameConfig->worldIndex);
		setText(titleLabel, worldIndexStr, 5, 10);
	} else {
		setText(titleLabel, "Create World", 5, 10);
	}
	addWidget(topPanel, titleLabel);
	
	saveWorldButton = createButton(BUTTON_SAVE_WORLD, 70, 80, 160, 50, colorKey, "Save World (S)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(topPanel, saveWorldButton);
	
	mainMenuButton = createButton(BUTTON_MAIN_MENU, 300, 80, 160, 50, colorKey, "Go to Main Menu (F1)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(topPanel, mainMenuButton);
	
	quitButton = createButton(BUTTON_QUIT, 550, 80, 160, 50, colorKey, "Quit Program (Esc)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(topPanel, quitButton);
	
	sidePanel = createPanel(0, 0, 150, 200, 650);
	setBgColor(sidePanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, sidePanel);
	
	placeMouseButton = createButton(BUTTON_PLACE_MOUSE, 20, 50, 160, 60, colorKey, "Place Mouse (M)", 5, 20, "images/smallButtonReg.bmp", "images/smallButtonMarked.bmp");
	addWidget(sidePanel, placeMouseButton);
	
	placeCatButton = createButton(BUTTON_PLACE_CAT, 20, 150, 160, 60, colorKey, "Place Cat (C)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(sidePanel, placeCatButton);
	
	placeCheeseButton = createButton(BUTTON_PLACE_CHEESE, 20, 250, 160, 60, colorKey, "Place Cheese (P)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(sidePanel, placeCheeseButton);
	
	placeWallButton = createButton(BUTTON_PLACE_WALL, 20, 350, 160, 60, colorKey, "Place Wall (W)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(sidePanel, placeWallButton);
	
	placeEmptyButton = createButton(BUTTON_PLACE_EMPTY, 20, 450, 160, 60, colorKey, "Place Empty Space (Space)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(sidePanel, placeEmptyButton);
	
	gridPanel = createPanel(0, GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT);
	setBgColor(gridPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, gridPanel);
	
	gridButton = createButton(BUTTON_GRID, 0, 0, GRID_WIDTH, GRID_HEIGHT, colorKey, NULL, 0, 0, "images/grid.bmp", NULL);
	addWidget(gridPanel, gridButton);
	
	markLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH + 5, GRID_CELL_HEIGHT+ 5);
	setGridLabelCoordinates(markLabel, createPoint(0,0), 0);
	setColorKey(markLabel, colorKey);
	setImage(markLabel, "images/border.bmp");
	addWidget(gridPanel, markLabel);
	
	return window;
	
}

GameEditorModel *createGameEditorModel(StateId stateId, void *initData) {	
	GameEditorModel *editModel = NULL;
	
	// Create the model struct for the editor window
	if ((editModel = (GameEditorModel *) malloc(sizeof(GameEditorModel))) == NULL) {
		// Malloc has failed and the user is notified
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	
	editModel->stateId = stateId;
	if (initData == NULL) {
		editModel->game = createEmptyGame();
	} else {
		SelectionModel *selectionModel = (SelectionModel *) initData;
		if (selectionModel->game != NULL) { // returing from save/error
			editModel->game = selectionModel->game;
		} else {
			editModel->game = createGameFromConfig(selectionModel->gameConfig);
		}
		freeSelectionModel(selectionModel, 1, 0);
	}
	editModel->markedPoint = createPoint(0,0);
	return editModel;
}

void updateGridButton(Widget *gridButton, GameModel *gameModel) {
	removeAllChildren(gridButton);
	
	if (!isEmptyPoint(gameModel->catPoint)) {
		Widget *catLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
		setImage(catLabel, "images/cat.bmp");
		addWidget(gridButton, catLabel);
	}
	
	if (!isEmptyPoint(gameModel->mousePoint)) {
		Widget *mouseLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
		setImage(mouseLabel, "images/mouse.bmp");
		addWidget(gridButton, mouseLabel);
	}
	
	if (!isEmptyPoint(gameModel->cheesePoint)) {
		Widget *cheeseLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(cheeseLabel, gameModel->cheesePoint, 1);
		setImage(cheeseLabel, "images/cheese.bmp");
		addWidget(gridButton, cheeseLabel);
	}
	
	placeWalls(gridButton, gameModel);
}

void updateEditView(Widget *window, GameEditorModel *editModel) {
	Widget *gridPanel = getChildAtindex(window, 2);
	Widget *gridButton = getChildAtindex(gridPanel, 0);
	updateGridButton(gridButton, editModel->game);
	drawUITree(window);
}

void startEditGame(GUIState* editGameState, void* initData) {
	GameEditorModel *editModel = createGameEditorModel(editGameState->stateId, initData);
	if (editModel == NULL) {
		isError = 1;
		return;
	}
	editGameState->model = editModel;
	
	Widget *window = createEditGameView(editModel);
	editGameState->viewState = window;
	updateEditView(window, editModel);
}

void* viewTranslateEventEditGame(void* viewState, SDL_Event* event) {
	Widget *widget;
	
	switch (event->type) {
		case SDL_QUIT:
			return createLogicalEvent(QUIT_PRESSED);
		case SDL_MOUSEBUTTONUP:
			widget = findWidgetFromTree(event->button.x, event->button.y, (Widget *) viewState);
			if (!isClickable(widget) && getId(getParent(widget)) != BUTTON_GRID) {
				return createLogicalEvent(IRRELEVANT_EVENT);
			} else {
				if (getId(widget) == BUTTON_GRID || getId(getParent(widget)) == BUTTON_GRID) {
					return getMovePointLogicalEvent(event->button.x, event->button.y);
				}
				return createSelectedButtonEventForId(SELECT_BUTTON, getId(widget));
			}
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_UP: return getMoveDirectionLogicalEvent(UP);
				case SDLK_DOWN: return getMoveDirectionLogicalEvent(DOWN);
				case SDLK_LEFT: return getMoveDirectionLogicalEvent(LEFT);
				case SDLK_RIGHT: return getMoveDirectionLogicalEvent(RIGHT);
				case SDLK_s: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_SAVE_WORLD);
				case SDLK_F1: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_MAIN_MENU);
	            case SDLK_ESCAPE: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_QUIT);
                case SDLK_m: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PLACE_MOUSE);
	            case SDLK_c: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PLACE_CAT);
	            case SDLK_p: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PLACE_CHEESE);
	            case SDLK_w: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PLACE_WALL);
	            case SDLK_SPACE: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PLACE_EMPTY);
				default: return createLogicalEvent(IRRELEVANT_EVENT);
			}
		default:
			return createLogicalEvent(IRRELEVANT_EVENT);
	}
}

void resetPoint(GameModel *game, BoardPoint point) {
	game->board[point.row][point.col] = EMPTY_TILE;
	if (arePointsEqual(game->catPoint, point)) {
		game->catPoint = createEmptyPoint();
	}
	if (arePointsEqual(game->mousePoint, point)) {
		game->mousePoint = createEmptyPoint();
	}
	if (arePointsEqual(game->cheesePoint, point)) {
		game->cheesePoint = createEmptyPoint();
	}
}

StateId handleSave(GameModel *game) {
	if (checkGameValidSetMsg(game)) {
		return SAVE_GAME;
	} else {
		return ERROR;
	}
}

StateId handleButtonSelectedEditGame(void* model, Widget *window, int buttonId) {
	GameEditorModel *editModel = (GameEditorModel *) model;	
	GameModel *game = editModel->game;
	switch (buttonId) {
		case BUTTON_SAVE_WORLD:
			return handleSave(game);
		case BUTTON_PLACE_MOUSE:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->mousePoint = editModel->markedPoint;
			editModel->game->isMouseTurn = 1;
			updateEditView(window, editModel);
			break;
		case BUTTON_PLACE_CAT:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->catPoint = editModel->markedPoint;
			editModel->game->isMouseTurn = 0;
			updateEditView(window, editModel);
			break;
		case BUTTON_PLACE_CHEESE:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->cheesePoint = editModel->markedPoint;
			updateEditView(window, editModel);
			break;
		case BUTTON_PLACE_WALL:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->board[editModel->markedPoint.row][editModel->markedPoint.col] = WALL_TILE;
			updateEditView(window, editModel);
			break;
		case BUTTON_PLACE_EMPTY:
			resetPoint(game, editModel->markedPoint);
			updateEditView(window, editModel);
			break;
		case BUTTON_MAIN_MENU:
			return MAIN_MENU;
		case BUTTON_QUIT:
			return QUIT;
		default:
			break;
	}
	return editModel->stateId;
}

void moveMarkedPoint(GameEditorModel *editModel, Widget* window, BoardPoint newPoint) {
	if (newPoint.row >= 0 && newPoint.row < BOARD_ROWS && newPoint.col >=0 && newPoint.col < BOARD_COLS) {
		editModel->markedPoint = newPoint;
		Widget *gridPanel = getChildAtindex(window, 2);
		Widget *markLabel = getChildAtindex(gridPanel, 1);
		setGridLabelCoordinates(markLabel, editModel->markedPoint, 0);
		drawUITree(window);
	}
}

StateId presenterHandleEventEditGame(void* model, void* viewState, void* logicalEvent) {
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	Widget *window = (Widget *) viewState;
	GameEditorModel *editModel = (GameEditorModel *) model;
	StateId result = editModel->stateId;
	int *clickedBtnId;
	BoardPoint newPoint;
	MoveDirection moveDirection;
	
	switch (logicalEventPtr->type) {
		case SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			result = handleButtonSelectedEditGame(model, window, *clickedBtnId);
		case MOVE_POINT:
				newPoint = *((BoardPoint *) logicalEventPtr->eventParams);
				moveMarkedPoint(editModel, window, newPoint);
				break;
		case MOVE_DIRECTION:
				moveDirection = *((MoveDirection *) logicalEventPtr->eventParams);
				newPoint = getMovedPoint(editModel->markedPoint, moveDirection);
				moveMarkedPoint(editModel, window, newPoint);
				break;
		case QUIT_PRESSED:
			result = QUIT;
		default:
			break;
	}
	
	freeLogicalEvent(logicalEvent);
	return result;
}

void* prepareInitDataForSaveWindow(GameModel *gameModel) {
	SelectionModel *selectionModelGame;
	selectionModelGame = createSelectionModel(GAME_EDITOR, NULL, gameModel->gameConfig, gameModel);
	if (gameModel->gameConfig == NULL) {
		selectionModelGame->gameConfig = NULL;
	}
	return selectionModelGame;
}

void* stopEditGame(GUIState* state, StateId nextStateId) {
	void *nextStateInitData = NULL;
	GameEditorModel *editModel = (GameEditorModel *) state->model;
	freeWidget((Widget *) state->viewState);
	
	if (nextStateId == SAVE_GAME || nextStateId == ERROR) {	
		nextStateInitData = prepareInitDataForSaveWindow(editModel->game);
	} else {
		freeGame(editModel->game);
	}
	free(editModel);
	return nextStateInitData;
}
