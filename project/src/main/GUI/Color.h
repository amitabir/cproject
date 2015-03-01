#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>

typedef struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b
} Color;

Color *createColor(Uint8 r,	Uint8 g, Uint8 b);

void setColor(Uint8 r,	Uint8 g, Uint8 b);
  
Uint32 getColorForSurface(SDL_Surface *surface);
  
#endif
