#ifndef COLOR_H_
#define COLOR_H_

#include <SDL.h>

typedef struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Color;

Color createColor(Uint8 r,	Uint8 g, Uint8 b);

void setColor(Color *color, Uint8 r,	Uint8 g, Uint8 b);

Uint32 getColorForSurface(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b); 

void setColorKey(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b);

#endif
