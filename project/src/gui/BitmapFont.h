#ifndef BITMAP_FONT_H_
#define BITMAP_FONT_H_

/* This is a utility class to create text figures according to a given char array (string).
  It does so by clipping a large picture with all the letters according to their ascii values. */

#include <SDL.h>
#include "string.h"
#include "Color.h"

#define ASCII_CHARS_NUM 256

/* The BitmapFont struct*/
typedef struct bitmap_font {
	SDL_Surface *bitmap; // The picture with all the letters.
	SDL_Rect chars[ASCII_CHARS_NUM]; // The clipping array to save all the rectangles where the letters are in the picture.
	int newLine; // The length for a new line.
	int space; // The length for space.
} BitmapFont;

/* Creates a new font struct from a given image with a given background color. The background color is needed to recognize the letters positions, i.e.
	where the letters start and stop. Also uses numCellRows and numCellsCols to specifig the arrangement of the letters in the picuture - it is
	assumed that the letters are arranged in a grid, so the number of rows and cols are needed. 
	Returns the created BitmapFont struct, or NULL if some error occurs.*/
BitmapFont *createFontFromImage(SDL_Surface *fontImg, Color imgBgColor, int numCellRows, int numCellsCols);

/* After the BitmapFont struct is initialized, use this method to add text in the given position onto the given surface. 
	Returns 0 on success, 1 if some error occured. */
int addTextToSurface(BitmapFont *bitmapFont, int textLocationX, int textLocationY, char *text, SDL_Surface *surface);

/* Frees the bitmap font struct */
void freeBitmapFont(BitmapFont *bitmapFont);

#endif
