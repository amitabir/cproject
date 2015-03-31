#ifndef COLOR_H_
#define COLOR_H_

#include <SDL.h>

typedef struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Color;

Color createColor(Uint8 r,	Uint8 g, Uint8 b);

Uint32 getFormattedColor(Color colorKey, SDL_Surface *surface);

int setColorKeyForSurface(Color colorKey, SDL_Surface *surface);

#endif
