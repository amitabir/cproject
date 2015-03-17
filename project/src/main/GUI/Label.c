#include "Label.h"

void label_draw(Widget *label){
	SDL_Rect position = getPosition(label);
	if (SDL_BlitSurface(getImage(label), NULL, getScreen(label), &position) != 0){
                printf("ERROR: failed to blit image: %s\n", SDL_GetError());
                //TODO
        }
}
