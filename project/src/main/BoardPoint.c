#include <stdlib.h>
#include <math.h>
#include "BoardPoint.h"
#include "ListUtils.h"

typedef enum {
        UP,
        DOWN,
        LEFT,
        RIGHT
} MoveDirection;


char** createBoard2() {
        char **board;
        int i;

        if ((board = (char**)malloc(BOARD_ROWS * sizeof(char*))) == NULL) {
                perror("Error: standard function malloc has failed");
                return NULL;
        }

        for (i = 0; i < BOARD_ROWS; i++) {
                if ((board[i] = (char*)malloc(BOARD_COLS * sizeof(char))) == NULL) {
                    perror("Error: standard function malloc has failed");
                                        free(board);
                    return NULL;
                }
        }
        return board;
}



BoardPoint getMovedPoint2(BoardPoint origPoint, MoveDirection direction) {
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

int isCatAround(char **board, BoardPoint point){
	int i = point.row, j = point.col;
	if(board[i+1][j] == CAT_TILE || board[i-1][j] == CAT_TILE || board[i][j+1] == CAT_TILE || board[i][j-1] == CAT_TILE){
		return 1;
	}
	return 0;
}

int isMoveValid2(char **board, BoardPoint point, MoveDirection direction, int isMouse) {
        BoardPoint newPoint;
        newPoint = getMovedPoint2(point, direction);

        if (newPoint.row >= BOARD_ROWS || newPoint.row < 0 || newPoint.col >= BOARD_COLS || newPoint.col < 0) {
                return 0;
        }

        if (board[newPoint.row][newPoint.col] == WALL_TILE || isMouse*isCatAround(board, newPoint)) {
                return 0;
        }
        return 1;
}


int isAdjacent(BoardPoint point1, BoardPoint point2) {
	return (point1.row == point2.row && abs(point1.col - point2.col) == 1) || (point1.col == point2.col && abs(point1.row - point2.row) == 1);
}

float calcOptDistance(BoardPoint point1, BoardPoint point2){
	return abs(point1.col - point2.col) + abs(point1.row - point2.row);
}

float calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, int isMouse){
	char **boardCopy = createBoard2();
	if(boardCopy == NULL){
		//TODO
	}
	int i,j;
	for(i = 0; i < BOARD_ROWS; i++){
		for(j = 0; j < BOARD_COLS; j++){
			boardCopy[i][j] = board[i][j];
		}
	}
	float result = 0;
	origin.dist = 0;
	BoardPoint *point;
	ListRef queue = newList(&origin);
	//ListRef queue2 = queue;
/*	while(!isEmpty(queue)){
		point = (BoardPoint *) headData(queue);
		boardCopy[point->row][point->col] = WALL_TILE;
		BoardPoint up, down, left, right;
		if(isMoveValid2(boardCopy, *point, UP, isMouse)){
			up = getMovedPoint2(*point, UP);
			up.dist = point->dist++;
			if(up.row == destination.row || up.col == destination.col){
				result = up.dist;
				break;
			}
			append(queue, &up);
		}
	        if(isMoveValid2(boardCopy, *point, DOWN, isMouse)){
                        down = getMovedPoint2(*point, DOWN);
                        down.dist = point->dist++;
                        if(down.row == destination.row || down.col == destination.col){
                                result = down.dist;
                                break;
                        }
                        append(queue, &down);
                }
                if(isMoveValid2(boardCopy, *point, LEFT, isMouse)){
                        left = getMovedPoint2(*point, LEFT);
                        left.dist = point->dist++;
                        if(left.row == destination.row || left.col == destination.col){
                                result = left.dist;
                                break;
                        }
                        append(queue, &left);
                }
                if(isMoveValid2(boardCopy, *point, RIGHT, isMouse)){
                        right = getMovedPoint2(*point, RIGHT);
                        right.dist = point->dist++;
                        if(right.row == destination.row || right.col == destination.col){
                                result = right.dist;
                                break;
                        }
                        append(queue, &right);
                }
		queue = tail(queue);
	}*/
	//free boardCopy
	//destroyList
	return result;
}
