#include "Button.h"
#include "Widget.h"
#include "BitmapFont.h"

void buttonDraw(Widget *button) {
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
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		//TODO
	}
}
