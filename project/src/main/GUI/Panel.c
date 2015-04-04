#include "Panel.h"

void panelDraw(Widget *panel){
	SDL_Rect rect;
	rect.x = getPosX(panel);
	rect.y = getPosY(panel);
	rect.w = getWidth(panel);
	rect.h = getHeight(panel);
	
	SDL_Surface *screen = getScreen(panel);
	SDL_FillRect(screen, &rect, getFormattedColor(getBgColor(panel), screen));
        // if (SDL_BlitSurface(getImage(panel), NULL, getScreen(panel), &position) != 0){
//                 printf("ERROR: failed to blit image: %s\n", SDL_GetError());
//                 //TODO
//         }

}

void panel_handle_event(Widget *window, SDL_Event *event){
	
}
