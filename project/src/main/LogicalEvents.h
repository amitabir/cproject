#ifndef LOGICAL_EVENTS_H_
#define LOGICAL_EVENTS_H_

typedef enum {
	QUIT_PRESSED,
	NO_EVENT,
	IRRELEVANT_EVENT,
	MARK_NEXT_BUTTON,
	SELECT_MARKED_BUTTON,
	MARK_AND_SELECT_BUTTON,
	SELECT_BUTTON,
	MOVE_POINT,
	MOVE_DIRECTION
} LogicalEventType;

typedef struct logical_event {
	LogicalEventType type;
	void *eventParams;
} LogicalEvent;

LogicalEvent *createLogicalEvent(LogicalEventType type);
LogicalEvent *createLogicalEventWithParams(LogicalEventType type, void *eventParams);
void freeLogicalEvent(LogicalEvent *logicalEvent);

#endif /* LOGICAL_EVENTS_H_ */

