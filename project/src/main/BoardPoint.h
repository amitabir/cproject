#ifndef BOARD_POINT_H_
#define BOARD_POINT_H_

#include "Constants.h"
#include "stdio.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} MoveDirection;

typedef struct board_point {
	int row;
	int col;
	int dist;
} BoardPoint;


BoardPoint createEmptyPoint();

BoardPoint createPoint(int row, int col);

int isEmptyPoint(BoardPoint point);

BoardPoint getMovedPoint(BoardPoint origPoint, MoveDirection direction);

int getMoveDirectionFromPoint(BoardPoint oldPoint, BoardPoint newPoint, MoveDirection *moveDirection);

int arePointsEqual(BoardPoint point1, BoardPoint point2);

int isAdjacent(BoardPoint point1, BoardPoint point2);

float calcOptDistance(BoardPoint point1, BoardPoint point2);

float calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, int isMouse);

#endif /* BOARD_POINT_H_ */
