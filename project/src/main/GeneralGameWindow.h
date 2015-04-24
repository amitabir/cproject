#ifndef GENERAL_GAME_WINDOW_H_
#define GENERAL_GAME_WINDOW_H_

#include <SDL.h>
#include "GUIState.h"
#include "GUI/Widget.h"
#include "Model/GameConfigModel.h"
#include "Model/GameModel.h"
#include "LogicalEvents.h"


#define BUTTON_GRID 99

LogicalEvent *getSelectedButtonEventForId(int buttonId);
LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos);
LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection moveDirection);
void placeWalls(Widget *gridButton, GameModel *gameModel);
void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad);
Widget* createGridPanel(GameModel *gameModel);

#endif /* GENERAL_GAME_WINDOW_H_ */
