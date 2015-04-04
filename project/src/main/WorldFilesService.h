#ifndef WORLD_FILE_SERVICE_H_
#define WORLD_FILE_SERVICE_H_

// Define constants
#define MIN_WORLD_INDEX 1
#define MAX_WORLD_INDEX 5
#define DEFAULT_TURNS_NUMBER 20
#define FILE_NAME_LENGTH 18
#define FILE_ERROR_MESSAGE_MAX_LENGTH 100
static const char WORLD_FILE_DIR[] = "worlds";
static const char WORLD_FILE_PREFIX[] = "world_";
static const char WORLD_FILE_ENDING[] = ".txt";
static const char CAT_STARTS_STR[] = "cat";
static const char MOUSE_STARTS_STR[] = "mouse";

typedef struct world_file_data {
	char **board;
	int numTurns;
	int isMouseStarts;
} WorldFileData;

typedef enum {
	READ_ERROR,
	WRITE_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR
} FileErrorType;

int writeWorldToFile(int worldIndex, WorldFileData *worldData);
int readWorldFromFile(int worldIndex, WorldFileData *worldData);
char *worldIndexToStr(int worldIndex);
	
#endif /* WORLD_FILE_SERVICE_H_ */
