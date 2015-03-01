#ifndef COLOR_H
#define COLOR_H

Color *createColor(Uint8 r,	Uint8 g, Uint8 b) {
	Color* result;
	result->r = r;
	result->g = g;
	result->b = b;
	return result;
}

void setColor(Color *color, Uint8 r, Uint8 g, Uint8 b) {
	result->r = r;
	result->g = g;
	result->b = b;
}
  
Uint32 getColorForSurface(SDL_Surface *surface) {
	return SDL_MapRGB(surface->format, r, g, b, a);
}
  
#endif
