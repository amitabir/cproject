#ifndef GAME_PLAY_H_
#define GAME_PLAY_H_

#include <SDL.h>
#include "GUIState.h"

// TODO remove?
#include "LogicalEvents.h"

// TODO maybe move these
LogicalEvent *getSelectedButtonEventForId(int buttonId);
LogicalEvent *getMovePointLogicalEvent(Uint16 xPos, Uint16 yPos);
LogicalEvent *getMoveDirectionLogicalEvent(MoveDirection *moveDirection);
void placeWalls(Widget *gridButton, GameModel *gameModel);
void setGridLabelCoordinates(Widget *label, BoardPoint point, int pad);
Widget* createGridPanel(GameModel *gameModel);

void startGamePlay(GUIState* mainMenuState, void* initData);
void* viewTranslateEventGamePlay(void* viewState, SDL_Event* event);
StateId presenterHandleEventGamePlay(void* model, void* viewState, void* logicalEvent);
void* stopGamePlay(GUIState* gui, StateId nextStateId);

#endif /* GAME_PLAY_H_ */
