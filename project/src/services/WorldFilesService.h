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

// A struct for saving the data read from the file, before making it an actual game.
typedef struct world_file_data {
	char **board; // The board in the file
	int numTurns; // Number of turns
	int isMouseStarts; // Mouse/Cat first turn
} WorldFileData;

// An enum for all possible file errors
typedef enum {
	READ_ERROR,
	WRITE_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR
} FileErrorType;

/* Creates and retunrns an empty WorldFileData struct for using when reading a file's data.  
   Returns NULL in case of an error */
WorldFileData *createEmptyWorldFileData();

/* Free the WorldfileData struct and its board. */
void freeWorldFileData(WorldFileData *worldData);

/* Writes the data given in the worldData struct to the file. 
	Returns 0 on success, 1 if some error occurs. */
int writeWorldToFile(int worldIndex, WorldFileData *worldData);

/* A utility method to parse the WorldFileData from the given file pointer fp. Can be used to read from stdin as well. 
	Returns 0 on success, 1 if some error occurs. */
int parseWorldFile(FILE *fp, int worldIndex, WorldFileData *worldData);

/* Reads a world data from the world file with the given worldIndex. The results is a WorldFileData struct containing the world's data.
	Returns 0 on success, 1 if some error occurs. */
int readWorldFromFile(int worldIndex, WorldFileData *worldData);
	
#endif /* WORLD_FILE_SERVICE_H_ */
