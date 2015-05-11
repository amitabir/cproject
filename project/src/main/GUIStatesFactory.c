#include "GUIStatesFactory.h"
#include "../presenters/MainMenu.h"
#include "../presenters/WorldSelection.h"
#include "../presenters/ChooseType.h"
#include "../presenters/ChooseSkill.h"
#include "../presenters/GamePlay.h"
#include "../presenters/GameEditor.h"
#include "../presenters/Error.h"
#include "../presenters/SelectionWindow.h"

// Creates the GUIState struct for each stateId.
GUIState createGUIForState(StateId stateId) {
	GUIState guiState;
	guiState.stateId = stateId;
	switch(stateId) {
		case MAIN_MENU:
			guiState.start = startMainMenu;
			guiState.viewTranslateEvent = viewTranslateEventSelectionWindow;
			guiState.presenterHandleEvent = presenterHandleEventMainMenu;
			guiState.stop = stopMainMenu;
			break;
		case LOAD_GAME:
		case EDIT_GAME:
		case SAVE_GAME:
			guiState.start = startWorldSelection;
			guiState.viewTranslateEvent = viewTranslateEventSelectionWindow;
			guiState.presenterHandleEvent = presenterHandleEventWorldSelection;
			guiState.stop = stopWorldSelection;
			break;
		case CAT_CHOOSE:
		case MOUSE_CHOOSE:
			guiState.start = startChooseType;
			guiState.viewTranslateEvent = viewTranslateEventSelectionWindow;
			guiState.presenterHandleEvent = presenterHandleEventChooseType;
			guiState.stop = stopSelectionWindow;
			break;
		case CAT_CHOOSE_SKILL:
		case MOUSE_CHOOSE_SKILL:
			guiState.start = startChooseSkill;
			guiState.viewTranslateEvent = viewTranslateEventSelectionWindow;
			guiState.presenterHandleEvent = presenterHandleEventChooseSkill;
			guiState.stop = stopSelectionWindow;
			break;
		case GAME_PLAY:
			guiState.start = startGamePlay;
			guiState.viewTranslateEvent = viewTranslateEventGamePlay;
			guiState.presenterHandleEvent = presenterHandleEventGamePlay;
			guiState.stop = stopGamePlay;
			break;
		case GAME_EDITOR:
			guiState.start = startEditGame;
			guiState.viewTranslateEvent = viewTranslateEventEditGame;
			guiState.presenterHandleEvent = presenterHandleEventEditGame;
			guiState.stop = stopEditGame;
			break;
		case ERROR:
			guiState.start = startError;
			guiState.viewTranslateEvent = viewTranslateEventSelectionWindow;
			guiState.presenterHandleEvent = presenterHandleEventError;
			guiState.stop = stopError;
			break;
		default:
			break;
	}
	return guiState;
}
