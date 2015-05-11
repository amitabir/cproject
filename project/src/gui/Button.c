#include <SDL.h>
#include "Button.h"
#include "Widget.h"

int buttonDraw(Widget *button) {
	if (!button->preparedForDraw) {
		prepareImageWidgetForDrawing(button);
	}

	SDL_Surface *image;
	if (!isEnabled(button)) {
		image = getDisabledImage(button);
	} else {
		if (isMarked(button)) {
			image = getMarkedImage(button);
		} else {
			image = getImage(button);
		}
	}
	
	if (button->text != NULL) {
		addTextToSurface(getBitmapFont(button), button->textPosX, button->textPosY, button->text, image);
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
		fprintf(stderr, "ERROR: failed to blit surface: %s \n", SDL_GetError());
		return 1;
	}
	
	return 0;
}
