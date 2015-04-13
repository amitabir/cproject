#ifndef BITMAP_FONT_H_
#define BITMAP_FONT_H_

#include <SDL.h>
#include "string.h"
#include "Color.h"

typedef struct bitmap_font {
	SDL_Surface *bitmap;
	SDL_Rect chars[256];
	int newLine;
	int space;
} BitmapFont;

BitmapFont *createFontFromImage(SDL_Surface *fontImg, Color imgBgColor, int numCellRows, int numCellsCols);
void addTextToSurface(BitmapFont *bitmapFont, int textLocationX, int textLocationY, char *text, SDL_Surface *surface);
void freeBitmapFont(BitmapFont *bitmapFont);

#endif
