#include "Window.h"

#define DEFAULT_BPP 0

int initScreen(Widget *window) {
    setScreen(window, SDL_SetVideoMode(getWidth(window), getHeight(window), DEFAULT_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF));
    
	if (getScreen(window) == NULL) {
            return 0;
			printf("Screen is NULL\n");
    }
	
    //Set the window caption
    SDL_WM_SetCaption(window->caption, NULL);
	
	// Create Bitmap Font helper for this window and its children widgets
	SDL_Surface *fontImg = (loadImage("images/Fonts.bmp"));
	Color fontImgBgColor = createColor(0xFF, 0xFF, 0xFF);
 	BitmapFont *bitmapFont = createFontFromImage(fontImg, fontImgBgColor, 10, 10);
	setBitmapFont(window, bitmapFont);
	
	window->preparedForDraw = 1;
    return 1;
}

void windowDraw(Widget *window) {
	if (!window->preparedForDraw) {
		initScreen(window);
	}
	SDL_FillRect(getScreen(window), NULL, getFormattedColor(getBgColor(window), getScreen(window)));
}
