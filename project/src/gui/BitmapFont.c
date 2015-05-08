#include "string.h"
#include "BitmapFont.h"

#define FIRST_ASCII_CHAR 32

// Returns a single pixel from the sruface.
Uint32 getPixelFromSurface(int x, int y, SDL_Surface *surface) {
    // Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *) surface->pixels;

    //Get the pixel requested - the pixels are stored in a one dimensional array, so we can access the pixel (x,y) by accessing pixels[y*width+x].
    return pixels[y * surface->w + x];
}

// applies the text onto the given destination surface.
int applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    //Blit
   if (SDL_BlitSurface(source, clip, destination, &offset)) {
	   fprintf(stderr, "ERROR: failed to blit surface: %s \n", SDL_GetError());
	   return 1;
   }
	
	return 0;
}

int findCharLeftSide(SDL_Surface *bitmap, Uint32 bgColor, int cellRow, int cellCol, int cellWidth, int cellHeight) {
	int col,row;
	int pX, pY;
	
    for (col = 0; col < cellWidth; col++) {
        for (row = 0; row < cellHeight; row++) {
            pX = cellWidth * cellCol + col;
            pY = cellHeight * cellRow + row;		
            if (getPixelFromSurface(pX, pY, bitmap) != bgColor) {				
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
			
            if (getPixelFromSurface(pX, pY, bitmap) != bgColor) {
                return pX;
            }
        }
    }
	return 0; // Shouldn't get here
}

void buildFont(BitmapFont *bitmapFont, SDL_Surface *fontImg, Uint32 imgBgColor, int numCellRows, int numCellsCols) {
	int cellW, cellH, cols, rows, currentChar;
	
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
			chars[currentChar].x = findCharLeftSide(bitmap, imgBgColor, rows, cols, cellW, cellH);
			chars[currentChar].w = findCharRightSide(bitmap, imgBgColor, rows, cols, cellW, cellH) - chars[currentChar].x + 1;
									
            //Go to the next character
            currentChar++;
        }
    }

    //Calculate space
    bitmapFont->space = cellW / 2;

    //Calculate new line
    bitmapFont->newLine = cellH + 1;
}

// Adds the given text to the surface - see header for doc.
int addTextToSurface(BitmapFont *bitmapFont, int textLocationX, int textLocationY, char *text, SDL_Surface *surface) {
    int currX = textLocationX, currY = textLocationY;
	int textIndex, textLength, ascii;

    if (bitmapFont->bitmap != NULL && text != NULL) {
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
					ascii = (int) text[textIndex];

               	 	// Show the character
               	 	if (applySurface(currX, currY, bitmapFont->bitmap, surface, &(bitmapFont->chars[ascii-FIRST_ASCII_CHAR])) != 0) {
						return 1;
					}

                	//Move over the width of the character with one pixel of padding
                	currX += bitmapFont->chars[ascii-FIRST_ASCII_CHAR].w + 1;
            }
        }
    }
	return 0;
}

// Creates a new BitmapFont from the given image - see header for doc.
BitmapFont *createFontFromImage(SDL_Surface *fontImg, Color fontImgBgColor, int numCellRows, int numCellsCols) {
	BitmapFont *result;
	
	if ((result = (BitmapFont*) malloc(sizeof(BitmapFont))) == NULL) {
		perror("Error: standard function malloc has failed");
		return NULL;
	}
	
    SDL_Surface *fontImageOpt = SDL_DisplayFormat(fontImg);
    SDL_FreeSurface(fontImg);
    SDL_SetColorKey(fontImageOpt, SDL_SRCCOLORKEY, getFormattedColor(fontImgBgColor, fontImageOpt));
	buildFont(result, fontImageOpt, getFormattedColor(fontImgBgColor, fontImageOpt), numCellRows, numCellsCols);
	return result;
}

// Free the bitmap font surface and pointer.
void freeBitmapFont(BitmapFont *bitmapFont) {
	 SDL_FreeSurface(bitmapFont->bitmap);
	 free(bitmapFont);	 
}
