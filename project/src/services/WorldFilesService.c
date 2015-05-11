#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "WorldFilesService.h"
#include "../model/Constants.h"
#include "BoardUtils.h"

// Creates the world file data, see header for doc.
WorldFileData *createEmptyWorldFileData() {
	WorldFileData* worldData;
	if ((worldData = (WorldFileData*) malloc(sizeof(WorldFileData))) == NULL) {
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	worldData->board = createBoard();
	if (worldData->board == NULL) {
		free(worldData);
		return NULL;
	}
	worldData->numTurns = 0;
	worldData->isMouseStarts = 0;
	return worldData;
}

// Frees the world file data, see header for doc.
void freeWorldFileData(WorldFileData *worldData) {
	if (worldData->board != NULL) {
		freeBoard(worldData->board);
	}
	free(worldData);
}

// Returns in fileName the name of the world file with the given index worldIndex.
void getWorldFileName(int worldIndex, char *fileName) {
	sprintf(fileName, "%s/%s%d%s", WORLD_FILE_DIR, WORLD_FILE_PREFIX, worldIndex, WORLD_FILE_ENDING);
}

// Handles file error - read, write, open or close errors. Also tries to close the file for read/write errors.
void handleFileError(FILE *fp, FileErrorType errorType, int worldIndex) {
	char message[FILE_ERROR_MESSAGE_MAX_LENGTH];
	switch(errorType) {
		case READ_ERROR:
			sprintf(message, "ERROR: Could not read data from world file with index %d", worldIndex);
			break;
		case WRITE_ERROR:
			sprintf(message, "ERROR: Could not write data to world file with index %d", worldIndex);
			break;
		case OPEN_ERROR:
			sprintf(message, "ERROR: Could not open world file of index %d", worldIndex);
			break;
		case CLOSE_ERROR:
			sprintf(message, "ERROR: Could not close world file of index %d", worldIndex);
			break;
		default:
			// Not possible
			break;
	}
	perror(message);
	 
	// Try to close the file after error
	if (fclose(fp) && errorType != CLOSE_ERROR && errorType != OPEN_ERROR) {
		perror("ERROR: Could not close the file after error");
	}
}

// Writes the given worldData struct to the right world file according to the given index. 
int writeWorldToFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	const char *startPlayer = NULL;
	int i,j;
	
	char fileName[FILE_NAME_LENGTH];
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "w");
	if (!fp) {
		handleFileError(fp, OPEN_ERROR, worldIndex);
		return 1;
	}

	if (fprintf(fp, "%d\n", worldData->numTurns) < 0) {
		handleFileError(fp, WRITE_ERROR, worldIndex);
		return 1;
	}

	worldData->isMouseStarts ? (startPlayer = MOUSE_STARTS_STR) : (startPlayer = CAT_STARTS_STR);
	if (fprintf(fp, "%s\n", startPlayer) < 0) {
		handleFileError(fp, WRITE_ERROR, worldIndex);
		return 1;
	}

	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			if (fprintf(fp, "%c", worldData->board[i][j]) < 0) {
				handleFileError(fp, WRITE_ERROR, worldIndex);
				return 1;
			}
		}
		if (fprintf(fp, "\n") < 0) {
			handleFileError(fp, WRITE_ERROR, worldIndex);
			return 1;
		}
	}

	if (fclose(fp)) {
		handleFileError(fp, CLOSE_ERROR, worldIndex);
		return 1;
	}
	return 0;
}

// Parses the given file pointer to extract the world data - see header for doc.
int parseWorldFile(FILE *fp, int worldIndex, WorldFileData *worldData) {
	char startPlayer[6];
	char numTurnsStr[4];
	char currentBoardChar;
	int isMouseStarts;
	int i,j;
		
	// Parse the number of turns
	if (fscanf(fp, "%s", numTurnsStr) < 1) {
		handleFileError(fp, READ_ERROR, worldIndex);
		return 1;
	}
	
	// Can be 'q' in case it is used for console mode - if so, return.
	if (numTurnsStr[0] == 'q') {
		return 0;
	} else {		
		sscanf(numTurnsStr, "%d", &(worldData->numTurns));
	}
	
	// Parse the starting player
	if (fscanf(fp, "%s\n", startPlayer) < 1) {
		handleFileError(fp, READ_ERROR, worldIndex);
		return 1;
	}	

	strcmp(startPlayer, CAT_STARTS_STR) == 0 ? (isMouseStarts = 0) : (isMouseStarts = 1);
	worldData->isMouseStarts = isMouseStarts;
	
	// Parse the grid data
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			currentBoardChar = fgetc(fp);
			worldData->board[i][j] = currentBoardChar;
		}
		currentBoardChar = fgetc(fp);
	}
	
	return 0;
}

// Reads the world data from the world file given by the worldIndex, see header for doc.
int readWorldFromFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	char fileName[FILE_NAME_LENGTH];
	
	// Open the correct file according to the index
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "r");
	if (!fp) {
		handleFileError(fp, OPEN_ERROR, worldIndex);
		return 1;
	}
	
	// Parse the world file using the utility method.
	if (!parseWorldFile(fp, worldIndex, worldData)) {
		return 1;
	}
	
	// Close the file
	if (fclose(fp)) {
		handleFileError(fp, CLOSE_ERROR, worldIndex);
		return 1;
	}
	
	return 0;
}
	

