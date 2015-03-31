#include "SDL.h"
#include "string.h"

typedef struct bitmap_font {
	SDL_Surface *bitmap;
	SDL_Rect chars[256];
	int newLine;
	int space;
} BitmapFont;

BitmapFont *createFontFromImage(SDL_Surface *fontImg, Uint32 imgBgColor, int numCellRows, int numCellsCols);
void addTextToSurface(BitmapFont *bitmapFont, int textLocationX, int textLocationY, char *text, SDL_Surface *surface);
void destroyBitmapFont(BitmapFont *bitmapFont);
