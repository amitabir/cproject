#ifndef GENERAL_GAME_WINDOW_H_
#define GENERAL_GAME_WINDOW_H_

#include <SDL.h>
#include "GUIState.h"
#include "GUI/Widget.h"
#include "Model/GameConfigModel.h"
#include "Model/GameModel.h"
#include "LogicalEvents.h"

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

#define BUTTON_GRID 99
#define GRID_WIDTH 600
#define GRID_HEIGHT 650
#define GRID_X_POS 200
#define GRID_Y_POS 150
#define GRID_CELL_WIDTH GRID_WIDTH / BOARD_ROWS
#define GRID_CELL_HEIGHT GRID_HEIGHT / BOARD_COLS

extern const char *WALL_IMAGE;
extern const char *CAT_IMAGE;
extern const char *MOUSE_IMAGE;
extern const char *CHEESE_IMAGE;
extern const char *GRID_IMAGE;

LogicalEvent *getSelectedButtonEventForId(int buttonId);
LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos);
LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection moveDirection);
int placeWalls(Widget *gridButton, GameModel *gameModel);
void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad);
Widget* createGridPanel(Widget *parent, GameModel *gameModel);

#endif /* GENERAL_GAME_WINDOW_H_ */
