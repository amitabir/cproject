#include <stdlib.h>
#include "LogicalEvents.h"



LogicalEvent *createLogicalEvent(LogicalEventType type) {
	return createLogicalEventWithParams(type, NULL);
}

LogicalEvent *createLogicalEventWithParams(LogicalEventType type, void *eventParams) {
	LogicalEvent *result;
	result = (LogicalEvent *) malloc(sizeof(LogicalEvent));
	result->type = type;
	result->eventParams = eventParams;
	return result;
}
