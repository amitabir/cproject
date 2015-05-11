#ifndef GENERAL_GAME_WINDOW_H_
#define GENERAL_GAME_WINDOW_H_

/* A common logic for the game play and the game editor. */

#include <SDL.h>
#include "GUIState.h"
#include "../gui/Widget.h"
#include "../model/GameConfigModel.h"
#include "../model/GameModel.h"
#include "../model/Constants.h"
#include "LogicalEvents.h"

// Top panel properties
#define TOP_PANEL_WIDTH 800
#define TOP_PANEL_HEIGHT 150
#define TOP_PANEL_POSX 0
#define TOP_PANEL_POSY 0

// Side panel properties
#define SIDE_PANEL_WIDTH 200
#define SIDE_PANEL_HEIGHT 650
#define SIDE_PANEL_POSX 0
#define SIDE_PANEL_POSY 150

// Side buttons properties
#define SIDE_BUTTON_WIDTH 150
#define SIDE_BUTTON_HEIGHT 60
#define SIDE_BUTTON_POSX 25
#define SIDE_BASE_BUTTON_POSY 50
#define SIDE_BASE_SPACING 120

// Grid properties
#define BUTTON_GRID 99
#define GRID_WIDTH 600
#define GRID_HEIGHT 650
#define GRID_X_POS 200
#define GRID_Y_POS 150
#define GRID_CELL_WIDTH GRID_WIDTH / BOARD_ROWS
#define GRID_CELL_HEIGHT GRID_HEIGHT / BOARD_COLS

// Images for the grid contents, used in both editor and game play.
extern const char *WALL_IMAGE;
extern const char *CAT_IMAGE;
extern const char *MOUSE_IMAGE;
extern const char *CHEESE_IMAGE;
extern const char *GRID_IMAGE;

/* This method recieves the coordinates of a pixel on the grid and returns the logical event with the grid cell coordinates (row, col). 
   The returned logical event will be of the type MOVE_POINT, may return NULL on error. */
LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos);

/* This method recieves the move direction and returns the logical event with the move direction to move in for further handling. 
   The returned logical event will be of the type MOVE_DIRECTION, may return NULL on error. */
LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection moveDirection);

/* Places wall lebels on the grid according to the game model board.
	 Returns 0 on success, 1 othetwise. */
int placeWalls(Widget *gridButton, GameModel *gameModel);

/* Places wall lebels on the grid according to the game model board.
	 Returns 0 on success, 1 othetwise. */
void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad);

/* Creates the grid panel, common for both the editor and the game play. the gameModel may be null.
    Returns the created grid panel, or NULL if some error occured. */
Widget* createGridPanel(Widget *parent, GameModel *gameModel);

#endif /* GENERAL_GAME_WINDOW_H_ */
