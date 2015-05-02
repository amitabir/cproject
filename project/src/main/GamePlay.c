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
#define SIDE_BUTTONS_NUM 5

#define GAME_STATUS_TEXT_MAX_LENGTH 18
	
#define TOP_PANEL_WIDTH 800
#define TOP_PANEL_HEIGHT 150
#define TOP_PANEL_POSX 0
#define TOP_PANEL_POSY 0

#define SIDE_PANEL_WIDTH 200
#define SIDE_PANEL_HEIGHT 650
#define SIDE_PANEL_POSX 0
#define SIDE_PANEL_POSY 150

#define SIDE_BUTTON_WIDTH 150
#define SIDE_BUTTON_HEIGHT 60
#define SIDE_BUTTON_POSX 25
#define SIDE_BASE_BUTTON_POSY 50
#define SIDE_BASE_SPACING 120

const char *PAUSE_BUTTON_RESUME_IMAGE = "images/Buttons/ResumeGame.bmp";
const char *PAUSE_BUTTON_RESUME_MARKED_IMAGE = "images/Buttons/ResumeGameMarked.bmp";
	
const char *PAUSE_BUTTON_HUMAN_TURN_IMAGE = "images/Buttons/Pause.bmp";
const char *PAUSE_BUTTON_HUMAN_TURN_MARKED_IMAGE = "images/Buttons/PauseMarked.bmp";
	
const char *PAUSE_BUTTON_MACHINE_TURN_IMAGE = "images/Buttons/PauseBeforeNextMove.bmp";
const char *PAUSE_BUTTON_MACHINE_TURN_MARKED_IMAGE = "images/Buttons/PauseBeforeNextMoveMarked.bmp";

const char *GAME_OVER_MESSAGE_CAT = "Game Over - Cat Wins!!!";
const char *GAME_OVER_MESSAGE_MOUSE = "Game Over - Mouse Wins!!!";
const char *GAME_OVER_MESSAGE_TIMEOUT = "Game Over - Timeout!!!";

const char *TURN_STATUS_TEXT_HUMAN_WAITING = "Human - waiting for next move...";
const char *TURN_STATUS_TEXT_MACHINE_COMPUTING =  "Machine - computing...";
const char *TURN_STATUS_TEXT_HUMAN_PAUSED = "Human - paused";
const char *TURN_STATUS_TEXT_MACHINE_PAUSED = "Machine - paused";

const char *GAME_PLAY_BUTTONS_IMAGES[] = {NULL, "images/Buttons/ReconfigureMouse.bmp", "images/Buttons/ReconfigureCat.bmp",
	 			"images/Buttons/RestartGame.bmp", "images/Buttons/GoToMainMenu.bmp",  "images/Buttons/QuitProgram.bmp"};
const char *GAME_PLAY_MARKED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/ReconfigureMouseMarked.bmp", "images/Buttons/ReconfigureCatMarked.bmp", 
				"images/Buttons/RestartGameMarked.bmp", "images/Buttons/GoToMainMenuMarked.bmp", "images/Buttons/QuitProgramMarked.bmp"};
const char *GAME_PLAY_DISABLED_BUTTONS_IMAGES[] = {NULL, "images/Buttons/ReconfigureMouseDisabled.bmp", "images/Buttons/ReconfigureCatDisabled.bmp",
	 			"images/Buttons/RestartGameDisabled.bmp", "images/Buttons/GoToMainMenuDisabled.bmp", "images/Buttons/QuitProgramDisabled.bmp"};

typedef enum {
	BUTTON_PAUSE,
	BUTTON_RECONFIG_MOUSE,
	BUTTON_RECONFIG_CAT,
	BUTTON_RESTART_GAME,
	BUTTON_MAIN_MENU,
	BUTTON_QUIT,
} ButtonId;

Widget* createSideButton(Widget *parent, int buttonId, int posX, int posY, int width, int height,
	 	const char* buttonImage, const char* buttonMarkedImage, const char* buttonDisabledImage) {
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	Widget *button = createButton(buttonId, posX, posY, width, height, colorKey, NULL, 0, 0, buttonImage, buttonMarkedImage);
	if (button == NULL) {
		return NULL;
	}
	
	if (setDisabledImage(button, buttonDisabledImage) != 0) {
		freeWidget(button);
		return NULL;
	}
	
	addWidget(parent, button);
	return button;
}

Widget* createGamePlayView(GameModel *gameModel) {
	Widget *window = NULL;
	
	// Top panel widgets
	Widget *topPanel = NULL, *gameOverLabel = NULL, *gameStatusLabel = NULL, *turnStatusLabel = NULL, *pauseButton = NULL;
	
	// Sidebar widgets
	Widget *sidePanel = NULL;
	
	// Grid area
	Widget *gridPanel = NULL;
	
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	window = createWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	
	topPanel = createPanel(TOP_PANEL_POSX, TOP_PANEL_POSY, TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT, bgColor);
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
	
	pauseButton = createButton(BUTTON_PAUSE, 250, 100, 300, 50, colorKey, NULL, 0, 0, NULL, NULL);
	addWidget(topPanel, pauseButton);
	
	sidePanel = createPanel(SIDE_PANEL_POSX, SIDE_PANEL_POSY, SIDE_PANEL_WIDTH, SIDE_PANEL_HEIGHT, bgColor);
	addWidget(window, sidePanel);
	
	int buttonIdx;
	for (buttonIdx = BUTTON_RECONFIG_MOUSE; buttonIdx <= SIDE_BUTTONS_NUM; buttonIdx++) {
		if (createSideButton(sidePanel, buttonIdx, SIDE_BUTTON_POSX, SIDE_BASE_BUTTON_POSY + SIDE_BASE_SPACING * (buttonIdx - 1), SIDE_BUTTON_WIDTH,
			 		SIDE_BUTTON_HEIGHT, GAME_PLAY_BUTTONS_IMAGES[buttonIdx], GAME_PLAY_MARKED_BUTTONS_IMAGES[buttonIdx],
					GAME_PLAY_DISABLED_BUTTONS_IMAGES[buttonIdx]) == NULL) {
			freeWidget(window);
			return NULL;
		}
	}
	
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
	char gameStatusText[GAME_STATUS_TEXT_MAX_LENGTH];
	if (gameModel->isMouseTurn) {
		sprintf(gameStatusText, "Mouse's move (%d)", gameModel->numTurns);
	} else {
		sprintf(gameStatusText, "Cat's move (%d)", gameModel->numTurns);
	}
	setText(gameStatusLabel, gameStatusText, 5, 20);
}

void updateTurnStatusLabel(GameModel *gameModel, Widget *turnStatusLabel) {
	const char *turnStatusText;
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

int setPauseButtonImages(Widget *pauseButton, const char* imageName, const char *markedImageName) {
	if (setImage(pauseButton, imageName) != 0) {
		return 1;
	}
	if (setMarkedImage(pauseButton, markedImageName) != 0) {
		return 1;
	}
	return 0;
}

int updatePauseButton(GameModel *gameModel, Widget* pauseButton) {
	if (gameModel->isPaused) {
		if (setPauseButtonImages(pauseButton, PAUSE_BUTTON_RESUME_IMAGE, PAUSE_BUTTON_RESUME_MARKED_IMAGE) != 0) {
			return 1;
		}
	} else {
		if (isCurrentPlayerHuman(gameModel)) {
			if (setPauseButtonImages(pauseButton, PAUSE_BUTTON_HUMAN_TURN_IMAGE, PAUSE_BUTTON_HUMAN_TURN_MARKED_IMAGE) != 0) {
				return 1;
			}
		} else {
			if (setPauseButtonImages(pauseButton, PAUSE_BUTTON_MACHINE_TURN_IMAGE, PAUSE_BUTTON_MACHINE_TURN_MARKED_IMAGE) != 0) {
				return 1;
			}
		}
	}
	return 0;
}

int updateTopPanel(Widget *topPanel, GameModel *gameModel) {
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
		if (updatePauseButton(gameModel, pauseButton) != 0) {
			return 1;
		}
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
	return 0;
}

void updateSidePanel(Widget *sidePanel, GameModel *gameModel) {
	Widget *sideButton;
	int i;
	for (i = 0; i < 5; i++) {
		sideButton = getChildAtindex(sidePanel, i);
		setEnabled(sideButton, gameModel->isPaused || gameModel->isGameOver);
	}
}

int updateView(Widget *window, GameModel *gameModel) {
	Widget *topPanel = getChildAtindex(window, 0);
	if (updateTopPanel(topPanel, gameModel) != 0) {
		return 1;
	}
	
	Widget *sidePanel = getChildAtindex(window, 1);
	updateSidePanel(sidePanel, gameModel);
	
	Widget *gridPanel = getChildAtindex(window, 2);
	Widget *gridButton = getChildAtindex(gridPanel ,0);
	Widget *catLabel = getChildAtindex(gridButton, 0);
	Widget *mouseLabel = getChildAtindex(gridButton, 1);
	setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
	setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
	
	return drawUITree(window);	
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
	if (window == NULL) {
		isError = 1;
		return;
	}
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
