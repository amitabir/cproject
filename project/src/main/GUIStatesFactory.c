#include "GUIStatesFactory.h"
#include "MainMenu.h"
#include "LoadGame.h"
#include "ChooseType.h"
#include "ChooseSkill.h"
#include "GamePlay.h"
#include "EditGame.h"
#include "Error.h"
#include "GUIState.h"

GUIState createGUIForState(StateId stateId) {
	GUIState guiState;
	guiState.stateId = stateId;
	switch(stateId) {
		case MAIN_MENU:
			guiState.start = startMainMenu;
			guiState.viewTranslateEvent = viewTranslateEventMainMenu;
			guiState.presenterHandleEvent = presenterHandleEventMainMenu;
			guiState.stop = stopMainMenu;
			break;
		case LOAD_GAME:
		case EDIT_GAME:
		case SAVE_GAME:
			guiState.start = startLoadGame;
			guiState.viewTranslateEvent = viewTranslateEventLoadGame;
			guiState.presenterHandleEvent = presenterHandleEventLoadGame;
			guiState.stop = stopLoadGame;
			break;
		case CAT_CHOOSE:
		case MOUSE_CHOOSE:
			guiState.start = startChooseType;
			guiState.viewTranslateEvent = viewTranslateEventChooseType;
			guiState.presenterHandleEvent = presenterHandleEventChooseType;
			guiState.stop = stopChooseType;
			break;
		case CAT_CHOOSE_SKILL:
		case MOUSE_CHOOSE_SKILL:
			guiState.start = startChooseSkill;
			guiState.viewTranslateEvent = viewTranslateEventChooseSkill;
			guiState.presenterHandleEvent = presenterHandleEventChooseSkill;
			guiState.stop = stopChooseSkill;
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
			guiState.viewTranslateEvent = viewTranslateEventError;
			guiState.presenterHandleEvent = presenterHandleEventError;
			guiState.stop = stopError;
			break;
		default:
			break;
	}
	return guiState;
}
