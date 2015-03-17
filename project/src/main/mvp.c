#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

#define STATES_COUNT 2
#define POLLING_DELAY 10

// an enumeration of all the different states of the program.
// each state should correspond to a specific GUI.
// Should be moved to some header file.
typedef enum {
	MAIN_MENU,
	LOAD_GAME, 
	/*...*/
	QUIT
} StateId;

// The GUI structure.
typedef struct GUI {
	// The unique state id:
	StateId stateId;

	// The model and viewState. Assumed to be NULL until GUI is started and once it is stopped.
	// The model and view state should NOT hold references to each other.
	void *model, *viewState;

	// The function pointer for starting this GUI - initializing the model and viewState as well as drawing the initial state of the GUI.
	void (*start) (struct GUI* gui, void* initData);

	// The function pointer for translating the SDL_Event to a logical event according to the current viewState.
	// The logical event will be passed to the presenter which will take care of updating the model and/or the view.
	// The data type of the logical event is assumed to be know by the presenter and will also be freed by it, if need be.
	void* (*viewTranslateEvent) (void* viewState, SDL_Event* event);

	// The function pointer for handling the given logical event.
	// may or may not update the model and/or viewState.
	// Returns the next state to transition to.
	StateId (*presenterHandleEvent) (void* model, void* viewState, void* logicalEvent);

	// The function pointer for deactivating this GUI - freeing the model and viewState and any other resources used.
	// Returns the initialization data for the next state (can be NULL if not required).
	void* (*stop) (struct GUI* gui);
} GUI;

// Should be externalized in some header file.
int isError = 0;

// should be defined in some header file and implemented somewhere else.
// assumed not to allocate heap memory.
GUI createGUIForState(StateId stateId);

int main() {
	// initialize GUI structs mapping by state ids:
	GUI guis[STATES_COUNT];
	
	guis[MAIN_MENU] = createGUIForState(MAIN_MENU);
	guis[LOAD_GAME] = createGUIForState(LOAD_GAME);
	/*...*/

	// Starting the default/initial GUI:
	StateId nextStateId = MAIN_MENU;

	GUI activeGUI = guis[nextStateId];
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
					void* nextGuiInitData = activeGUI.stop(&activeGUI);

					activeGUI = guis[nextStateId];
					activeGUI.start(&activeGUI, nextGuiInitData);
				}
			}
		}
		SDL_Delay(POLLING_DELAY);
	}
	
	// API may be extended with a "provideInitData" flag or something similar:
	activeGUI.stop(&activeGUI);
	
	return isError;
}


