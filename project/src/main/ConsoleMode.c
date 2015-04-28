#include "ConsoleMode.h"
#include "Model/Evaluation.h"
#include "Model/GameLogicService.h"

//TODO delete from here
char** createBoardTemp() {
        char **board;
        int i, j;

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

                // Init board with empty tiles
                for (i = 0; i < BOARD_ROWS; i++) {
                        for (j = 0; j < BOARD_COLS; j++) {
                                board[i][j] = EMPTY_TILE;
                        }
                }

        return board;
}

int consoleMode2() {
	WorldFileData *worldData = createEmptyWorldFileData();
	int result = parseWorldFile(stdin, 0, worldData);
	if (!result) {
		return 1;
	}
	printf("Finished Parsing! \n");
	GameModel *gameModel = createEmptyGame();
	initGameFromWorldFile(gameModel, worldData);
	freeWorldFileData(worldData);
		
	int score = getScoreForState(gameModel->board, gameModel->catPoint, gameModel->mousePoint, gameModel->cheesePoint, gameModel->numTurns, gameModel->isMouseTurn);
	printf("%d \n", score);
	freeGame(gameModel);
	
	return 0;
}

int consoleMode3() {
	int quit = 0;
	while(!quit) {
		quit = consoleMode2();
	}
	return 1;
}


int consoleMode(){
	int quit = 0;
        char startPlayer[5],read[5], tempChar;
	char **board = createBoardTemp();
        int i, j, numTurns, score;
	BoardPoint catPoint, mousePoint, cheesePoint;
while(!quit){
        if (scanf("%s", read) < 0) {
//                handleFileError(fp, WRITE_ERROR, worldIndex);
                return 0;
        }
	tempChar = getchar();
	if(strlen(read) == 1){
		if(read[0] == 'q'){
			quit = 1;
			break;
		} else {
			sscanf(read, "%d", &numTurns);
		}
	}

        if (scanf("%s", startPlayer) < 0) {
//                handleFileError(fp, WRITE_ERROR, worldIndex);
                return 0;
        }
	tempChar = getchar();
        for (i = 0; i < BOARD_ROWS; i++) {
                for (j = 0; j < BOARD_COLS; j++) {
                        tempChar = (char) getchar();
			switch (tempChar){
				case MOUSE_TILE :
					mousePoint.row = i;
					mousePoint.col = j;
					board[i][j] = EMPTY_TILE;
					break;
				case CAT_TILE :
					catPoint.row = i;
					catPoint.col = j;
					board[i][j] = EMPTY_TILE;
					break;
				case CHEESE_TILE :
					cheesePoint.row = i;
					cheesePoint.col = j;
					board[i][j] = EMPTY_TILE;
					break;
				case WALL_TILE :
					board[i][j] = WALL_TILE;
					break;
				default : // Empty tile
					board[i][j] = EMPTY_TILE;
					break;
			}
                }
                tempChar = getchar();
        }
		//TODO
	score = getScoreForState(board, catPoint, mousePoint, cheesePoint, 0, 0);
	printf("%d\n", score);
}
	return 1;
} 
