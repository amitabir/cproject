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



void getMovedPoint2(BoardPoint *origPoint, BoardPoint *destPoint, MoveDirection direction) {
	destPoint->row = origPoint->row;
	destPoint->col = origPoint->col;
	destPoint->dist = origPoint->dist + 1;
        switch(direction) {
                case UP:
                        destPoint->row--;
                        break;
                case DOWN:
                        destPoint->row++;
                        break;
                case LEFT:
                        destPoint->col--;
                        break;
                case RIGHT:
                        destPoint->col++;
                        break;
                default:
                        break;
      	}
}

int isCatAround(char **board, BoardPoint point){
	int i = point.row, j = point.col;
	if(board[i+1][j] == CAT_TILE || board[i-1][j] == CAT_TILE || board[i][j+1] == CAT_TILE || board[i][j-1] == CAT_TILE){
		return 1;
	}
	return 0;
}

int isMoveValid2(char **board, BoardPoint *point, MoveDirection direction, int isMouse) {
        BoardPoint *newPoint = (BoardPoint *) malloc(sizeof(BoardPoint));
        getMovedPoint2(point, newPoint, direction);
        if (newPoint->row >= BOARD_ROWS || newPoint->row < 0 || newPoint->col >= BOARD_COLS || newPoint->col < 0) {
                return 0;
        }

        if (board[newPoint->row][newPoint->col] == WALL_TILE){ //|| isMouse*isCatAround(board, newPoint)) {
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
//	printf("Origin is at (%d,%d)", origin.row, origin.col);
//	printf("Destination is at (%d,%d)", destination.row, destination.col);
	char **boardCopy = createBoard2();
	if(boardCopy == NULL){
		//TODO
	}
	int i,j;
	for(i = 0; i < BOARD_ROWS; i++){
		for(j = 0; j < BOARD_COLS; j++){
			boardCopy[i][j] = board[i][j];
			if(!isMouse && board[i][j] == CHEESE_TILE){
//				printf("Cheese!\n");
				boardCopy[i][j] = WALL_TILE;
			}
		}
	}
	float result = 0;
	BoardPoint *point, *originCopy = (BoardPoint *) malloc(sizeof(BoardPoint));
	originCopy->row = origin.row;
	originCopy->col = origin.col;
	originCopy->dist = 0;
	ListRef queue = newList(originCopy);
	//ListRef queue2 = queue;
	while(queue != NULL && !isEmpty(queue)){
		point = (BoardPoint *) headData(queue);
		boardCopy[point->row][point->col] = WALL_TILE;
		BoardPoint *up = (BoardPoint *) malloc(sizeof(BoardPoint));
		BoardPoint *down = (BoardPoint *) malloc(sizeof(BoardPoint));
		BoardPoint *left = (BoardPoint *) malloc(sizeof(BoardPoint));
		BoardPoint *right = (BoardPoint *) malloc(sizeof(BoardPoint));
		if(isMoveValid2(boardCopy, point, UP, isMouse)){
			getMovedPoint2(point, up, UP);
			if(up->row == destination.row && up->col == destination.col){
			//	printf("hurrayup\n");
				result = up->dist;
				break;
			}
			boardCopy[up->row][up->col] = WALL_TILE;
			append(queue, up);
		}
	        if(isMoveValid2(boardCopy, point, DOWN, isMouse)){
                        getMovedPoint2(point, down, DOWN);
                        if(down->row == destination.row && down->col == destination.col){
			//	printf("hurraydown\n");
                                result = down->dist;
                                break;
                        }
			boardCopy[down->row][down->col] = WALL_TILE;
                        append(queue, down);
                }
                if(isMoveValid2(boardCopy, point, LEFT, isMouse)){
		//	printf("left is (%d,%d)\n", left->row, left->col);
                        getMovedPoint2(point, left, LEFT);
		//	printf("left is now (%d,%d)\n", left->row, left->col);
		//	printf("left->row = %d, left->col = %d, dest->row = %d, dest->col = %d\n", left->row, left->col, destination.row, destination.col);
                        if(left->row == destination.row && left->col == destination.col){
			//	printf("hurrayleft\n");
                                result = left->dist;
                                break;
                        }
			boardCopy[left->row][left->col] = WALL_TILE;
                        append(queue, left);
                }
                if(isMoveValid2(boardCopy, point, RIGHT, isMouse)){
                        getMovedPoint2(point, right, RIGHT);
                        if(right->row == destination.row && right->col == destination.col){
			//	printf("hurrayright\n");
                                result = right->dist;
                                break;
                        }
			boardCopy[right->row][right->col] = WALL_TILE;
                        append(queue, right);
                }
		queue = tail(queue);
	}
	//free boardCopy
	//destroyList
	return result;
}
