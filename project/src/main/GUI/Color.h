#ifndef COLOR_H_
#define COLOR_H_

#include <SDL.h>

/* The Color struct which represents a RGB color and has this three fields - Red, Green, Blue. */
typedef struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Color;

/* This function receives three Uint8 which represents the RGB colors and creates a color struct
from them and returns it. */
Color createColor(Uint8 r,	Uint8 g, Uint8 b);

/* This function receives a Color struct and a pointer to a SDL_Surface and formatting it to the
SDL RGB format and returning a Uint32 which represents it. */
Uint32 getFormattedColor(Color colorKey, SDL_Surface *surface);

/* This function receives a Color struct which represents a key color and a SDL_Surface pointer and sets the
 surface's key color to it. */
int setColorKeyForSurface(Color colorKey, SDL_Surface *surface);

#endif
