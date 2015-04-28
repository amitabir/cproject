#include <stdlib.h>
#include <math.h>
#include "BoardPoint.h"
#include "../Utils/ListUtils.h"

BoardPoint createEmptyPoint() {
        BoardPoint result;
        result.row = -1;
        result.col = -1;
        return result;
}

BoardPoint createPoint(int row, int col) {
        BoardPoint result;
        result.row = row;
        result.col = col;
        return result;
}

int isEmptyPoint(BoardPoint point) {
        return point.row == -1 || point.col == -1;
}

BoardPoint getMovedPoint(BoardPoint origPoint, MoveDirection direction) {
        BoardPoint result;
        result.row = origPoint.row;
        result.col = origPoint.col;
        switch(direction) {
                case UP:
                        result.row--;
                        break;
                case DOWN:
                        result.row++;
                        break;
                case LEFT:
                        result.col--;
                        break;
                case RIGHT:
                        result.col++;
                        break;
                default:
                        break;
        }

        return result;
}

int getMoveDirectionFromPoint(BoardPoint oldPoint, BoardPoint newPoint, MoveDirection *moveDirection) {
        if (isAdjacent(newPoint, oldPoint)) {
                if (newPoint.row == oldPoint.row && newPoint.col == oldPoint.col - 1) {
                        *moveDirection = LEFT;
                } else if (newPoint.row == oldPoint.row && newPoint.col == oldPoint.col + 1) {
                        *moveDirection = RIGHT;
                } else if (newPoint.row == oldPoint.row - 1 && newPoint.col == oldPoint.col) {
                        *moveDirection = UP;
                } else {
                        *moveDirection = DOWN;
                }
                return 1;
        }
        return 0;
}

int arePointsEqual(BoardPoint point1, BoardPoint point2) {
	return point1.row == point2.row && point1.col == point2.col;
}

int isAdjacent(BoardPoint point1, BoardPoint point2) {
	return (point1.row == point2.row && abs(point1.col - point2.col) == 1) || (point1.col == point2.col && abs(point1.row - point2.row) == 1);
}
