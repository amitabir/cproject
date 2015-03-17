#include "Color.h"

Color createColor(Uint8 r,	Uint8 g, Uint8 b) {
	Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	return result;
}

void setColor(Color *color, Uint8 r, Uint8 g, Uint8 b) {
	color->r = r;
	color->g = g;
	color->b = b;
}
  
Uint32 getColorForSurface(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b) {
	return SDL_MapRGB(surface->format, r, g, b);
}

void setColorKey(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b){
	Uint32 colorKey = getColorForSurface(surface, r, g, b);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorKey);
}
