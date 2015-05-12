#include "Widget.h"

// Creates a new widget according to the given parameters - see header for doc.
Widget *createWidget(int id, Widget *parent, int posX, int posY, int width, int height, const char *caption, WidgetType type, 
		int (*drawFunc)(Widget*)){
	Widget *widget;
	
	// Create the widget struct
	if ((widget =(Widget *) malloc(sizeof(struct widget))) == NULL) {
		// Malloc has failed and the user is notified
		perror("ERROR: standard function malloc has failed");
		return NULL;
	}
	
	// Initialize all the widget fields to default values.
	widget->id = id;
	widget->parent = parent;
	widget->posX = posX;
	widget->posY = posY;
	widget->width = width;
	widget->height = height;
	widget->type = type;
	widget->drawFunc = drawFunc;
	widget->visible = 1;
	widget->enabled = 1;
	widget->marked = 0;
	widget->markable = 1;
	widget->caption = caption;
	widget->children = NULL;
	widget->imageFileName = NULL;
	widget->markedImageFileName = NULL;
	widget->disabledImageFileName = NULL;
	widget->image = NULL;
	widget->markedImage = NULL;
	widget->disabledImage = NULL;
	widget->screen = NULL;
	widget->preparedForDraw = 0;
	widget->useColorKey = 0;
	widget->text = NULL;
	widget->bitmapFont = NULL;
	
	// Return the created widget
	return widget;
}

int hasChildren(Widget *widget){
	if (widget->children == NULL){
		return 0;
	} else {
		return 1;
	}
}

SDL_Surface* loadImage(const char *filename) {
    SDL_Surface* loadedImage = NULL;
	loadedImage = SDL_LoadBMP(filename);
	if (loadedImage == NULL) {
		fprintf(stderr, "ERROR: Failed to load image: %s\n", SDL_GetError());
	}
	return loadedImage;
}

int setImage(Widget *widget, const char *filename) {
	if (widget->image != NULL) {
		SDL_FreeSurface(widget->image);
	}
	widget->imageFileName = filename;
    widget->image = loadImage(widget->imageFileName);
	if (widget->image == NULL) {
		return 1;
	}
	return 0;
}

int setMarkedImage(Widget *widget, const char *filename) {
	if (widget->markedImage != NULL) {
		SDL_FreeSurface(widget->markedImage);
	}
	widget->markedImageFileName = filename;
    widget->markedImage = loadImage(widget->markedImageFileName);
	if (widget->markedImage == NULL) {
		return 1;
	}
	return 0;
}

int setDisabledImage(Widget *widget, const char *filename) {
	if (widget->disabledImage != NULL) {
		SDL_FreeSurface(widget->disabledImage);
	}
	widget->disabledImageFileName = filename;
    widget->disabledImage = loadImage(widget->disabledImageFileName);
	if (widget->disabledImage == NULL) {
		return 1;
	}
	return 0;
}

int reloadImages(Widget *widget) {
	if (widget->image != NULL) {
		SDL_FreeSurface(widget->image);
		if (widget->imageFileName != NULL) {
			widget->image = loadImage(widget->imageFileName);
			if (widget->image == NULL) {
				return 1;
			} 
		} else {
			widget->image = NULL;
		}
		widget->preparedForDraw = 0;
	}
	
	if (widget->markedImage != NULL) {
		SDL_FreeSurface(widget->markedImage);
		if (widget->markedImageFileName != NULL) {
			widget->markedImage = loadImage(widget->markedImageFileName);
			if (widget->markedImage == NULL) {
				return 1;
			} 
		} else {
			widget->markedImage = NULL;
		}
		widget->preparedForDraw = 0;
	}
	
	if (widget->disabledImage != NULL) {
		SDL_FreeSurface(widget->disabledImage);
		if (widget->disabledImageFileName != NULL) {
			widget->disabledImage = loadImage(widget->disabledImageFileName);
			if (widget->disabledImage == NULL) {
				return 1;
			} 
		} else {
			widget->disabledImage = NULL;
		}
		widget->preparedForDraw = 0;
	}
	return 0;
}

/* This function receives a Widget pointer and a SDL_Surface pointer of an image and returns an optimized version of the
image using SDL_DisplayFormat function. In addition if the widget is defined with a color key then the optimized image is
set with the according color key. */
SDL_Surface *getOptimizedImage(Widget *widget, SDL_Surface *image) {
	SDL_Surface* optimizedImage = NULL;
	
    // If the image loaded
    if (image != NULL) {
        // Create an optimized surface
        optimizedImage = SDL_DisplayFormat(image);

        // Free the old surface
        SDL_FreeSurface(image);

        // If the surface was optimized and the widget is defined with a color key
        if (optimizedImage != NULL && widget->useColorKey) {
            // Color key the surface
			setColorKeyForSurface(widget->colorKey, optimizedImage);
        }
    }
	return optimizedImage;
}

void prepareImageWidgetForDrawing(Widget *widget) {
	widget->image = getOptimizedImage(widget, widget->image);
	widget->markedImage = getOptimizedImage(widget, widget->markedImage);
	widget->disabledImage = getOptimizedImage(widget, widget->disabledImage);
	widget->preparedForDraw = 1;
}

int getId(Widget *widget){
	return widget->id;
}

int isVisible(Widget *widget){
	return widget->visible;
}

void setVisible(Widget *widget, int visible){
	widget->visible = visible;
}

int isClickable(Widget *widget) {
	return widget->type == BUTTON;
}

int isEnabled(Widget *widget){
	return widget->enabled;
}

void setEnabled(Widget *widget, int enabled){
	widget->enabled = enabled;
}

int isMarked(Widget *widget){
	return widget->marked;
}

void setMarked(Widget *widget, int marked){
	widget->marked = marked;
}

int isMarkable(Widget *widget) {
	return widget->markable;
}

void setMarkable(Widget *widget, int markable) {
	widget->markable = markable;
}

const char *getCaption(Widget *widget){
	return widget->caption;
}

void setCaption(Widget *widget, const char *caption){
	widget->caption = caption;
}

Color getBgColor(Widget *widget){
	return widget->bgColor;
}

void setBgColor(Widget *widget, Color color){
	widget->bgColor = color;
}

Color getColorKey(Widget *widget){
	return widget->colorKey;
}

Color setColorKey(Widget *widget, Color colorKey) {
	widget->useColorKey = 1;
	return widget->colorKey = colorKey;
}

void setCoords(Widget *widget, int x, int y){
	widget->posX = x;
	widget->posY = y;
}

void setSize(Widget *widget, int w, int h){
	widget->width = w;
	widget->height = h;
}

int getPosX(Widget *widget){
	return widget->posX;
}

int getPosY(Widget *widget){
	return widget->posY;
}

void setPosX(Widget *widget, int posX) {
	if (widget->parent != NULL) {
		widget->posX = widget->parent->posX + posX;
	} else {
		widget->posX = posX;
	}	
}

void setPosY(Widget *widget, int posY) {
	if (widget->parent != NULL) {
		widget->posY = widget->parent->posY + posY;
	} else {
		widget->posY = posY;
	}	
}

int getWidth(Widget *widget){
	return widget->width;
}

int getHeight(Widget *widget){
	return widget->height;
}

Widget *getParent(Widget *widget){
	return widget->parent;
}

ListRef getChildren(Widget *widget){
	return widget->children;
}

SDL_Surface *getImage(Widget *widget) {
	return widget->image;
}

SDL_Surface *getMarkedImage(Widget *widget) {
	return widget->markedImage;
}

SDL_Surface *getDisabledImage(Widget *widget) {
	return widget->disabledImage;
}


SDL_Surface *getScreen(Widget *widget) {
	if (widget->screen == NULL) {
		return getScreen(widget->parent);
	}
	return widget->screen;
}

void setScreen(Widget *widget, SDL_Surface *screen) {
	widget->screen = screen;
}

int setText(Widget *widget, const char *text, int textPosX, int textPosY) {
	widget->textPosX = textPosX;
	widget->textPosY = textPosY;
	if (widget->text != NULL) {
		if (reloadImages(widget) != 0) {
			return 1;
		}
		free(widget->text);
	}
	
	if (text != NULL) {
		widget->text = (char *) malloc(sizeof(char) * (strlen(text) + 1));
		strcpy(widget->text, text);
	}
	return 0;
}

// When adding a child widget, update its position according to the parent's starting position
void addWidget(Widget *parent, Widget *child) {
	if (parent->children == NULL) {
		parent->children = newList(NULL);
	}
	append(parent->children, child);
	child->parent = parent;
	
	child->posX += parent->posX;
	child->posY += parent->posY;

	if (child->posX + child->width >= parent->posX + parent->width) {
		child->width = parent->posX + parent->width - child->posX;
	}
	
	if (child->posY + child->height >= parent->posY + parent->height) {
		child->height = parent->posY + parent->height - child->posY;
	}
}
void removeAllChildren(Widget *widget) {
	if (widget->children != NULL) {
		destroyList(widget->children, freeWidget);
	}
	widget->children = NULL;
}

Widget *getChildAtindex(Widget *parent, int childIndex) {
	int currIndex = 0;
	Widget *child;
	ListRef curr = parent->children;
	while (curr != NULL) {
		child = (Widget *) headData(curr);
		if (currIndex == childIndex) {
			return child;
		}
		curr = tail(curr);
		currIndex++;
	}
	return NULL;
}

int findChildIndex(Widget *parent, Widget *child) {
	int currIndex = 0;
	Widget *currChild;
	ListRef curr = parent->children;
	while (curr != NULL) {
		currChild = (Widget *) headData(curr);
		if (currChild == child) {
			return currIndex;
		}
		curr = tail(curr);
		currIndex++;
	}
	return -1;
}

int getChildrenNum(Widget *parent) {
	int count = 0;
	ListRef curr = parent->children;
	while (curr != NULL) {
		count++;
		curr = tail(curr);
	}
	return count;
}

int (*getDrawFunc(Widget *widget))(Widget *widget){
	return widget->drawFunc;
}

void setBitmapFont(Widget *widget, BitmapFont *bitmapFont) {
	widget->bitmapFont = bitmapFont;
}

BitmapFont *getBitmapFont(Widget *widget) {
	if (widget->bitmapFont == NULL) {
		if (widget->parent != NULL) {
			return getBitmapFont(widget->parent);
		}
	} else {
		return widget->bitmapFont;
	}
	return NULL;
}

// Freeing the widget and all of its resources - see header for doc.
void freeWidget(void *widgetPtr) {
	Widget *widget = (Widget *) widgetPtr;
	if (widget->children != NULL) {
		destroyList(widget->children, freeWidget);
	}
	
	if (widget->image != NULL) {
		SDL_FreeSurface(widget->image);
	}
	
	if (widget->markedImage != NULL) {
		SDL_FreeSurface(widget->markedImage);
	}
	
	if (widget->disabledImage != NULL) {
		SDL_FreeSurface(widget->disabledImage);
	}
	
	if (widget->text != NULL) {
		free(widget->text);
	}
	
	// Only the window have it
	if (widget->parent == NULL) {
		if (widget->bitmapFont != NULL) {
			freeBitmapFont(widget->bitmapFont);
		}
		SDL_FreeSurface(widget->screen);
 	}	
	free(widget);
}
