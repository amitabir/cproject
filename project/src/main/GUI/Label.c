#include "Label.h"
#include "BitmapFont.h"

void labelDraw(Widget *label) {
	if (!label->preparedForDraw) {
		prepareImageWidgetForDrawing(label);
	}
	
	SDL_Surface *labelSurface = getImage(label);
	if (labelSurface == NULL) {
		labelSurface = SDL_CreateRGBSurface(0, getWidth(label), getWidth(label), 32, 0, 0, 0, 0);
		SDL_FillRect(labelSurface, NULL, getFormattedColor(getBgColor(label), labelSurface));
	}	
	
	addTextToSurface(getBitmapFont(label), label->textPosX, label->textPosY, label->text, labelSurface);
	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = getWidth(label);
	size.h = getHeight(label);
	SDL_Rect position;
	position.x = getPosX(label);
	position.y = getPosY(label);
	if (SDL_BlitSurface(labelSurface, &size, getScreen(label->parent), &position) != 0) {
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		//TODO
	}
}
