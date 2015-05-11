#ifndef SELECTION_WINDOW_H_
#define SELECTION_WINDOW_H_

/* This is the general selection window, which holds the common logic, view and model for all the selection windows. */

#include <SDL.h>
#include "GUIState.h"
#include "../model/GameConfigModel.h"
#include "../model/GameModel.h"
#include "../gui/Widget.h"


// Main Panel
#define MAIN_PANEL_WIDTH 400
#define MAIN_PANEL_HEIGHT 720
#define MAIN_PANEL_POSX 200
#define MAIN_PANEL_POSY 40
#define MAIN_PANEL_INDEX_IN_WINDOW 0

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

/* The selection model, which holds the data for every selection window, together with a pointer to the previous window.  */
typedef struct selection_model {
	StateId stateId; // The state ID
	GameConfigurationModel *gameConfig; // The game configuration model
	int markedButtonIndex; // The current marked button index.
	GameModel *game; // The saved game state, in case we arrived to the window in the middle of a game.
	struct selection_model *previousStateModel; // The previous state and data.
} SelectionModel;

/* Creates a new selection model using the previous state, configuration and game, all of those can be null.
 	 Returns the created SelecionModel struct or NULL if some error occured. */
SelectionModel *createSelectionModel(StateId stateId, SelectionModel *previousStateModel, GameConfigurationModel *previousConfig, GameModel *game);

/* Creates a new selection model using the initData received from a previous state and the current state id. 
	If initData is NULL, create an empty selection model with defaults.
	If not, the initData must be a SelectionModel struct, passed from another state. 
	Two options are possible:
	 	- if the current stateId mathces the stateId in the model: it means we got back to this window using a back button - return the given model.
		- if it's not, create and return a new model based on the previous one.
	Returns the created SelecionModel struct or NULL if some error occured. */
SelectionModel *createSelectionModelByState(StateId stateId, void *initData);

/* Free the selection model. Receives two flags: freePrevious - to free also all previous models, shouldFreeGame - to free the game that the game spointer points to */
void freeSelectionModel(SelectionModel *selectionModel, int freePrevious, int shouldFreeGame);

/* A common utility function to all selection windows - unmark the button indicated by markButtonPtr and mark the newButtonToMark.
  Assumes that the window's children are those created by createSelectionWindowView (see below) */
void markButton(Widget *window, int *markButtonPtr, int newButtonToMark);

/* A common SDL event to logical event translation function for all selection windows, translates the given SDL event to a logical event,
 according to the view. If a button was clicked or marked (using TAB key), it searches for the right button in the UITree and returns the right logical event. */
void* viewTranslateEventSelectionWindow(void* viewState, SDL_Event* event);

/* A common handler for logical events for all selection windows. It receives the model and view (window), the logical event to handle, the current marked button pointer,
   a button handler function to activate specific window logic for each of the buttons, the state ID to return for staying in the same state and the number of buttons in the view.
	Returns the next state ID to move to, could be the sameStateId. */
StateId presenterHandleEventSelectionWindow(void* model, Widget *window, void* logicalEvent, int *markButtonPtr, 
StateId (*handleButtonSelected)(void *model, Widget *window, int buttonId), StateId sameStateId, int buttonsNumber);

/* A commond handler for stopping the selection window, freeing all the resources and pssing the init data for the next state. */
void* stopSelectionWindow(GUIState* state, StateId nextStateId);

/* Creates the selection window view: a window widget with a main panel, a logo and a title label, a buttons panel and buttons.
    Paramerers: The title text, the text position (x,y), the number of buttons to create, the unmarked and marked images list for the buttons.
	Returns the created view or NULL if some error occured. */
Widget* createSelectionWindowView(char *titleText, int textPosx, int textPosY, int buttonsNumber, const char *buttonImages[], const char *buttonMarkedImages[]);

/* Creates a single button using the all the buttons parameters, relevant for selection windows. */
Widget* createSelectionButton(Widget *parent, int buttonId, int posX, int posY, int width, int height,
	 	const char* buttonImage, const char* buttonMarkedImage);
		
/* Creates an up and down arrows on the given button with ID buttonId, used for WorldSelection and ChooseSkill windows. */
int addUpDownArrows(Widget *window, int buttonId, int buttonUpId, int buttonDownId);		

#endif /* SELECTION_WINDOW_H_ */
