#ifndef WIDGET_H_
#define WIDGET_H_

#include <SDL.h>
#include <SDL_video.h>
#include "Color.h"
#include "../ListUtils.h"
#include "BitmapFont.h"


typedef enum {
        WINDOW,
        PANEL,
        BUTTON,
        LABEL
} WidgetType;

typedef struct widget {
	int id;
	int posX;
	int posY;
	int width;
	int height;
    Color bgColor;
	Color colorKey;
	WidgetType type;
    int visible;
    int enabled;
	int marked;
	int markable;
    const char *caption;
    struct widget *parent;
    ListRef children;
	char *imageFileName;
	char *markedImageFileName;
	char *disabledImageFileName;
    SDL_Surface *image;
	SDL_Surface *markedImage;
    SDL_Surface *disabledImage;
    SDL_Surface *screen;
	BitmapFont *bitmapFont;
	char *text;
	int textPosX;
	int textPosY;
	int preparedForDraw;
	int useColorKey;
	    
	void (*draw)(struct widget*);
} Widget;

Widget *createWidget(int id, Widget *parent, int posX, int posY, int width, int height, const char *caption, WidgetType type,
	 	void (*draw)(Widget*));

void prepareImageWidgetForDrawing(Widget *widget);

void* handle_event(Widget *button, SDL_Event event);

SDL_Surface* loadImage(char *filename);

int hasChildren(Widget *widget);
int isVisible(Widget *widget);
void setVisible(Widget *widget, int visible);
int isEnabled(Widget *widget);
void setEnabled(Widget *widget, int enabled);
int isClickable(Widget *widget);
int isMarked(Widget *widget);
void setMarked(Widget *widget, int marked);
int isMarkable(Widget *widget);
void setMarkable(Widget *widget, int markable);
const char *getCaption(Widget *widget);
void setCaption(Widget *widget, const char *caption);
Color getBgColor(Widget *widget);
void setBgColor(Widget *widget, Color color);
Color setColorKey(Widget *widget, Color color);
void setText(Widget *widget, char *text, int textPosX, int textPosY);

int getId(Widget *widget);
void setCoords(Widget *widget, int x, int y);
void setSize(Widget *widget, int w, int h);
int getPosX(Widget *widget);
int getPosY(Widget *widget);
void setPosX(Widget *widget, int posX);
void setPosY(Widget *widget, int posY);
int getWidth(Widget *widget);
int getHeight(Widget *widget);

Widget *getParent(Widget *widget);
ListRef getChildren(Widget *widget);
SDL_Surface *getImage(Widget *widget);
SDL_Surface *getMarkedImage(Widget *widget);
SDL_Surface *getDisabledImage(Widget *widget);
SDL_Surface *getScreen(Widget *widget);
void setImage(Widget *widget, char *filename);
void setMarkedImage(Widget *widget, char *filename);
void setDisabledImage(Widget *widget, char *filename);
void setScreen(Widget *widget, SDL_Surface *screen);
void addWidget(Widget *parent, Widget *child);
void removeWidget(Widget *parent, Widget *child);
void removeAllChildren(Widget *widget);

void setBitmapFont(Widget *widget, BitmapFont *bitmapFont);
BitmapFont *getBitmapFont(Widget *widget);

Widget *getChildAtindex(Widget *parent, int childIndex);
int findChildIndex(Widget *parent, Widget *child);

void (*getDrawFunc(Widget *widget))(Widget *widget);
void freeWidget(Widget *widget);
#endif
