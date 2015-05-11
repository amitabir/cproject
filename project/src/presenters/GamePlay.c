#include "../gui/UITree.h"
#include "../gui/WidgetFactory.h"
#include "../gui/GUIConstants.h"
#include "SelectionWindow.h"
#include "LogicalEvents.h"
#include "GamePlay.h"
#include "../services/BoardPoint.h"
#include "../model/Constants.h"
#include "../services/WorldFilesService.h"
#include "GeneralGameWindow.h"
#include "../services/GameLogicService.h"

#define DELAY_AFTER_MACHINE_CALC_MILLIS 1000
#define SIDE_BUTTONS_NUM 5

#define GAME_STATUS_TEXT_MAX_LENGTH 18

// Game over label configuration
#define GAME_OVER_LABEL_WIDTH 500
#define GAME_OVER_LABEL_HEIGHT 40
#define GAME_OVER_LABEL_POSY (TOP_PANEL_HEIGHT - GAME_OVER_LABEL_HEIGHT) / 2

#define GAME_OVER_MOUSE_LABEL_POSX 260
#define GAME_OVER_CAT_LABEL_POSX 274
#define GAME_OVER_TIMEOUT_LABEL_POSX 277

#define GAME_OVER_TEXT_POSX 0
#define GAME_OVER_TEXT_POSY 0

// Game status label configuration
#define GAME_STATUS_LABEL_WIDTH 200
#define GAME_STATUS_LABEL_HEIGHT 40
#define GAME_STATUS_LABEL_POSY 10

#define GAME_STATUS_MOUSE_LABEL_POSX 305
#define GAME_STATUS_CAT_LABEL_POSX 315

#define GAME_STATUS_TEXT_POSX 0
#define GAME_STATUS_TEXT_POSY 0

// Turn status label configuration
#define TURN_STATUS_LABEL_WIDTH 400
#define TURN_STATUS_LABEL_HEIGHT 40
#define TURN_STATUS_LABEL_POSY 50

#define TURN_STATUS_HUMAN_POSX 222
#define TURN_STATUS_MACHINE_POSX 285
#define TURN_STATUS_HUMAN_PAUSED_PAUSED_POSX 320
#define TURN_STATUS_MACHINE_PAUSED_POSX 307

#define TURN_STATUS_TEXT_POSX 0
#define TURN_STATUS_TEXT_POSY 0

// Pause Button configuration
#define PAUSE_BUTTON_WIDTH 250
#define PAUSE_BUTTON_HEIGHT 50
#define PAUSE_BUTTON_POSX (TOP_PANEL_WIDTH - PAUSE_BUTTON_WIDTH) / 2
#define PAUSE_BUTTON_POSY 90

const char *PAUSE_BUTTON_RESUME_IMAGE = "images/Buttons/ResumeGame.bmp";
const char *PAUSE_BUTTON_RESUME_MARKED_IMAGE = "images/Buttons/ResumeGameMarked.bmp";
	
const char *PAUSE_BUTTON_HUMAN_TURN_IMAGE = "images/Buttons/Pause.bmp";
const char *PAUSE_BUTTON_HUMAN_TURN_MARKED_IMAGE = "images/Buttons/PauseMarked.bmp";
	
const char *PAUSE_BUTTON_MACHINE_TURN_IMAGE = "images/Buttons/PauseBeforeNextMove.bmp";
const char *PAUSE_BUTTON_MACHINE_TURN_MARKED_IMAGE = "images/Buttons/PauseBeforeNextMoveMarked.bmp";

const char *GAME_STATUS_MOUSE_MOVE =  "Mouse's move (%d)";
const char *GAME_STATUS_CAT_MOVE =  "Cat's move (%d)";

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

// Create and reuturn a side button in the side panel, or NULL if an error occured.
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

// Create and returns the side panel, or NULL if an error occured.
Widget *createSidePanel(Widget *parent) {
	Color bgColor = createColor(0xFF, 0xFF, 0xFF);
	Widget *sidePanel = createPanel(SIDE_PANEL_POSX, SIDE_PANEL_POSY, SIDE_PANEL_WIDTH, SIDE_PANEL_HEIGHT, bgColor);
	addWidget(parent, sidePanel);
	
	int buttonIdx;
	for (buttonIdx = BUTTON_RECONFIG_MOUSE; buttonIdx <= SIDE_BUTTONS_NUM; buttonIdx++) {
		if (createSideButton(sidePanel, buttonIdx, SIDE_BUTTON_POSX, SIDE_BASE_BUTTON_POSY + SIDE_BASE_SPACING * (buttonIdx - 1), SIDE_BUTTON_WIDTH,
			 		SIDE_BUTTON_HEIGHT, GAME_PLAY_BUTTONS_IMAGES[buttonIdx], GAME_PLAY_MARKED_BUTTONS_IMAGES[buttonIdx],
					GAME_PLAY_DISABLED_BUTTONS_IMAGES[buttonIdx]) == NULL) {
			freeWidget(sidePanel);
			return NULL;
		}
	}
	return sidePanel;
}

// Create and return the game window widget with all its children according to the givenl gameModel.
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
	window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_CAPTION, bgColor);
	
	topPanel = createPanel(TOP_PANEL_POSX, TOP_PANEL_POSY, TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT, bgColor);
	addWidget(window, topPanel);
	
	gameOverLabel = createLabel(0, GAME_OVER_LABEL_POSY, GAME_OVER_LABEL_WIDTH, GAME_OVER_LABEL_HEIGHT);
	setBgColor(gameOverLabel, bgColor);
	setVisible(gameOverLabel, 0);
	addWidget(topPanel, gameOverLabel);
	
	gameStatusLabel = createLabel(0, GAME_STATUS_LABEL_POSY, GAME_STATUS_LABEL_WIDTH, GAME_STATUS_LABEL_HEIGHT);
	setBgColor(gameStatusLabel, bgColor);
	addWidget(topPanel, gameStatusLabel);
	
	turnStatusLabel = createLabel(0, TURN_STATUS_LABEL_POSY, TURN_STATUS_LABEL_WIDTH, TURN_STATUS_LABEL_HEIGHT);
	setBgColor(turnStatusLabel, bgColor);
	addWidget(topPanel, turnStatusLabel);
	
	pauseButton = createButton(BUTTON_PAUSE, PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, colorKey,
		 	NULL, 0, 0, NULL, NULL);
	addWidget(topPanel, pauseButton);
	
	// Create the side panel
	sidePanel = createSidePanel(window);
	if (sidePanel == NULL) {
		freeWidget(window);
		return NULL;
	}
	
	// Create the grid panel
	gridPanel = createGridPanel(window, gameModel);
	if (gridPanel == NULL) {
		freeWidget(window);
		return NULL;
	}
	return window;
}

// Return 1 if the current player is human, 0 if it is a machine.
int isCurrentPlayerHuman(GameModel *gameModel) {
	return (gameModel->isMouseTurn && gameModel->gameConfig->isMouseHuman) || (!gameModel->isMouseTurn && gameModel->gameConfig->isCatHuman);
}

/* Creates the game model which is simply the game. If a game is not null and a configuration was given, update the game's configuration.
// Returns the game model, or NULL if some error occured. */
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

// Update the game status label according to the game model
void updateGameStatusLabel(GameModel *gameModel, Widget *gameStatusLabel) {
	char gameStatusText[GAME_STATUS_TEXT_MAX_LENGTH];
	if (gameModel->isMouseTurn) {
		sprintf(gameStatusText, GAME_STATUS_MOUSE_MOVE, gameModel->numTurns);
		setPosX(gameStatusLabel, GAME_STATUS_MOUSE_LABEL_POSX);
	} else {
		sprintf(gameStatusText, GAME_STATUS_CAT_MOVE, gameModel->numTurns);
		setPosX(gameStatusLabel, GAME_STATUS_CAT_LABEL_POSX);
	}
	setText(gameStatusLabel, gameStatusText, GAME_STATUS_TEXT_POSX, GAME_STATUS_TEXT_POSY);
}

// Update the turn status label according to the game model
void updateTurnStatusLabel(GameModel *gameModel, Widget *turnStatusLabel) {
	const char *turnStatusText;
	if (!gameModel->isPaused) {
		if (isCurrentPlayerHuman(gameModel)) {
			turnStatusText = TURN_STATUS_TEXT_HUMAN_WAITING;
			setPosX(turnStatusLabel, TURN_STATUS_HUMAN_POSX);
		} else {
			turnStatusText = TURN_STATUS_TEXT_MACHINE_COMPUTING;
			setPosX(turnStatusLabel, TURN_STATUS_MACHINE_POSX);
		}
	} else {
		if (isCurrentPlayerHuman(gameModel)) {
			turnStatusText = TURN_STATUS_TEXT_HUMAN_PAUSED;
			setPosX(turnStatusLabel, TURN_STATUS_HUMAN_PAUSED_PAUSED_POSX);
		} else {
			turnStatusText = TURN_STATUS_TEXT_MACHINE_PAUSED;
			setPosX(turnStatusLabel, TURN_STATUS_MACHINE_PAUSED_POSX);
		}
	}
	setText(turnStatusLabel, turnStatusText, TURN_STATUS_TEXT_POSX, TURN_STATUS_TEXT_POSY);
}

// Update the game over label according to the game model
void updateGameOverLabel(GameModel *gameModel, Widget *gameOverLabel) {
	const char *gameOverText;
	
	switch (gameModel->winType) {
		case CAT_WINS:
			gameOverText = GAME_OVER_MESSAGE_CAT;
			setPosX(gameOverLabel, GAME_OVER_CAT_LABEL_POSX);
			break;
		case MOUSE_WINS:
			gameOverText = GAME_OVER_MESSAGE_MOUSE;
			setPosX(gameOverLabel, GAME_OVER_MOUSE_LABEL_POSX);
			break;
		case DRAW:
			gameOverText = GAME_OVER_MESSAGE_TIMEOUT;
			setPosX(gameOverLabel, GAME_OVER_TIMEOUT_LABEL_POSX);
			break;
		default: 
			gameOverText = NULL;
			break;
	}
	
	setText(gameOverLabel, gameOverText, GAME_OVER_TEXT_POSX, GAME_OVER_TEXT_POSY);
}

// Set the new images for the pause button. Returns 0 on success, 1 otherwise. 
int setPauseButtonImages(Widget *pauseButton, const char* imageName, const char *markedImageName) {
	if (setImage(pauseButton, imageName) != 0) {
		return 1;
	}
	if (setMarkedImage(pauseButton, markedImageName) != 0) {
		return 1;
	}
	return 0;
}

// Updates the pause button images according to the game model. Returns 0 on success, 1 otherwise. 
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

// Updates the top panel according to the game model. Returns 0 on success, 1 otherwise. 
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
		updateGameOverLabel(gameModel, gameOverLabel);
	}
	return 0;
}

// Update side panel buttons according to the game model.
void updateSidePanel(Widget *sidePanel, GameModel *gameModel) {
	Widget *sideButton;
	int i;
	for (i = 0; i < SIDE_BUTTONS_NUM; i++) {
		sideButton = getChildAtindex(sidePanel, i);
		setEnabled(sideButton, gameModel->isPaused || gameModel->isGameOver);
	}
}

// Update the view after a change in the game status. Returns 0 on success, 1 otherwise. 
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

// Handles a machine turn if the current player is a machine. Uses the GameLogicService.
void handleMachineTurn(GameModel *gameModel, Widget *window) {
	handleMachineMove(gameModel);
	SDL_Delay(DELAY_AFTER_MACHINE_CALC_MILLIS);
	updateView(window, gameModel);
}

// Starts the game play - creating the model and view - see header for doc.
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
	isError = updateView(window, gameModel);
}

// Translating SDL events to logical events - see header for doc.
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

// Handle button selected events for the game play window according to the given buttonId. Returns the next state ID.
StateId handleButtonSelectedGamePlay(void* model, Widget *window, int buttonId) {
	GameModel *gameModel = (GameModel *) model;	
	if (!gameModel->isGameOver && !gameModel->isPaused && buttonId != BUTTON_PAUSE) {
		return GAME_PLAY; // Ignore side buttons when not paused
	}
	switch (buttonId) {
		case BUTTON_PAUSE:
			gameModel->isPaused = !gameModel->isPaused;			
			if (updateView(window, gameModel) != 0) {
				isError = 1;
				return GAME_PLAY;
			}
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
			if (updateView(window, gameModel) != 0) {
				isError = 1;
				return GAME_PLAY;
			}
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

// Handle a move of a player and updates the view. Returns 0 on success, 1 otherwise.
int handleMove(GameModel *gameModel, Widget *window, MoveDirection moveDirection) {
	if (gameModel->isMouseTurn) {
		makeMouseMove(gameModel, moveDirection);
		if (updateView(window, gameModel) != 0) {
			return 1;
		}
	} else {
		makeCatMove(gameModel, moveDirection);
		if (updateView(window, gameModel) != 0) {
			return 1;
		}
	}
	return 0;
}

// Returns the move direction to which the point has moved in the moveDirection given. Returns 1 if a move should be made (if the points are adjacent, 0 otherwise).
int getMoveDirectionFromCurrentPlayerPoint(GameModel *gameModel, BoardPoint newPoint, MoveDirection *moveDirection) {
	BoardPoint oldPoint;
	if (gameModel->isMouseTurn) {
		oldPoint = gameModel->mousePoint;
	} else {
		oldPoint = gameModel->catPoint;
	}
	return getMoveDirectionFromPoint(oldPoint, newPoint, moveDirection);
}

// Handles logical events - see header for doc.
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
		if (handleMove(gameModel, window, moveDirection) != 0) {
			isError = 1;
		}
	}
	
	freeLogicalEvent(logicalEvent);
	return result;
}

// When moving to a selection window we want the BACK buttons to work correctly, so we simulate the previous states as if they were a selection window states.
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

// Stops the game play - freeing the resources -  see header for doc.
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
