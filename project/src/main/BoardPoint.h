#ifndef BOARD_POINT_H_
#define BOARD_POINT_H_

typedef struct board_point {
	int row;
	int col;
} BoardPoint;

int isAdjacent(BoardPoint point1, BoardPoint point2);

float calcDistance(BoardPoint point1, BoardPoint point2);

#endif /* BOARD_POINT_H_ */
