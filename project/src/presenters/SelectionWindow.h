#ifndef SELECTION_WINDOW_H_
#define SELECTION_WINDOW_H_

#include <SDL.h>
#include "GUIState.h"
#include "../gui/Widget.h"
#include "../model//GameConfigModel.h"
#include "../model/GameModel.h"
#include "../gui/WidgetFactory.h"

// Main Panel
#define MAIN_PANEL_WIDTH 400
#define MAIN_PANEL_HEIGHT 720
#define MAIN_PANEL_POSX 200
#define MAIN_PANEL_POSY 40

// Logo Label
#define LOGO_LABEL_WIDTH 211
#define LOGO_LABEL_HEIGHT 149
#define LOGO_LABEL_POSX (MAIN_PANEL_WIDTH - LOGO_LABEL_WIDTH) / 2
#define LOGO_LABEL_POSY 0

// Title Label
#define TITLE_LABEL_WIDTH 300
#define TITLE_LABEL_HEIGHT 50
#define TITLE_LABEL_POSX (MAIN_PANEL_WIDTH - TITLE_LABEL_WIDTH) / 2
#define TITLE_LABEL_POSY LOGO_LABEL_HEIGHT + 20
#define PADDING_AFTER_TITLE 20

// Buttons Panel
#define BUTTONS_PANEL_WIDTH MAIN_PANEL_WIDTH
#define BUTTONS_PANEL_HEIGHT MAIN_PANEL_HEIGHT - LOGO_LABEL_HEIGHT - 50
#define BUTTONS_PANEL_POSX 0
#define BUTTONS_PANEL_POSY LOGO_LABEL_HEIGHT + 10

// Buttons
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_POSX (BUTTONS_PANEL_WIDTH - BUTTON_WIDTH) / 2
#define BASE_BUTTON_POSY 100

// Up arrow button
#define BUTTON_UP_WIDTH 25
#define BUTTON_UP_HEIGHT 25
#define BUTTON_UP_POSX BUTTON_WIDTH - BUTTON_UP_WIDTH
#define BUTTON_UP_POSY 0 

// Down arrow button
#define BUTTON_DOWN_WIDTH 25
#define BUTTON_DOWN_HEIGHT 25
#define BUTTON_DOWN_POSX BUTTON_WIDTH - BUTTON_DOWN_WIDTH
#define BUTTON_DOWN_POSY BUTTON_UP_HEIGHT


typedef struct selection_model {
	StateId stateId;
	GameConfigurationModel *gameConfig;
	int markedButtonIndex;
	GameModel *game;
	struct selection_model *previousStateModel;
} SelectionModel;

SelectionModel *createSelectionModel(StateId stateId, SelectionModel *previousStateModel, GameConfigurationModel *previousConfig, GameModel *game);
SelectionModel *createSelectionModelByState(StateId stateId, void *initData);
void freeSelectionModel(SelectionModel *selectionModel, int freePrevious, int shouldFreeGame);
void markButton(Widget *window, int *markButtonPtr, int newButtonToMark);
void* viewTranslateEventSelectionWindow(void* viewState, SDL_Event* event);
StateId presenterHandleEventSelectionWindow(void* model, Widget *window, void* logicalEvent, int *markButtonPtr, 
StateId (*handleButtonSelected)(void *model, Widget *window, int buttonId), StateId sameStateId, int buttonsNumber);
void* stopSelectionWindow(GUIState* state, StateId nextStateId);
Widget* createSelectionWindowView(char *titleText, int textPosx, int textPosY, int buttonsNumber, const char *buttonImages[], const char *buttonMarkedImages[]);
Widget* createSelectionButton(Widget *parent, int buttonId, int posX, int posY, int width, int height,
	 	const char* buttonImage, const char* buttonMarkedImage);
int addUpDownArrows(Widget *window, int buttonId, int buttonUpId, int buttonDownId);		

#endif /* SELECTION_WINDOW_H_ */
