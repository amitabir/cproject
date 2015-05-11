#include "GeneralGameWindow.h"
#include "../gui/Widget.h"
#include "../gui/WidgetFactory.h"

// Default positions for labels before they are put in their correct place on the grid
#define DEFAULT_POSX 0
#define DEFAULT_POSY 0

#define GRID_BUTTON_X_POS 0
#define GRID_BUTTON_Y_POS 0

#define GRID_LABEL_X_PADDING 3 
#define GRID_LABEL_Y_PADDING 4


// Images for grid
const char *WALL_IMAGE = "images/wall.bmp";
const char *CAT_IMAGE = "images/cat.bmp";
const char *MOUSE_IMAGE = "images/mouse.bmp";
const char *CHEESE_IMAGE = "images/cheese.bmp";
const char *GRID_IMAGE = "images/grid.bmp";

// Returns a logical event with grid coordinates according to pixel coordinates on the grid - see header for doc. 
LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos) {
	BoardPoint *point;
	if ((point = (BoardPoint *) malloc(sizeof(BoardPoint))) == NULL) {
		perror("ERROR: Standard function malloc has failed");
		return NULL;
	}
	int cellH = GRID_CELL_HEIGHT, cellW = GRID_CELL_WIDTH;
	point->row = (yPos - GRID_Y_POS) / cellH;
	point->col = (xPos - GRID_X_POS) / cellW;
	return createLogicalEventWithParams(MOVE_POINT, point);
}

// Returns a logical event with grid coordinates according to pixel coordinates on the grid - see header for doc. 
LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection moveDirection) {
	MoveDirection *moveDirectionPtr;
	if ((moveDirectionPtr = (MoveDirection *) malloc(sizeof(MoveDirection))) == NULL) {
		perror("ERROR: Standard function malloc has failed");
		return NULL;
	}
	*moveDirectionPtr = moveDirection;
	return createLogicalEventWithParams(MOVE_DIRECTION, moveDirectionPtr);
}

// Places walls on the grid according to the game model - see header for doc.
int placeWalls(Widget *gridButton, GameModel *gameModel) {
	int i,j;
	Widget *wallLabel;
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			if (gameModel->board[i][j] == WALL_TILE) {
				wallLabel = createLabel(0, 0, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
				BoardPoint wallPoint;
				wallPoint.row = i;
				wallPoint.col = j;
				setGridLabelCoordinates(wallLabel, wallPoint, 1);
				if (setImage(wallLabel, WALL_IMAGE) != 0) {
					freeWidget(wallLabel);
					return 1;
				}
				addWidget(gridButton, wallLabel);
			} 
		}
	}
	return 0;
}

// Set the coordinates on the window for a grid label, according to its row and col - see header for doc.
void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad) {
	int paddingx = 0;
	int paddingy = 0;
	
	if (pad) {
		paddingx = GRID_LABEL_X_PADDING;
		paddingy = GRID_LABEL_Y_PADDING;
	}
	setPosX(label, point.col * GRID_CELL_WIDTH + paddingx);
	setPosY(label, point.row * GRID_CELL_HEIGHT + paddingy);
}

// Creates the grid panel - see header for doc.
Widget* createGridPanel(Widget *parent, GameModel *gameModel) {
	Widget *gridButton = NULL, *catLabel = NULL, *mouseLabel = NULL, *cheeseLabel = NULL;
	Color colorKey = createColor(0xFF, 0xFF, 0xFF);
	
	Widget *gridPanel = createPanel(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, colorKey);
	addWidget(parent, gridPanel);
	
	gridButton = createButton(BUTTON_GRID, GRID_BUTTON_X_POS, GRID_BUTTON_Y_POS, GRID_WIDTH, GRID_HEIGHT, colorKey, NULL, 0, 0, GRID_IMAGE, NULL);
	addWidget(gridPanel, gridButton);
	
	// If a game model was given, add a label for the mouse, cat, cheese and walls on the grid.
	if (gameModel != NULL) {
		catLabel = createLabel(DEFAULT_POSX, DEFAULT_POSY, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(catLabel, gameModel->catPoint, 1);
		if (setImage(catLabel, CAT_IMAGE) != 0) {
			freeWidget(gridPanel);
			return NULL;
		}
		addWidget(gridButton, catLabel);
	
		mouseLabel = createLabel(DEFAULT_POSX, DEFAULT_POSY, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(mouseLabel, gameModel->mousePoint, 1);
		if (setImage(mouseLabel, MOUSE_IMAGE) != 0) {
			freeWidget(gridPanel);
			return NULL;
		}
		addWidget(gridButton, mouseLabel);
	
		cheeseLabel = createLabel(DEFAULT_POSX, DEFAULT_POSY, GRID_CELL_WIDTH, GRID_CELL_HEIGHT);
		setGridLabelCoordinates(cheeseLabel, gameModel->cheesePoint, 1);
		if (setImage(cheeseLabel, CHEESE_IMAGE) != 0) {
			freeWidget(gridPanel);
			return NULL;
		}
		addWidget(gridButton, cheeseLabel);
	
		if (placeWalls(gridButton, gameModel) != 0) {
			freeWidget(gridPanel);
			return NULL;
		}
	}
	return gridPanel;
}
