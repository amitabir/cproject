#include "Panel.h"

void panel_draw(Widget *panel){
	SDL_Rect position = getPosition(panel);
        if (SDL_BlitSurface(getImage(panel), NULL, getScreen(panel),&position ) != 0){
                printf("ERROR: failed to blit image: %s\n", SDL_GetError());
                //TODO
        }

}

void panel_handle_event(Widget *window, SDL_Event *event){

}
