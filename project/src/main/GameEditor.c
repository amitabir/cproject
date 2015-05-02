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

#define BUTTONS_NUM 8
#define TOP_BUTTONS_NUM 3

#define TOP_BUTTON_WIDTH 200
#define TOP_BUTTON_HEIGHT 50
#define TOP_BUTTON_POSY 80
#define TOP_BUTTON_BASE_POXS 10
#define TOP_BUTTON_SPACING 290

#define EDITOR_TITLE_LABEL_MAX_LENGTH 8

#define EDITOR_TITLE_LABEL_WIDTH 150
#define EDITOR_TTILE_LABEL_HEIGHT 50
#define EDITOR_TITLE_LABEL_CREATE_WORLD_POSX 330
#define EDITOR_TITLE_LABEL_WORLD_INDEX_POSX 355
#define EDITOR_TITLE_LABEL_POSY 20

#define EDITOR_TITLE_TEXT_POSX 5
#define EDITOR_TITLE_TEXT_POSY 20

const char *EDITOR_TITLE_CREATE_WORLD = "Create World";
const char *EDITOR_TITLE_WORLD_INDEX = "World %d";

const char *GAME_EDITOR_BUTTONS_IMAGES[] = {"images/Buttons/SaveWorldEditor.bmp", "images/Buttons/GoToMainMenuEditor.bmp",
	 			"images/Buttons/QuitProgramEditor.bmp", "images/Buttons/PlaceMouse.bmp",  "images/Buttons/PlaceCat.bmp", "images/Buttons/PlaceCheese.bmp",
				"images/Buttons/PlaceWall.bmp", "images/Buttons/PlaceEmptySpace.bmp"};
const char *GAME_EDITOR_MARKED_BUTTONS_IMAGES[] = {"images/Buttons/SaveWorldEditorMarked.bmp", "images/Buttons/GoToMainMenuEditorMarked.bmp", 
				"images/Buttons/QuitProgramEditorMarked.bmp", "images/Buttons/PlaceMouseMarked.bmp", "images/Buttons/PlaceCatMarked.bmp",
				"images/Buttons/PlaceCheeseMarked.bmp", "images/Buttons/PlaceWallMarked.bmp", "images/Buttons/PlaceEmptySpaceMarked.bmp"};

const char *FRAME_IMAGE = "images/Buttons/frame.bmp";

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

Widget* createEditorButton(Widget *parent, int buttonId, int posX, int posY, int width, int height,
	 	const char* buttonImage, const char* buttonMarkedImage) {
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	Widget *button = createButton(buttonId, posX, posY, width, height, colorKey, NULL, 0, 0, buttonImage, buttonMarkedImage);
	if (button == NULL) {
		return NULL;
	}
	
	addWidget(parent, button);
	return button;
}

Widget *createTitleLabel(GameConfigurationModel *gameConfig) {
	char worldIndexStr[EDITOR_TITLE_LABEL_MAX_LENGTH];
	
	Widget *titleLabel = createLabel(0, EDITOR_TITLE_LABEL_POSY, EDITOR_TITLE_LABEL_WIDTH, EDITOR_TTILE_LABEL_HEIGHT);
	setBgColor(titleLabel, createColor(0xFF, 0xFF, 0xFF));
	if (gameConfig != NULL) {
		sprintf(worldIndexStr, EDITOR_TITLE_WORLD_INDEX, gameConfig->worldIndex);
		setText(titleLabel, worldIndexStr, EDITOR_TITLE_TEXT_POSX, EDITOR_TITLE_TEXT_POSY);
		setPosX(titleLabel, EDITOR_TITLE_LABEL_WORLD_INDEX_POSX);
	} else {
		setText(titleLabel, EDITOR_TITLE_CREATE_WORLD, EDITOR_TITLE_TEXT_POSX, EDITOR_TITLE_TEXT_POSY);
		setPosX(titleLabel, EDITOR_TITLE_LABEL_CREATE_WORLD_POSX);
	}
	
	return titleLabel;
}

Widget* createEditGameView(GameEditorModel *editModel) {
	Widget *window = NULL, *topPanel = NULL, *titleLabel = NULL, *sidePanel = NULL, *gridPanel = NULL, *markLabel = NULL;
	int buttonIdx;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	
	window = createWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	topPanel = createPanel(TOP_PANEL_POSX, TOP_PANEL_POSY, TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT, bgColor);
	addWidget(window, topPanel);
	
	titleLabel = createTitleLabel(editModel->game->gameConfig);
	addWidget(topPanel, titleLabel);
	
	// Add buttons to the top panel
	for (buttonIdx = BUTTON_SAVE_WORLD; buttonIdx < TOP_BUTTONS_NUM; buttonIdx++) {
		if (createEditorButton(topPanel, buttonIdx, TOP_BUTTON_BASE_POXS + buttonIdx * TOP_BUTTON_SPACING, TOP_BUTTON_POSY, TOP_BUTTON_WIDTH,
			 		TOP_BUTTON_HEIGHT, GAME_EDITOR_BUTTONS_IMAGES[buttonIdx], GAME_EDITOR_MARKED_BUTTONS_IMAGES[buttonIdx]) == NULL) {
			freeWidget(window);
			return NULL;
		}
	}

	// Create the side panel
	sidePanel = createPanel(SIDE_PANEL_POSX, SIDE_PANEL_POSY, SIDE_PANEL_WIDTH, SIDE_PANEL_HEIGHT, bgColor);
	addWidget(window, sidePanel);	
	
	// Add buttons to the side panel
	for (buttonIdx = BUTTON_PLACE_MOUSE; buttonIdx < BUTTONS_NUM; buttonIdx++) {	
		if (createEditorButton(sidePanel, buttonIdx, SIDE_BUTTON_POSX, SIDE_BASE_BUTTON_POSY + SIDE_BASE_SPACING * (buttonIdx - TOP_BUTTONS_NUM),
		 	SIDE_BUTTON_WIDTH,	SIDE_BUTTON_HEIGHT, GAME_EDITOR_BUTTONS_IMAGES[buttonIdx], GAME_EDITOR_MARKED_BUTTONS_IMAGES[buttonIdx]) == NULL) {
			freeWidget(window);
			return NULL;
		}
	}
	
	// Create the grid panel and button
	gridPanel = createGridPanel(window, editModel->game);
	if (gridPanel == NULL) {
		freeWidget(window);
		return NULL;
	}
	
	// Add the marking label to the grid panel
	markLabel = createLabel(0, 0, GRID_CELL_WIDTH + 5, GRID_CELL_HEIGHT+ 5);
	setGridLabelCoordinates(markLabel, createPoint(0,0), 0);
	setColorKey(markLabel, colorKey);
	if (setImage(markLabel, FRAME_IMAGE) != 0) {
		freeWidget(window);
		return NULL;
	}
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

int updateGridButton(Widget *gridButton, GameModel *gameModel) {
	removeAllChildren(gridButton);
	
	if (!isEmptyPoint(gameModel->catPoint)) {
		Widget *catLabel = createLabel(0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
		if (setImage(catLabel, CAT_IMAGE) != 0) {
			freeWidget(catLabel);
			return 1;
		}
		addWidget(gridButton, catLabel);
	}
	
	if (!isEmptyPoint(gameModel->mousePoint)) {
		Widget *mouseLabel = createLabel(0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
		if (setImage(mouseLabel, MOUSE_IMAGE) != 0) {
			freeWidget(mouseLabel);
			return 1;
		}
		addWidget(gridButton, mouseLabel);
	}
	
	if (!isEmptyPoint(gameModel->cheesePoint)) {
		Widget *cheeseLabel = createLabel(0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(cheeseLabel, gameModel->cheesePoint, 1);
		if (setImage(cheeseLabel, CHEESE_IMAGE) != 0) {
			freeWidget(cheeseLabel);
			return 1;
		}
		addWidget(gridButton, cheeseLabel);
	}
	
	return placeWalls(gridButton, gameModel);
}

int updateEditView(Widget *window, GameEditorModel *editModel) {
	Widget *gridPanel = getChildAtindex(window, 2);
	Widget *gridButton = getChildAtindex(gridPanel, 0);
	if (updateGridButton(gridButton, editModel->game) != 0) {
		return 1;
	}
	return drawUITree(window);
}

void startEditGame(GUIState* editGameState, void* initData) {
	GameEditorModel *editModel = createGameEditorModel(editGameState->stateId, initData);
	if (editModel == NULL) {
		isError = 1;
		return;
	}
	editGameState->model = editModel;	
	
	Widget *window = createEditGameView(editModel);
	if (window == NULL) {
		isError = 1;
		return;
	}
	editGameState->viewState = window;
	isError = updateEditView(window, editModel);
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
			if (updateEditView(window, editModel) != 0) {
				isError = 1;
				return editModel->stateId;
			}
			break;
		case BUTTON_PLACE_CAT:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->catPoint = editModel->markedPoint;
			editModel->game->isMouseTurn = 0;
			if (updateEditView(window, editModel) != 0) {
				isError = 1;
				return editModel->stateId;
			}
			break;
		case BUTTON_PLACE_CHEESE:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->cheesePoint = editModel->markedPoint;
			if (updateEditView(window, editModel) != 0) {
				isError = 1;
				return editModel->stateId;
			}
			break;
		case BUTTON_PLACE_WALL:
			resetPoint(game, editModel->markedPoint); 
			editModel->game->board[editModel->markedPoint.row][editModel->markedPoint.col] = WALL_TILE;
			if (updateEditView(window, editModel) != 0) {
				isError = 1;
				return editModel->stateId;
			}
			break;
		case BUTTON_PLACE_EMPTY:
			resetPoint(game, editModel->markedPoint);
			if (updateEditView(window, editModel) != 0) {
				isError = 1;
				return editModel->stateId;
			}
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

int moveMarkedPoint(GameEditorModel *editModel, Widget* window, BoardPoint newPoint) {
	if (newPoint.row >= 0 && newPoint.row < BOARD_ROWS && newPoint.col >=0 && newPoint.col < BOARD_COLS) {
		editModel->markedPoint = newPoint;
		Widget *gridPanel = getChildAtindex(window, 2);
		Widget *markLabel = getChildAtindex(gridPanel, 1);
		setGridLabelCoordinates(markLabel, editModel->markedPoint, 0);
		return drawUITree(window);
	}
	return 0;
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
			break;
		case MOVE_POINT:
				newPoint = *((BoardPoint *) logicalEventPtr->eventParams);
				if (moveMarkedPoint(editModel, window, newPoint) != 0) {
					isError = 1;
				}
				break;
		case MOVE_DIRECTION:
				moveDirection = *((MoveDirection *) logicalEventPtr->eventParams);
				newPoint = getMovedPoint(editModel->markedPoint, moveDirection);
				if (moveMarkedPoint(editModel, window, newPoint) != 0) {
					isError = 1;
				}
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
		freeConfig(selectionModelGame->gameConfig);
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
