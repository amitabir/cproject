#include "Panel.h"
#include <SDL.h>

int panelDraw(Widget *panel){
	SDL_Rect rect;
	rect.x = getPosX(panel);
	rect.y = getPosY(panel);
	rect.w = getWidth(panel);
	rect.h = getHeight(panel);
	
	SDL_Surface *screen = getScreen(panel);
	if (screen == NULL) {
		fprintf(stderr, "ERROR: Could not find initialized screen surface for drawing panel: %s", SDL_GetError());
		return 1;
	} 
	if (SDL_FillRect(screen, &rect, getFormattedColor(getBgColor(panel), screen)) != 0) {
		fprintf(stderr, "Could not fill rectangle for panel: %s \n", SDL_GetError());
		return 1;
	}
	return 0;
}

