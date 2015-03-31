#include "GUIStatesFactory.h"
#include "MainMenu.h"
#include "CatChoose.h"
#include "CatChooseSkill.h"
#include "GamePlay.h"
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
		case CAT_CHOOSE:
		case MOUSE_CHOOSE:
			guiState.start = startCatChoose;
			guiState.viewTranslateEvent = viewTranslateEventCatChoose;
			guiState.presenterHandleEvent = presenterHandleEventCatChoose;
			guiState.stop = stopCatChoose;
			break;
		case CAT_CHOOSE_SKILL:
		case MOUSE_CHOOSE_SKILL:
			guiState.start = startCatChooseSkill;
			guiState.viewTranslateEvent = viewTranslateEventCatChooseSkill;
			guiState.presenterHandleEvent = presenterHandleEventCatChooseSkill;
			guiState.stop = stopCatChooseSkill;
			break;
		case GAME_PLAY:
			guiState.start = startGamePlay;
			guiState.viewTranslateEvent = viewTranslateEventGamePlay;
			guiState.presenterHandleEvent = presenterHandleEventGamePlay;
			guiState.stop = stopGamePlay;
			break;
		default:
			break;
	}
	return guiState;
}
