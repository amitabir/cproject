#include <SDL.h>
#include <SDL_video.h>

#include "CatAndMouse.h"
#include "../presenters/GUIState.h"
#include "../presenters/LogicalEvents.h"
#include "GUIStatesFactory.h"
#include "ConsoleMode.h"

// A boolean int for error, externalized in GUIState.h and used to mark if an error occured in one of the windows mode.
int isError = 0;

/* This function initiates the SDL. */
int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "ERROR: unable to init SDL: %s\n", SDL_GetError());
            return 0;
    }
	return 1;
}

// Handles console mode. Returns 0 on success, 1 otherwise.
int handleConsoleMode(char *currentPlayer) {
	int isMousePlayer = 0;
	if (!strcmp(currentPlayer, "mouse")) {
		isMousePlayer = 1;
	}
	return runConsoleMode(isMousePlayer);
}

/* The main function. Runs the game while the user didn't exit and there are no errors */
int main(int argc, char* args[]) {
	if (argc > 3) {
		printf("Error: more than 2 parmeters have been passed to the program! Exiting.");
		exit(1);
	} else if (argc == 3 && strcmp(args[1], "console")) {
		return handleConsoleMode(args[2]);
	}
	
	// Init SDL
	if (!init()) {
		exit(1);
	}
	
	int shouldWait = 1;

	// initialize GUI structs mapping by state ids
	GUIState guiStates[STATES_COUNT];

	int stateId;
	for (stateId = 0; stateId < STATES_COUNT; stateId++) {
		guiStates[stateId] = createGUIForState(stateId);
	}

 	// Starting the default/initial GUI:
	StateId nextStateId = MAIN_MENU;

	GUIState activeGUI = guiStates[nextStateId];
	activeGUI.start(&activeGUI, NULL);
	


	// Main handling events loop
	while (!isError && nextStateId != QUIT) {
		SDL_Event event;
		void* logicalEvent;
		// translating the SDL event to a logical event using the view
		if (SDL_PollEvent(&event) != 0) {
			shouldWait = 0;
			logicalEvent = activeGUI.viewTranslateEvent(activeGUI.viewState, &event);
		} else {
			// If no event occured - pass NO_EVENT as the logical event.
			shouldWait = 1;
			logicalEvent = createLogicalEvent(NO_EVENT);
		}
			
		// Handling the logical event using the presenter
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
		
		SDL_Delay(POLLING_DELAY);
	}

	activeGUI.stop(&activeGUI, nextStateId);
	
	SDL_Quit();
	
	return isError;
}
