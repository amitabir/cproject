#include "Window.h"

#define DEFAULT_BPP 0

/* This function receives a Widget pointer to a window and initiates it. */
int initScreen(Widget *window) {
    setScreen(window, SDL_SetVideoMode(getWidth(window), getHeight(window), DEFAULT_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF));    
	
	if (getScreen(window) == NULL) {
		fprintf(stderr, "ERROR: failed to set video mode: %s\n", SDL_GetError());
		return 1;
    }
	
    //Set the window caption
    SDL_WM_SetCaption(window->caption, NULL);
	
	// Create Bitmap Font helper for this window and its children widgets
	SDL_Surface *fontImg = loadImage("images/Font.bmp");
	Color fontImgBgColor = createColor(0xFF, 0xFF, 0xFF);
 	BitmapFont *bitmapFont = createFontFromImage(fontImg, fontImgBgColor, 10, 10);
	if (bitmapFont == NULL) {
		return 1;
	}
	setBitmapFont(window, bitmapFont);
	
	window->preparedForDraw = 1;
    return 0;
}

// Draw the window, init the screen on the first time.
int windowDraw(Widget *window) {
	if (!window->preparedForDraw) {
		if (initScreen(window) != 0) {
			return 1;
		}
	}
	if (SDL_FillRect(getScreen(window), NULL, getFormattedColor(getBgColor(window), getScreen(window))) != 0) {
		fprintf(stderr, "ERROR: Could fill rectangle for window scrren: %s\n", SDL_GetError());		
		return 1;
	}
	return 0;
}
