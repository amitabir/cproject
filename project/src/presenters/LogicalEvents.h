#ifndef LOGICAL_EVENTS_H_
#define LOGICAL_EVENTS_H_

/* The logical events representing events in the application */

// The event types
typedef enum {
	// When quit is pressed, either by QUIT buttons or using the 'x' button in the cornder
	QUIT_PRESSED, 
	// A special event sent when there is no SDL event at all. Used for advancing machines games.
	NO_EVENT, 
	// Irrlevant event - describing a click on unclickable widget, or some other SDL event which is irrelevant.
	IRRELEVANT_EVENT, 
	// Mark the next button in selection windows
	MARK_NEXT_BUTTON, 
	// Select the currently marked button in selection windows
	SELECT_MARKED_BUTTON,
	// Mark and select (on click) the currently marked button in selection windows
	MARK_AND_SELECT_BUTTON,
	UP_PRESSED, 
	DOWN_PRESSED, 
	// Select some button in non-selection windows
	SELECT_BUTTON,
	// Move an item on the grid to a different point
	MOVE_POINT,
	// Move an item on the grid in a specific direction (arrow keys)
	MOVE_DIRECTION
} LogicalEventType;

// The struct representing the logical event.
typedef struct logical_event {
	LogicalEventType type; // The event type
	void *eventParams; // The event parameters
} LogicalEvent;

/* Creates a new logical event using its type and without parameters
    Returns the created logical event or NULL if some error occured. */
LogicalEvent *createLogicalEvent(LogicalEventType type);

/* Creates a new logical event using its type and parameters
    Returns the created logical event or NULL if some error occured. */
LogicalEvent *createLogicalEventWithParams(LogicalEventType type, void *eventParams);

/* A utility method that creates a new logical event of the given type with button ID as a parameter.
    Returns the created logical event or NULL if some error occured. */
LogicalEvent *createSelectedButtonEventForId(LogicalEventType type, int buttonId);

/* Frees the logical events and its parameters if needed */
void freeLogicalEvent(LogicalEvent *logicalEvent);

#endif /* LOGICAL_EVENTS_H_ */

