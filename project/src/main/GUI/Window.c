#include "Window.h"

#define DEFAULT_BPP 0

int initScreen(Widget *window) {
    //setScreen(window, SDL_SetVideoMode(getWidth(window), getHeight(window), DEFAULT_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF));
    setScreen(window, SDL_SetVideoMode(800, 800, DEFAULT_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF));
    
	
	if (getScreen(window) == NULL) {
		fprintf(stderr, "ERROR: failed to set video mode: %s\n", SDL_GetError());
		return 1;
    }
	
    //Set the window caption
    SDL_WM_SetCaption(window->caption, NULL);
	
	// Create Bitmap Font helper for this window and its children widgets
	SDL_Surface *fontImg = loadImage("images/FonstNew.bmp");
	Color fontImgBgColor = createColor(0xFF, 0xFF, 0xFF);
 	BitmapFont *bitmapFont = createFontFromImage(fontImg, fontImgBgColor, 10, 10);
	setBitmapFont(window, bitmapFont);
	
	window->preparedForDraw = 1;
    return 0;
}

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
