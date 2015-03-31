#include "Button.h"
#include "Widget.h"
#include "BitmapFont.h"

// TODO remove
#include <string.h>

void button_draw(Widget *button) {
	if (!button->preparedForDraw) {
		prepareImageWidgetForDrawing(button);
	}

	SDL_Surface *fontImage1 = (loadImage("images/Fonts.bmp"));
    SDL_Surface *fontImage = SDL_DisplayFormat( fontImage1 );
    SDL_FreeSurface( fontImage1 );	
    SDL_SetColorKey( fontImage, SDL_SRCCOLORKEY, SDL_MapRGB(fontImage->format, 0xFF, 0xFF, 0xFF ) );
 	BitmapFont *font = createFontFromImage(fontImage, SDL_MapRGB(fontImage->format, 0xFF, 0xFF, 0xFF), 10, 10);

	SDL_Surface *image;
	if (isMarked(button)) {
		image = getMarkedImage(button);
	} else {
		image = getImage(button);
	}
	
	if (button->text != NULL) {
		addTextToSurface(font, button->textPosX, button->textPosY, button->text, image);
	}

	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = getWidth(button);
	size.h = getHeight(button);
	SDL_Rect position;
	position.x = getPosX(button);
	position.y = getPosY(button);
	if (SDL_BlitSurface(image, &size, getScreen(button->parent), &position) != 0) {
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		//TODO
	}
}
