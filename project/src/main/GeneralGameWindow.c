#include "GeneralGameWindow.h"
#include "GUI/Widget.h"
#include "GUI/WidgetFactory.h"

#define GRID_WIDTH 600
#define GRID_HEIGHT 650
#define GRID_X_POS 200
#define GRID_Y_POS 150
#define GRID_CELL_WIDTH GRID_WIDTH / BOARD_ROWS
#define GRID_CELL_HEIGHT GRID_HEIGHT / BOARD_COLS

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
	MoveDirection *moveDirectionPtr = (MoveDirection *) malloc(sizeof(MoveDirection));
	*moveDirectionPtr = moveDirection;
	return createLogicalEventWithParams(MOVE_DIRECTION, moveDirectionPtr);
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

void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad) {
	int padding = 0;
	if (pad) {
		padding = 5;
	}
	setPosX(label, point.col * GRID_CELL_WIDTH + padding);
	setPosY(label, point.row * GRID_CELL_HEIGHT + padding);
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
