#include "Window.h"

#define ScreenWidth 800
#define ScreenHeight 800

int init_screen(Widget *window){
        if( SDL_Init(SDL_INIT_VIDEO) < 0){
                fprintf(stderr, "ERROR: unable to init SDL: %s\n", SDL_GetError());//TODO
                return 0;
        }
         setScreen(window, SDL_SetVideoMode(ScreenWidth, ScreenHeight, 0, SDL_HWSURFACE|SDL_DOUBLEBUF));
        if(getScreen(window) == NULL){
                return 0;
		printf("Screen is NULL\n");
        }
        return 1;
}

void window_draw(Widget *window){
	init_screen(window);
        if (SDL_BlitSurface(getImage(window), NULL, getScreen(window), NULL) != 0){
                printf("ERROR: failed to blit image: %s\n", SDL_GetError());
        }
	//TODO
}
