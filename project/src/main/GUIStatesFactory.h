#ifndef GUI_STATE_FACTORY_H_
#define GUI_STATE_FACTORY_H_

/* This is the GUI states factory, for every StateId it creates the appropriate GUIState. */

#include "../presenters/GUIState.h"

/* Returns for each stateId the corresponding GUIState struct with all the method pointers initialized */
GUIState createGUIForState(StateId stateId);

#endif /* GUI_STATE_FACTORY_H_ */
