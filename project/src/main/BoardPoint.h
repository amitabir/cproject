#ifndef BOARD_POINT_H_
#define BOARD_POINT_H_

#include "Constants.h"
#include "stdio.h"

typedef struct board_point {
	int row;
	int col;
	int dist;
} BoardPoint;

int isAdjacent(BoardPoint point1, BoardPoint point2);

float calcOptDistance(BoardPoint point1, BoardPoint point2);

float calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, int isMouse);

#endif /* BOARD_POINT_H_ */
