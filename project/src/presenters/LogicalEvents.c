#include <stdlib.h>
#include <stdio.h>
#include "LogicalEvents.h"

// Create logical event with type only - see header for doc.
LogicalEvent *createLogicalEvent(LogicalEventType type) {
	return createLogicalEventWithParams(type, NULL);
}

// Create logical event with parameters - see header for doc.
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

// Create logical event with buttonId as a parameter - see header for doc.
LogicalEvent *createSelectedButtonEventForId(LogicalEventType type, int buttonId) {
	int *clickedIndexPtr;
	if ((clickedIndexPtr = (int *)malloc(sizeof(int))) == NULL) {
		perror("ERROR: Standard function malloc has failed");
		return NULL;
	}
	*clickedIndexPtr = buttonId;
	return createLogicalEventWithParams(type, clickedIndexPtr);
}

// Frees the logical event - see header for doc.
void freeLogicalEvent(LogicalEvent *logicalEvent) {
	if (logicalEvent->eventParams != NULL) {
		free(logicalEvent->eventParams);
	}
	free(logicalEvent);
}
