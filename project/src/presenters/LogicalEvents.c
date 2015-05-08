#include <stdlib.h>
#include <stdio.h>
#include "LogicalEvents.h"

LogicalEvent *createLogicalEvent(LogicalEventType type) {
	return createLogicalEventWithParams(type, NULL);
}

LogicalEvent *createLogicalEventWithParams(LogicalEventType type, void *eventParams) {
	LogicalEvent *result;
	if ((result = (LogicalEvent *) malloc(sizeof(LogicalEvent))) == NULL) {
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	result->type = type;
	result->eventParams = eventParams;
	return result;
}

LogicalEvent *createSelectedButtonEventForId(LogicalEventType type, int buttonId) {
	int *clickedIndexPtr;
	if ((clickedIndexPtr = (int *)malloc(sizeof(int))) == NULL) {
		perror("ERROR: Standard function malloc has failed");
		return NULL;
	}
	*clickedIndexPtr = buttonId;
	return createLogicalEventWithParams(type, clickedIndexPtr);
}

void freeLogicalEvent(LogicalEvent *logicalEvent) {
	if (logicalEvent->eventParams != NULL) {
		free(logicalEvent->eventParams);
	}
	free(logicalEvent);
}
