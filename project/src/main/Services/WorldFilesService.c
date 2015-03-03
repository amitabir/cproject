#include "WorldFilesService.h"
#include "Constants.h"
#include <stdio.h>
#include <string.h> 

// Remove this
#include <stdlib.h>


// TODO handle errors

void getWorldFileName(int worldIndex, char *fileName) {
	// TODO : add directory
	sprintf(fileName, "%s%d%s", WORLD_FILE_PREFIX, worldIndex, WORLD_FILE_ENDING);
}

int writeWorldToFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	const char *startPlayer = NULL;
	char numTurnsStr[3];
	int i,j;
	
	char fileName[FILE_NAME_LENGTH];
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		return 0;
	}

	worldData->isMouseStarts ? (startPlayer = MOUSE_STARTS_STR) : (startPlayer = CAT_STARTS_STR);
	fprintf(fp, "%s\n", startPlayer);
	sprintf(numTurnsStr, "%d", worldData->numTurns);
	fprintf(fp, "%s\n", numTurnsStr);
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			fprintf(fp, "%c", worldData->board[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	return 1;
}

int readWorldFromFile(int worldIndex, WorldFileData *worldData) {
	FILE *fp = NULL;
	WorldFileData *result = NULL;
	char startPlayer[5];
	char currentBoardChar;
	int isMouseStarts;
	int i,j;
	
	char fileName[FILE_NAME_LENGTH];
	getWorldFileName(worldIndex, fileName);
	fp = fopen(fileName, "r");
	
	fscanf(fp, "%s\n", startPlayer);
	strcmp(startPlayer, CAT_STARTS_STR) == 0 ? (isMouseStarts = 0) : (isMouseStarts = 1);
	worldData->isMouseStarts = isMouseStarts;
	fscanf(fp, "%d\n", &(worldData->numTurns));
	char **row = worldData->board;
	char *col = *row;
	
	while ((currentBoardChar = fgetc(fp)) != EOF) {
		if (currentBoardChar != '\n') {
			*col = currentBoardChar;
			col++;
		} else {
			row++;
			col = *row;
		}
	}
	
	fclose(fp);
	return 1;
}

int main() {
	WorldFileData *world = NULL;
	world = (WorldFileData*) malloc(sizeof(WorldFileData));
	world->numTurns = 20;
	world->isMouseStarts = 0;
	char *board[] = {"###P###", "#######", "###W###", "##WWW##", "###W###", "#######", "M#####C"};
	world->board = board;
	writeWorldToFile(1, world);
	
	WorldFileData *readWorld = NULL;
	readWorld = (WorldFileData*) malloc(sizeof(WorldFileData));
	readWorld->board = (char**) malloc(7*sizeof(char*));
	int i = 0;
	for (; i < 7; i++) {
		readWorld->board[i] =  (char*) malloc(7*sizeof(char));
	}
	readWorldFromFile(1, readWorld);
	writeWorldToFile(2, readWorld);
}
	

