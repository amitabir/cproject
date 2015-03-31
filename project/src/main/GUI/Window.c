#include "Window.h"

#define DEFAULT_BPP 0

int init_screen(Widget *window) {
    setScreen(window, SDL_SetVideoMode(getWidth(window), getHeight(window), DEFAULT_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF));
    
	if (getScreen(window) == NULL) {
            return 0;
			printf("Screen is NULL\n");
    }
	
    //Set the window caption
    SDL_WM_SetCaption(window->caption, NULL);
	
    return 1;
}

void window_draw(Widget *window){
	init_screen(window);
	SDL_FillRect(getScreen(window), NULL, getFormattedColor(getBgColor(window), getScreen(window)));
        // if (SDL_BlitSurface(getImage(window), NULL, getScreen(window), NULL) != 0) {
  //               printf("ERROR: failed to blit image: %s\n", SDL_GetError());
  //       }
	//TODO
}
