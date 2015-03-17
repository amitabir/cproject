#include "SDL.h"
#include "string.h"

Uint32 getPixelFromSurface(int x, int y, SDL_Surface *surface) {
    // Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *) surface->pixels;

    //Get the pixel requested - the pixels are stored in a one dimensional array, so we can access the pixel (x,y) by accessing pixels[y*width+x].
    return pixels[y * surface->w + x];
}

int findCharLeftSide(SDL_Surface *bitmap, Uint32 bgColor, int cellRow, int cellCol, int cellWidth, int cellHeight) {
	int col,row;
	int pX, pY;
	
    for (col = 0; col < cellWidth; col++) {
        for (row = 0; row < cellHeight; row++) {
            pX = cellWidth * cellCol + col;
            pY = cellHeight * cellRow + row;

            if (get_pixel32(pX, pY, bitmap) != bgColor) {
                return pX;
            }
        }
    }
	return 0; // Shouldn't get here
}

int findCharRightSide(SDL_Surface *bitmap, Uint32 bgColor, int cellRow, int cellCol, int cellWidth, int cellHeight) {
	int col,row;
	int pX, pY;
	
    for (col = cellWidth - 1; col >= 0; col--) {
        for (row = 0; row < cellHeight; row++) {
            pX = cellWidth * cellCol + col;
            pY = cellHeight * cellRow + row;

            if (get_pixel32(pX, pY, bitmap) != bgColor) {
                return pX;
            }
        }
    }
	return 0; // Shouldn't get here
}

void buildFont(BitmapFont *bitmapFont, SDL_Surface *fontImg, Uint32 imgBgColor, int numCellRows, int numCellsCols) {
	int cellW, cellH, cols, rows, currentChar;
	
    // If surface is NULL
    if( surface == NULL ) {
        return;
    }
	
    //Get the bitmap
    bitmapFont->bitmap = fontImg;
	SDL_Surface *bitmap = bitmapFont->bitmap;
	SDL_Rect *chars = bitmapFont->chars;
	
    //Set the cell dimensions
    cellW = bitmap->w / numCellsCols;
    cellH = bitmap->h / numCellRows;
	
    //The current character we're setting
    currentChar = 0;
	
    //Go through the cell rows
    for (rows = 0; rows < numCellRows; rows++) {
        //Go through the cell columns
        for (cols = 0; cols < numCellsCols; cols++) {
            chars[currentChar].y = cellH * rows;
            chars[currentChar].h = cellH;
			
			// Find the right and left sides of the character in the cell, and adjust cell width.
			chars[currentChar].x = findCharLeftSide(bitmap, bgColor, rows, cols, cellW, cellH);
			chars[currentChar].w = findCharRightSide(bitmap, bgColor, rows, cols, cellW, cellH) - chars[currentChar].x + 1;
			
            //Go to the next character
            currentChar++;
        }
    }

    //Calculate space
    bitmapFont->space = cellW / 2;

    //Calculate new line
    bitmapFont->newLine = cellH + 5;
}

void addTextToSurface(BitmapFont *bitmapFont, int textLocationX, int textLocationY, char *text, SDL_Surface *surface) {
    int currX = textLocationX, currY = textLocationY;
	int textIndex, textLength;

    if (bitmapFont->bitmap != NULL) {
		textLength = strlen(text);
        for (textIndex = 0; textIndex < textLength; textIndex++) {
            
            switch (text[textIndex]) {
            	case ' ':
                	currX += bitmapFont->space;
					break;
				case '\n':
	                currY += bitmapFont->newLine;
					currX = textLocationX;
					break;
				default:
                	//Get the ASCII value of the character
					int ascii = (unsigned char)text[textIndex];
				
					SDL_Rect char_rect = bitmapFont->chars[ascii-32];

               	 	//Show the character
               	 	apply_surface(currX, currY, bitmapFont->bitmap, surface, &(bitmapFont->chars[ascii-32]) );
				
                	//Move over the width of the character with one pixel of padding
                	currX += bitmapFont->chars[ ascii-32 ].w + 1;
            }
        }
    }
}

BitmapFont *createFontFromImage(SDL_Surface *fontImg, Uint32 imgBgColor, int numCellRows, int numCellsCols) {
	BitmapFont *result = (BitmapFont*) malloc(sizeof(BitmapFont));
	build_font(result, surface, imgBgColor, numCellRows, numCellsCols);
	return result;
}

void destroyBitmapFont(BitmapFont *bitmapFont) {
	 SDL_FreeSurface(bitmapFont->bitmap);
	 free(bitmapFont);
}