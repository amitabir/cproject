#include <stdio.h>
#include <stdlib.h>
#include "../src/main/WorldFilesService.h"
#include "../src/main/MoveLogicService.h"
#include "../src/main/GameLogicService.h"


int main() {
	WorldFileData *readWorld = NULL;
	readWorld = (WorldFileData*) malloc(sizeof(WorldFileData));
	readWorld->board = (char**) malloc(7*sizeof(char*));
	int i = 0;
	for (; i < 7; i++) {
		readWorld->board[i] =  (char*) malloc(7*sizeof(char));
	}
	readWorldFromFile(1, readWorld);
	printf("World was read from file! \n");	
}
