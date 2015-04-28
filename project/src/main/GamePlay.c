#include "GUI/Widget.h"
#include "GUI/Window.h"
#include "GUI/UITree.h"
#include "GUI/WidgetFactory.h"
#include "GUI/Color.h"
#include "GUI/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "GamePlay.h"
#include "Model/BoardPoint.h"
#include "Model/Constants.h"
#include "Model/WorldFilesService.h"
#include "GeneralGameWindow.h"
#include "Model/GameLogicService.h"

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
} ButtonId;

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
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	window = createWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	
	topPanel = createPanel(0, 0, 800, 150, bgColor);
	addWidget(window, topPanel);
	
	gameOverLabel = createLabel(200, 50, 500, 60);
	setBgColor(gameOverLabel, createColor(0xFF, 0xFF, 0xFF));
	setVisible(gameOverLabel, 0);
	addWidget(topPanel, gameOverLabel);
	
	gameStatusLabel = createLabel(250, 0, 300, 50);
	setBgColor(gameStatusLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(topPanel, gameStatusLabel);
	
	turnStatusLabel = createLabel(250, 50, 300, 50);
	setBgColor(turnStatusLabel, createColor(0xFF, 0xFF, 0xFF));
	addWidget(topPanel, turnStatusLabel);
	
	pauseButton = createButton(BUTTON_PAUSE, 250, 100, 300, 50, colorKey, NULL, 0, 0, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
	addWidget(topPanel, pauseButton);
	
	sidePanel = createPanel(0, 150, 200, 650, bgColor);
	addWidget(window, sidePanel);
	
	reconfigureMouseButton = createButton(BUTTON_RECONFIG_MOUSE, 20, 50, 160, 60, colorKey, "Reconfigure\nMouse (F1)", 5, 0, "images/smallButtonReg.bmp", "images/smallButtonMarked.bmp");
	setDisabledImage(reconfigureMouseButton, "images/smallButtonDisabled.bmp");
	addWidget(sidePanel, reconfigureMouseButton);
	
	reconfigureCatButton = createButton(BUTTON_RECONFIG_CAT, 20, 150, 160, 60, colorKey, "Reconfigure\nCat (F2)", 5, 0, "images/smallButtonReg.bmp","images/smallButtonMarked.bmp");
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
	GameModel *result = NULL;
	SelectionModel *selectionModel = (SelectionModel *) initData;
	if (selectionModel->game != NULL) {
		if (updateConfigForGame(selectionModel->game, selectionModel->gameConfig) == 0) {
			result = selectionModel->game;
		}
	} else {
		result = createGameFromConfig(selectionModel->gameConfig);
	}
	freeSelectionModel(selectionModel, 1, 0);
	return result;
}

void updateGameStatusLabel(GameModel *gameModel, Widget *gameStatusLabel) {
	char gameStatusText[18];
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
	
	drawUITree(window);	
}

void handleMachineTurn(GameModel *gameModel, Widget *window) {
	handleMachineMove(gameModel);
	SDL_Delay(DELAY_AFTER_MACHINE_CALC_MILLIS);
	updateView(window, gameModel);
}

void startGamePlay(GUIState* gamePlayState, void* initData) {
	GameModel *gameModel = createGameModel(initData);
	if (gameModel == NULL) {
		isError = 1;
		return;
	}
	gamePlayState->model = gameModel;
		
	Widget *window = createGamePlayView(gameModel);
	gamePlayState->viewState = window;
	checkGameOver(gameModel);
	updateView(window, gameModel);
}

void* viewTranslateEventGamePlay(void* viewState, SDL_Event* event) {
	Widget *widget;
	
	switch (event->type) {
		case SDL_QUIT:
			return createLogicalEvent(QUIT_PRESSED);
		case SDL_MOUSEBUTTONUP:
			widget = findWidgetFromTree(event->button.x, event->button.y, (Widget *) viewState);
			if (!isClickable(widget) || !isEnabled(widget)) {
				return createLogicalEvent(IRRELEVANT_EVENT);
			} else {
				int buttonId = getId(widget);
				if (buttonId == BUTTON_GRID) {
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
	            case SDLK_SPACE: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_PAUSE);
                case SDLK_F1: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_RECONFIG_MOUSE);
	            case SDLK_F2: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_RECONFIG_CAT);
	            case SDLK_F3: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_RESTART_GAME);
	            case SDLK_F4: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_MAIN_MENU);
	            case SDLK_ESCAPE: return createSelectedButtonEventForId(SELECT_BUTTON, BUTTON_QUIT);
				default: return createLogicalEvent(IRRELEVANT_EVENT);
			}
		default:
			return createLogicalEvent(IRRELEVANT_EVENT);
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
			if (resetGameFromWorldFile(gameModel) != 0) {
				isError = 1;
				return GAME_PLAY;
			}
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
	StateId result = GAME_PLAY;
	if (logicalEvent == NULL) {
		isError = 1;
		return result;
	}
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
			result = handleButtonSelectedGamePlay(model, window, *clickedBtnId);
			break;
		case MOVE_POINT:
			newPoint = (BoardPoint *) logicalEventPtr->eventParams;
			makeMove = getMoveDirectionFromCurrentPlayerPoint(gameModel, *newPoint, &moveDirection);			
			break;
		case MOVE_DIRECTION:
			moveDirection = *((MoveDirection *) logicalEventPtr->eventParams);
			makeMove = 1;
			break;
		case QUIT_PRESSED:
			result = QUIT;
		default:
			break;
	}
	
	if (makeMove && !gameModel->isPaused && !gameModel->isGameOver) {
		handleMove(gameModel, window, moveDirection);
	}
	
	freeLogicalEvent(logicalEvent);
	return result;
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
	freeWidget((Widget *) state->viewState);
	GameModel *gameModel = (GameModel *) state->model;
	
	switch (nextStateId) {
		case MAIN_MENU:
			freeGame(gameModel);
			return NULL;
		case MOUSE_CHOOSE:
		case CAT_CHOOSE:
			return prepareInitDataForConfigureWindows(gameModel, GAME_PLAY);
		case MOUSE_CHOOSE_SKILL:
			return prepareInitDataForConfigureWindows(gameModel, MOUSE_CHOOSE);
		case CAT_CHOOSE_SKILL:
			return prepareInitDataForConfigureWindows(gameModel, CAT_CHOOSE);
		default:
			freeGame(gameModel);
			return NULL;
	}
}
