#include <SDL.h>
#include <SDL_video.h>

#include "CatAndMouse.h"
#include "GUIState.h"
#include "GUIStatesFactory.h"


int isError = 0;

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "ERROR: unable to init SDL: %s\n", SDL_GetError());
            return 0;
    }
	return 1;
}

int main(int argc, char* args[]) {
	if (!init()) {
		exit(1);
	}

	// initialize GUI structs mapping by state ids:
	GUIState guiStates[STATES_COUNT];

	guiStates[MAIN_MENU] = createGUIForState(MAIN_MENU);
	guiStates[CAT_CHOOSE] = createGUIForState(CAT_CHOOSE);
	guiStates[CAT_CHOOSE_SKILL] = createGUIForState(CAT_CHOOSE_SKILL);
	guiStates[MOUSE_CHOOSE] = createGUIForState(MOUSE_CHOOSE);
	guiStates[MOUSE_CHOOSE_SKILL] = createGUIForState(MOUSE_CHOOSE_SKILL);
	guiStates[GAME_PLAY] = createGUIForState(GAME_PLAY);
	
	

 	// Starting the default/initial GUI:
	StateId nextStateId = MAIN_MENU;

	GUIState activeGUI = guiStates[nextStateId];
	activeGUI.start(&activeGUI, NULL);

	while (!isError && nextStateId != QUIT) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {

			// translating the SDL event to a logical event using the view:
			void* logicalEvent = activeGUI.viewTranslateEvent(activeGUI.viewState, &event);
			
			// Handling the logical event using the presenter:
			nextStateId = activeGUI.presenterHandleEvent(activeGUI.model, activeGUI.viewState, logicalEvent);
			
			// if state has changed, stop the active GUI and move to the next one:
			if (activeGUI.stateId != nextStateId) {
				if (nextStateId == QUIT) {
					break;
				}
				else {
					void* nextGuiInitData = activeGUI.stop(&activeGUI, nextStateId);

					activeGUI = guiStates[nextStateId];
					activeGUI.start(&activeGUI, nextGuiInitData);
				}
			}
		}
		SDL_Delay(POLLING_DELAY);
	}

	//API may be extended with a "provideInitData" flag or something similar:
	activeGUI.stop(&activeGUI, nextStateId);
	
	SDL_Quit();
	
	return isError;
}
