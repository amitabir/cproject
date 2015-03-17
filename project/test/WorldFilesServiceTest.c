#include <stdio.h>
#include <stdlib.h>
#include "../src/main/WorldFilesService.h"

int main() {
	WorldFileData *world = NULL;
	world = (WorldFileData*) malloc(sizeof(WorldFileData));
	world->numTurns = 20;
	world->isMouseStarts = 0;
	char *board[] = {"###P###", "#######", "###W###", "##WWW##", "###W###", "#######", "M#####C"};
	world->board = board;
	int result = writeWorldToFile(1, world);
	printf("Result is : %d \n", result);

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
