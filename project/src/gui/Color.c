#include "Color.h"

Color createColor(Uint8 r,	Uint8 g, Uint8 b) {
	Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	return result;
}
  
Uint32 getFormattedColor(Color colorKey, SDL_Surface *surface) {
	return SDL_MapRGB(surface->format, colorKey.r, colorKey.g, colorKey.b);
}

int setColorKeyForSurface(Color colorKey, SDL_Surface *surface){
	Uint32 colorKeyFormatted = getFormattedColor(colorKey, surface);
	return SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorKeyFormatted);
}
