#ifndef BOARD_POINT_H_
#define BOARD_POINT_H_

/* The MoveDirection enum defines all the possible moves. */
typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} MoveDirection;

/* The BoardPoint struct defines a point on the board. */
typedef struct board_point {
	int row;
	int col;
	int dist;
} BoardPoint;

/* This function creates and returns an empty point, i.e. not initialized. */
BoardPoint createEmptyPoint();

/* This function receives two int which represents a row and a column, creates and returns
 a point initialized with these values. */
BoardPoint createPoint(int row, int col);

/* This function receives a point and returns 1 if the point is empty (=uninitialized) and 0 otherwise. */
int isEmptyPoint(BoardPoint point);

/* This function receives a BoardPoint and a direction and returns a BoardPoint moved by the direction from the original point. */
BoardPoint getMovedPoint(BoardPoint origPoint, MoveDirection direction);

/* This function receives two BoardPoints, oldPoint and newPoint and a pointer to a MoveDirection and checks if it is possible
to get from the oldPoint to the newPoint with one move and if so puts that move into the MoveDirection pointer and returns 1,
otherwise it returns 0. */
int getMoveDirectionFromPoint(BoardPoint oldPoint, BoardPoint newPoint, MoveDirection *moveDirection);

/* This function receives two BoardPoints and returns 1 if they are equal, i.e. their row and column values are tha same,
and 0 otherwise. */
int arePointsEqual(BoardPoint point1, BoardPoint point2);

/* This function receives two BoardPoints and returns 1 if they are adjacent, i.e. reachable from one to another by one move,
and 0 otherwise. */
int isAdjacent(BoardPoint point1, BoardPoint point2);

#endif /* BOARD_POINT_H_ */
