#include "Button.h"

void button_draw(Widget *button){
	SDL_Rect position = getPosition(button);
	if (SDL_BlitSurface(getImage(button), NULL, getScreen(button), &position) != 0){
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		//TODO
	}
}
