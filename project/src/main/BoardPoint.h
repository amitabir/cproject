#ifndef BOARD_POINT_H_
#define BOARD_POINT_H_

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} MoveDirection;

typedef struct board_point {
	int row;
	int col;
} BoardPoint;


BoardPoint createEmptyPoint();

BoardPoint createPoint(int row, int col);

int isEmptyPoint(BoardPoint point);

BoardPoint getMovedPoint(BoardPoint origPoint, MoveDirection direction);

int getMoveDirectionFromPoint(BoardPoint oldPoint, BoardPoint newPoint, MoveDirection *moveDirection);

int arePointsEqual(BoardPoint point1, BoardPoint point2);

int isAdjacent(BoardPoint point1, BoardPoint point2);

float calcDistance(BoardPoint point1, BoardPoint point2);

#endif /* BOARD_POINT_H_ */
