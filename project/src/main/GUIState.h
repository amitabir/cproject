#ifndef GUI_STATE_H_
#define GUI_STATE_H_

#include <SDL.h>

typedef enum {
	MAIN_MENU,
	CAT_CHOOSE,
	CAT_CHOOSE_SKILL,
	MOUSE_CHOOSE,
	MOUSE_CHOOSE_SKILL,
	GAME_PLAY,
	LOAD_GAME, 
	GAME_EDITOR,
	EDIT_GAME,
	SAVE_GAME,
	ERROR,
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
	void* (*stop) (struct GUI* gui, StateId nextStateId);
} GUIState;


#endif /* GUI_STATE_H_ */
