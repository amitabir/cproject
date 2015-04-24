#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "WorldFilesService.h"
#include "Constants.h"
#include "BoardUtils.h"

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
	return worldData;
}

void freeWorldFileData(WorldFileData *worldData) {
	if (worldData->board != NULL) {
		freeBoard(worldData->board);
	}
	free(worldData);
}

void getWorldFileName(int worldIndex, char *fileName) {
	sprintf(fileName, "%s/%s%d%s", WORLD_FILE_DIR, WORLD_FILE_PREFIX, worldIndex, WORLD_FILE_ENDING);
}

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
	if (fclose(fp) && errorType != CLOSE_ERROR) {
		perror("ERROR: Could not close the file after error");
	}
}

int writeWorldToFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	const char *startPlayer = NULL;
	int i,j;
	
	char fileName[FILE_NAME_LENGTH];
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "w");
	if (!fp) {
		handleFileError(fp, OPEN_ERROR, worldIndex);
		return 0;
	}

	if (fprintf(fp, "%d\n", worldData->numTurns) < 0) {
		handleFileError(fp, WRITE_ERROR, worldIndex);
		return 0;
	}

	worldData->isMouseStarts ? (startPlayer = MOUSE_STARTS_STR) : (startPlayer = CAT_STARTS_STR);
	if (fprintf(fp, "%s\n", startPlayer) < 0) {
		handleFileError(fp, WRITE_ERROR, worldIndex);
		return 0;
	}

	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			if (fprintf(fp, "%c", worldData->board[i][j]) < 0) {
				handleFileError(fp, WRITE_ERROR, worldIndex);
				return 0;
			}
		}
		if (fprintf(fp, "\n") < 0) {
			handleFileError(fp, WRITE_ERROR, worldIndex);
			return 0;
		}
	}

	if (fclose(fp)) {
		handleFileError(fp, CLOSE_ERROR, worldIndex);
		return 0;
	}
	return 1;
}

int parseWorldFile(FILE *fp, int worldIndex, WorldFileData *worldData) {
	char startPlayer[6];
	char numTurnsStr[4];
	char currentBoardChar;
	int isMouseStarts;
	int i,j;
	
	if (fscanf(fp, "%s\n", numTurnsStr) < 1) {
		handleFileError(fp, READ_ERROR, worldIndex);
		return 0;
	}
	
	if (numTurnsStr[0] == 'q') {
		return 0;
	} else {		
		sscanf(numTurnsStr, "%d\n", &(worldData->numTurns));
	}
	
	if (fscanf(fp, "%s\n", startPlayer) < 1) {
		handleFileError(fp, READ_ERROR, worldIndex);
		return 0;
	}	

	strcmp(startPlayer, CAT_STARTS_STR) == 0 ? (isMouseStarts = 0) : (isMouseStarts = 1);
	worldData->isMouseStarts = isMouseStarts;
	
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			currentBoardChar = fgetc(fp);
			worldData->board[i][j] = currentBoardChar;
		}
		currentBoardChar = fgetc(fp);
	}
	
	return 1;
}

int readWorldFromFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	char fileName[FILE_NAME_LENGTH];
	
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "r");
	if (!fp) {
		handleFileError(fp, OPEN_ERROR, worldIndex);
		return 0;
	}
	
	if (!parseWorldFile(fp, worldIndex, worldData)) {
		return 0;
	}

	if (fclose(fp)) {
		handleFileError(fp, CLOSE_ERROR, worldIndex);
		return 0;
	}
	
	return 1;
}
	

