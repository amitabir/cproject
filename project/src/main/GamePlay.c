#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/DrawBoard.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Events.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "GUIState.h"
#include "LogicalEvents.h"
#include "GamePlay.h"
#include "BoardPoint.h"
#include "Constants.h"
#include "GameModel.h"
#include "WorldFilesService.h"
#include "GameLogicService.h"

#define GRID_WIDTH 600
#define GRID_HEIGHT 650
#define GRID_X_POS 200
#define GRID_Y_POS 150
#define GRID_CELL_WIDTH GRID_WIDTH / BOARD_ROWS
#define GRID_CELL_HEIGHT GRID_HEIGHT / BOARD_COLS
#define DELAY_AFTER_MACHINE_CALC_MILLIS 1000

static char *PAUSE_BUTTON_MACHINE_TURN_TEXT = "Pause Before Next Move (Space)";
static char *PAUSE_BUTTON_HUMAN_TURN_TEXT = "Pause (Space)";
static char *PAUSE_BUTTON_RESUME_TEXT = "Resume Game (Space)";

static char *GAME_OVER_MESSAGE_CAT = "Game Over - Cat Wins!!!";
static char *GAME_OVER_MESSAGE_MOUSE = "Game Over - Mouse Wins!!!";
static char *GAME_OVER_MESSAGE_TIMEOUT = "Game Over - Timeout!!!";

static char *TURN_STATUS_TEXT_HUMAN_WAITING = "Human - waiting for next move...";
static char *TURN_STATUS_TEXT_MACHINE_COMPUTING =  "Machine - computing...";
static char *TURN_STATUS_TEXT_HUMAN_PAUSED = "Human - paused";
static char *TURN_STATUS_TEXT_MACHINE_PAUSED = "Machine - paused";

typedef enum {
	BUTTON_PAUSE,
	BUTTON_RECONFIG_MOUSE,
	BUTTON_RECONFIG_CAT,
	BUTTON_RESTART_GAME,
	BUTTON_MAIN_MENU,
	BUTTON_QUIT,
	BUTTON_GRID
} ButtonId;

void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad) {
	int padding = 0;
	if (pad) {
		padding = 5;
	}
	setPosX(label, point.col * GRID_CELL_WIDTH + padding);
	setPosY(label, point.row * GRID_CELL_HEIGHT + padding);
}

void placeWalls(Widget *gridButton, GameModel *gameModel) {
	int i,j;
	Widget *wallLabel;
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			if (gameModel->board[i][j] == WALL_TILE) {
				wallLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
				BoardPoint wallPoint;
				wallPoint.row = i;
				wallPoint.col = j;
				setGridLabelCoordinates(wallLabel, wallPoint, 1);
				setImage(wallLabel, "images/wall.bmp");
				addWidget(gridButton, wallLabel);
			} 
		}
	}
}

Widget* createGridPanel(GameModel *gameModel) {
	Widget *gridButton = NULL, *catLabel = NULL, *mouseLabel = NULL, *cheeseLabel = NULL;
	Widget *gridPanel = createPanel(0, GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT);
	setBgColor(gridPanel, createColor(0xFF, 0xFF, 0xFF));
	
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	gridButton = createButton(BUTTON_GRID, 0, 0, GRID_WIDTH, GRID_HEIGHT, colorKey, NULL, 0, 0, "images/grid.bmp", NULL);
	addWidget(gridPanel, gridButton);
	
	catLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
	setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
	setImage(catLabel, "images/cat.bmp");
	addWidget(gridButton, catLabel);
	
	mouseLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
	setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
	setImage(mouseLabel, "images/mouse.bmp");
	addWidget(gridButton, mouseLabel);
	
	cheeseLabel = createLabel(0, 0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
	setGridLabelCoordinates(cheeseLabel, gameModel->cheesePoint, 1);
	setImage(cheeseLabel, "images/cheese.bmp");
	addWidget(gridButton, cheeseLabel);
	
	placeWalls(gridButton, gameModel);
	return gridPanel;
}

Widget* createGamePlayView(GameModel *gameModel) {
	Widget *window = NULL;
	
	// Top panel widgets
	Widget *topPanel = NULL, *gameOverLabel = NULL, *gameStatusLabel = NULL, *turnStatusLabel = NULL, *pauseButton = NULL;
	
	// Sidebar widgets
	Widget *sidePanel = NULL, *reconfigureMouseButton = NULL, *reconfigureCatButton = NULL, *restartGameButton = NULL,
		 	*mainMenuButton = NULL, *quitButton = NULL;
	
	// Grid area
	Widget *gridPanel = NULL;
	
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	window = createWindow(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION);
	setBgColor(window, createColor(0xFF, 0xFF, 0xFF));
	
	topPanel = createPanel(0, 0, 0, 800, 150);
	setBgColor(topPanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, topPanel);
	
	gameOverLabel = createLabel(0, 200, 50, 500, 60);
	setBgColor(gameOverLabel, createColor(0xFF, 0xFF, 0xFF));
	setVisible(gameOverLabel, 0);
	addWidget(topPanel, gameOverLabel);
	
	gameStatusLabel = createLabel(0, 250, 0, 300, 50);
	setBgColor(gameStatusLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(topPanel, gameStatusLabel);
	
	turnStatusLabel = createLabel(0, 250, 50, 300, 50);
	setBgColor(turnStatusLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(topPanel, turnStatusLabel);
	
	pauseButton = createButton(BUTTON_PAUSE, 250, 100, 300, 50, colorKey, NULL, 0, 0, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(topPanel, pauseButton);
	
	sidePanel = createPanel(0, 0, 150, 200, 650);
	setBgColor(sidePanel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(window, sidePanel);
	
	reconfigureMouseButton = createButton(BUTTON_RECONFIG_MOUSE, 20, 50, 160, 60, colorKey, "Reconfigure Mouse (F1)", 5, 20, "images/smallButtonReg.bmp", "images/smallButtonMarked.bmp");
	setDisabledImage(reconfigureMouseButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, reconfigureMouseButton);
	
	reconfigureCatButton = createButton(BUTTON_RECONFIG_CAT, 20, 150, 160, 60, colorKey, "Reconfigure Cat (F2)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	setDisabledImage(reconfigureCatButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, reconfigureCatButton);
	
	restartGameButton = createButton(BUTTON_RESTART_GAME, 20, 250, 160, 60, colorKey, "Restart Game (F3)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	setDisabledImage(restartGameButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, restartGameButton);
	
	mainMenuButton = createButton(BUTTON_MAIN_MENU, 20, 350, 160, 60, colorKey, "Go to Main Menu (F4)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	setDisabledImage(mainMenuButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, mainMenuButton);
	
	quitButton = createButton(BUTTON_QUIT, 20, 450, 160, 60, colorKey, "Quit Program (F5)", 5, 20, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	setDisabledImage(quitButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, quitButton);
	
	gridPanel = createGridPanel(gameModel);
	addWidget(window, gridPanel);
	return window;
}

int isCurrentPlayerHuman(GameModel *gameModel) {
	return (gameModel->isMouseTurn && gameModel->gameConfig->isMouseHuman) || (!gameModel->isMouseTurn && gameModel->gameConfig->isCatHuman);
}

GameModel *createGameModel(void *initData) {
	SelectionModel *selectionModel = (SelectionModel *) initData;
	if (selectionModel->game != NULL) {
		updateConfigForGame(selectionModel->game, selectionModel->gameConfig);
		return selectionModel->game;
	}
	return createGameFromConfig(selectionModel->gameConfig);
}

void updateGameStatusLabel(GameModel *gameModel, Widget *gameStatusLabel) {
	char *gameStatusText = (char *) malloc(18 * sizeof(char));
	if (gameModel->isMouseTurn) {
		sprintf(gameStatusText, "Mouse's move (%d)", gameModel->numTurns);
	} else {
		sprintf(gameStatusText, "Cat's move (%d)", gameModel->numTurns);
	}
	setText(gameStatusLabel, gameStatusText, 5, 20);
}

void updateTurnStatusLabel(GameModel *gameModel, Widget *turnStatusLabel) {
	char *turnStatusText;
	if (!gameModel->isPaused) {
		if (isCurrentPlayerHuman(gameModel)) {
			turnStatusText = TURN_STATUS_TEXT_HUMAN_WAITING;
		} else {
			turnStatusText = TURN_STATUS_TEXT_MACHINE_COMPUTING;
		}
	} else {
		if (isCurrentPlayerHuman(gameModel)) {
			turnStatusText = TURN_STATUS_TEXT_HUMAN_PAUSED;
		} else {
			turnStatusText = TURN_STATUS_TEXT_MACHINE_PAUSED;
		}
	}
	setText(turnStatusLabel, turnStatusText, 5, 20);
}

void updatePauseButton(GameModel *gameModel, Widget* pauseButton) {
	char *pauseButtonText;
	if (gameModel->isPaused) {
		pauseButtonText = PAUSE_BUTTON_RESUME_TEXT;
	} else {
		if (isCurrentPlayerHuman(gameModel)) {
			pauseButtonText = PAUSE_BUTTON_HUMAN_TURN_TEXT;
		} else {
			pauseButtonText = PAUSE_BUTTON_MACHINE_TURN_TEXT;
		}
	}
	setText(pauseButton, pauseButtonText, 45, 20);
}

void updateTopPanel(Widget *topPanel, GameModel *gameModel) {
	Widget *gameOverLabel = getChildAtindex(topPanel, 0);
	Widget *gameStatusLabel = getChildAtindex(topPanel, 1);
	Widget *turnStatusLabel = getChildAtindex(topPanel, 2);
	Widget *pauseButton = getChildAtindex(topPanel, 3);
	
	if (!gameModel->isGameOver) {
		setVisible(gameStatusLabel, 1);
		setVisible(turnStatusLabel, 1);
		setVisible(pauseButton, 1);
		setVisible(gameOverLabel, 0);
		updateGameStatusLabel(gameModel, gameStatusLabel);
		updateTurnStatusLabel(gameModel, turnStatusLabel);
		updatePauseButton(gameModel, pauseButton);
	} else {
		setVisible(gameStatusLabel, 0);
		setVisible(turnStatusLabel, 0);
		setVisible(pauseButton, 0);
		setVisible(gameOverLabel, 1);
		switch (gameModel->winType) {
			case CAT_WINS:
				setText(gameOverLabel, GAME_OVER_MESSAGE_CAT, 45, 20);
				break;
			case MOUSE_WINS:
				setText(gameOverLabel, GAME_OVER_MESSAGE_MOUSE, 45, 20);
				break;
			case DRAW:
				setText(gameOverLabel, GAME_OVER_MESSAGE_TIMEOUT, 45, 20);
				break;
			default: break;
		}
	}
}

void updateSidePanel(Widget *sidePanel, GameModel *gameModel) {
	Widget *sideButton;
	int i;
	for (i = 0; i < 5; i++) {
		sideButton = getChildAtindex(sidePanel, i);
		setEnabled(sideButton, gameModel->isPaused || gameModel->isGameOver);
	}
}

void updateView(Widget *window, GameModel *gameModel) {
	Widget *topPanel = getChildAtindex(window, 0);
	updateTopPanel(topPanel, gameModel);
	
	Widget *sidePanel = getChildAtindex(window, 1);
	updateSidePanel(sidePanel, gameModel);

	Widget *gridPanel = getChildAtindex(window, 2);
	Widget *gridButton = getChildAtindex(gridPanel ,0);
	Widget *catLabel = getChildAtindex(gridButton, 0);
	Widget *mouseLabel = getChildAtindex(gridButton, 1);
	setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
	setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
	
	draw_board(window);
}

void handleMachineTurn(GameModel *gameModel, Widget *window) {
	handleMachineMove(gameModel);
	SDL_Delay(DELAY_AFTER_MACHINE_CALC_MILLIS);
	updateView(window, gameModel);
}

void startGamePlay(GUIState* gamePlayState, void* initData) {
	GameModel *gameModel = createGameModel(initData);	
	gamePlayState->model = gameModel;
	
	Widget *window =  createGamePlayView(gameModel);
	gamePlayState->viewState = window;
	updateView(window, gameModel);
}

LogicalEvent *getSelectedButtonEventForId(int buttonId) {
	int *clickedIndexPtr = (int *)malloc(sizeof(int));
	*clickedIndexPtr = buttonId;
	return createLogicalEventWithParams(SELECT_BUTTON, clickedIndexPtr);
}

LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos) {
	BoardPoint *point = (BoardPoint *) malloc(sizeof(BoardPoint));
	int cellH = GRID_CELL_HEIGHT, cellW = GRID_CELL_WIDTH;
	point->row = (yPos - GRID_Y_POS) / cellH;
	point->col = (xPos - GRID_X_POS) / cellW;
	return createLogicalEventWithParams(MOVE_POINT, point);
}

LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection moveDirection) {
	return createLogicalEventWithParams(MOVE_DIRECTION, &moveDirection);
}

void* viewTranslateEventGamePlay(void* viewState, SDL_Event* event) {
	Widget *widget;
	
	switch (event->type) {
		case SDL_QUIT:
			return createLogicalEvent(QUIT_PRESSED);
		case SDL_MOUSEBUTTONUP:
			widget = findWidgetFromTree(event->button.x, event->button.y, (Widget *) viewState);
			if (!isClickable(widget) || !isEnabled(widget)) {
				return createLogicalEvent(NO_EVENT);
			} else {
				int buttonId = getId(widget);
				if (buttonId == BUTTON_GRID) {
					return getMovePointLogicalEvent(event->button.x, event->button.y);
				}
				return getSelectedButtonEventForId(getId(widget));
			}
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_UP: return getMoveDirectionLogicalEvent(UP);
				case SDLK_DOWN: return getMoveDirectionLogicalEvent(DOWN);
				case SDLK_LEFT: return getMoveDirectionLogicalEvent(LEFT);
				case SDLK_RIGHT: return getMoveDirectionLogicalEvent(RIGHT);
	            case SDLK_SPACE: return getSelectedButtonEventForId(BUTTON_PAUSE);
                case SDLK_F1: return getSelectedButtonEventForId(BUTTON_RECONFIG_MOUSE);
	            case SDLK_F2: return getSelectedButtonEventForId(BUTTON_RECONFIG_CAT);
	            case SDLK_F3: return getSelectedButtonEventForId(BUTTON_RESTART_GAME);
	            case SDLK_F4: return getSelectedButtonEventForId(BUTTON_MAIN_MENU);
	            case SDLK_ESCAPE: return getSelectedButtonEventForId(BUTTON_QUIT);
				default: return createLogicalEvent(NO_EVENT);
			}
		default:
			return createLogicalEvent(NO_EVENT);
	}
}

StateId handleButtonSelectedGamePlay(void* model, Widget *window, int buttonId) {
	GameModel *gameModel = (GameModel *) model;	
	switch (buttonId) {
		case BUTTON_PAUSE:
			gameModel->isPaused = !gameModel->isPaused;
			updateView(window, gameModel);
			break;
		case BUTTON_RECONFIG_MOUSE:
			if (gameModel->gameConfig->isMouseHuman) {
				return MOUSE_CHOOSE;
			} else {
				return MOUSE_CHOOSE_SKILL;
			}
		case BUTTON_RECONFIG_CAT:
			if (gameModel->gameConfig->isCatHuman) {
				return CAT_CHOOSE;
			} else {
				return CAT_CHOOSE_SKILL;
			}
		case BUTTON_RESTART_GAME:
			resetGameFromWorldFile(gameModel);
			updateView(window, gameModel);
			break;
		case BUTTON_MAIN_MENU:
			return MAIN_MENU;
		case BUTTON_QUIT:
			return QUIT;
		default:
			break;
	}
	return GAME_PLAY;
}

void handleMove(GameModel *gameModel, Widget *window, MoveDirection moveDirection) {
	if (gameModel->isMouseTurn) {
		makeMouseMove(gameModel, moveDirection);
		updateView(window, gameModel);
	} else {
		makeCatMove(gameModel, moveDirection);
		updateView(window, gameModel);
	}
}

int getMoveDirectionFromCurrentPlayerPoint(GameModel *gameModel, BoardPoint newPoint, MoveDirection *moveDirection) {
	BoardPoint oldPoint;
	if (gameModel->isMouseTurn) {
		oldPoint = gameModel->mousePoint;
	} else {
		oldPoint = gameModel->catPoint;
	}
	return getMoveDirectionFromPoint(oldPoint, newPoint, moveDirection);
}

StateId presenterHandleEventGamePlay(void* model, void* viewState, void* logicalEvent) {
	LogicalEvent *logicalEventPtr = (LogicalEvent *) logicalEvent;
	Widget *window = (Widget *) viewState;
	GameModel *gameModel = (GameModel *) model;
	int *clickedBtnId;
	int makeMove = 0;
	BoardPoint *newPoint = NULL;
	MoveDirection moveDirection;
	
	switch (logicalEventPtr->type) {
		case NO_EVENT:
			if (!isCurrentPlayerHuman(gameModel) && !gameModel->isGameOver && !gameModel->isPaused) {
				handleMachineTurn(gameModel, window);
			}
			break;
		case SELECT_BUTTON:
			clickedBtnId = (int *) logicalEventPtr->eventParams;
			return handleButtonSelectedGamePlay(model, window, *clickedBtnId);
		case MOVE_POINT:
				newPoint = (BoardPoint *) logicalEventPtr->eventParams;
				makeMove = getMoveDirectionFromCurrentPlayerPoint(gameModel, *newPoint, &moveDirection);
				break;
		case MOVE_DIRECTION:
				moveDirection = *((MoveDirection *) logicalEventPtr->eventParams);
				makeMove = 1;
				break;
		case QUIT_PRESSED:
			return QUIT;
		default:
			break;
	}
	
	if (makeMove && !gameModel->isPaused && !gameModel->isGameOver) {
		handleMove(gameModel, window, moveDirection);
	}
	
	// TODO free logical event
	return GAME_PLAY;
}

void* prepareInitDataForConfigureWindows(GameModel *gameModel, StateId stateOnBack) {
	SelectionModel *selectionModelGame;
	SelectionModel *SelectionModelBack;
	selectionModelGame = createSelectionModel(GAME_PLAY, NULL, gameModel->gameConfig, gameModel);
	if (GAME_PLAY != stateOnBack) {
		SelectionModelBack = createSelectionModel(stateOnBack, selectionModelGame, gameModel->gameConfig, gameModel);
		return SelectionModelBack;
	}
	return selectionModelGame;
}

void* stopGamePlay(GUIState* state, StateId nextStateId) {
	GameModel *gameModel = (GameModel *) state->model;
	
	switch (nextStateId) {
		case MAIN_MENU:
			return NULL;
		case MOUSE_CHOOSE:
		case CAT_CHOOSE:
			return prepareInitDataForConfigureWindows(gameModel, GAME_PLAY);
		case MOUSE_CHOOSE_SKILL:
			return prepareInitDataForConfigureWindows(gameModel, MOUSE_CHOOSE);
		case CAT_CHOOSE_SKILL:
			return prepareInitDataForConfigureWindows(gameModel, CAT_CHOOSE);
		default:
			return NULL;
	}
}
