#include "Widget.h"

Widget *createWidget(int id, Widget *parent, int posX, int posY, int width, int height, const char *caption, WidgetType type, 
		void (*draw)(Widget*)){
	Widget *widget =(Widget *) malloc(sizeof(struct widget));
	widget->id = id;
	widget->parent = parent;
	widget->posX = posX;
	widget->posY = posY;
	widget->width = width;
	widget->height = height;
	widget->type = type;
	widget->draw = draw;
	widget->visible = 1;
	widget->enabled = 1;
	widget->marked = 0;
	widget->markable = 1;
	widget->caption = caption;
	widget->children = NULL;
	widget->imageFileName = NULL;
	widget->image = NULL;
	widget->markedImage = NULL;
	widget->screen = NULL;
	widget->preparedForDraw = 0;
	widget->useColorKey = 0;
	widget->text = NULL;
	return widget;
}

int hasChildren(Widget *widget){
	if (widget->children == NULL){
		return 0;
	} else {
		return 1;
	}
}

SDL_Surface* loadImage(char *filename) {
    SDL_Surface* loadedImage = NULL;
	loadedImage = SDL_LoadBMP(filename);
	return loadedImage;
}

void setImage(Widget *widget, char *filename) {
	widget->imageFileName = filename;
    widget->image = loadImage(widget->imageFileName);
}

void reloadImages(Widget *widget) {
	if (widget->image != NULL) {
		SDL_FreeSurface(widget->image);
		widget->image = loadImage(widget->imageFileName);
		widget->preparedForDraw = 0;
	}
	
	if (widget->markedImage !=  NULL) {
		widget->markedImage = loadImage(widget->markedImageFileName);
		widget->preparedForDraw = 0;
	}
}

void setMarkedImage(Widget *widget, char *filename) {
	widget->markedImageFileName = filename;
    widget->markedImage = loadImage(widget->markedImageFileName);
}

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


SDL_Surface *getScreen(Widget *widget) {
	if (widget->screen == NULL) {
		return getScreen(widget->parent);
	}
	return widget->screen;
}

void setScreen(Widget *widget, SDL_Surface *screen) {
	widget->screen = screen;
}

void setText(Widget *widget, char *text, int textPosX, int textPosY) {
	widget->textPosX = textPosX;
	widget->textPosY = textPosY;
	if (widget->text != NULL) {
		reloadImages(widget);
	}
	widget->text = text;
}

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
void removeWidget(Widget *parent, Widget *child){
	// TODO
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

void (*getDrawFunc(Widget *widget))(Widget *widget){
	return widget->draw;
}
