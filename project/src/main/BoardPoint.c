#include <stdlib.h>
#include <math.h>
#include "BoardPoint.h"

int isAdjacent(BoardPoint point1, BoardPoint point2) {
	return (point1.row == point2.row && abs(point1.col - point2.col) == 1) || (point1.col == point2.col && abs(point1.row - point2.row) == 1);
}

float calcDistance(BoardPoint point1, BoardPoint point2) {
	return sqrt(pow((point1.row - point2.row),2) +  pow((point1.col - point2.col),2));
}
