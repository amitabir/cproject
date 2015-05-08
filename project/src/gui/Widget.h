#ifndef WIDGET_H_
#define WIDGET_H_

#include <SDL.h>
#include <SDL_video.h>
#include "Color.h"
#include "../main/ListUtils.h"
#include "BitmapFont.h"

/* This enum defines the possible types of widgets */
typedef enum {
        WINDOW,
        PANEL,
        BUTTON,
        LABEL
} WidgetType;

/* The widget struct defines the widget with all the necessary fields to describe all of the widget types */
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
	const char *imageFileName;
	const char *markedImageFileName;
	const char *disabledImageFileName;
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
	    
	int (*drawFunc)(struct widget*);
} Widget;

/* This function receives an id int, a parent widget, two ints posX and posY, int height, a const char* caption,
 a widgetType type and a drawFunc function to draw the widget and returns a Widget pointer to a new widget with the
 received arguments set. */
Widget *createWidget(int id, Widget *parent, int posX, int posY, int width, int height, const char *caption, WidgetType type,
	 	int (*drawFunc)(Widget*));

/* This function receives a Widget pointer widget and prepares it to drawing by loading the necessary images and
 and marking the widget as ready for drawing */
void prepareImageWidgetForDrawing(Widget *widget);

/* This function receives a Widget pointer and a SDL event and */ // TODO
void* handle_event(Widget *button, SDL_Event event);

/* This function receives a file name and loads the image by that name and returns a pointer to that SDL_Surface. */
SDL_Surface* loadImage(const char *filename);

/* This function receives a Widget pointer and returns 1 if the widget has any children and 0 otherwise. */
int hasChildren(Widget *widget);

/* This function receives a Widget pointer and returns 1 if the widget is visible and 0 otherwise. */
int isVisible(Widget *widget);

/* This function receives a Widget pointer and a visible int and sets the widget's visible field to it. */
void setVisible(Widget *widget, int visible);

/* This function receives a Widget pointer and returns 1 if the widget is enabled and 0 otherwise. */
int isEnabled(Widget *widget);

/* This function receives a Widget pointer and an enabled int and sets the widget's enabled field to it. */
void setEnabled(Widget *widget, int enabled);

/* This function receives a Widget pointer and returns 1 if the widget is clickable, i.e. should do something
if clicked, and 0 otherwise. */
int isClickable(Widget *widget);

/* This function receives a Widget pointer and returns 1 if the widget is marked and 0 otherwise. */
int isMarked(Widget *widget);

/* This function receives a Widget pointer and a marked int and sets the widget's marked field to it. */
void setMarked(Widget *widget, int marked);

/* This function receives a Widget pointer and returns 1 if the widget is markable and 0 otherwise. */
int isMarkable(Widget *widget);

/* This function receives a Widget pointer and a markable int and sets the widget's markable field to it. */
void setMarkable(Widget *widget, int markable);

/* This function receives a Widget pointer and returns a const char* which represents the caption of the widget. */
const char *getCaption(Widget *widget);

/* This function receives a Widget pointer and a const char* caption and sets the widget's caption field to it. */
void setCaption(Widget *widget, const char *caption);

/* This function receives a Widget pointer and returns a Color struct which represents the background color of the widget. */
Color getBgColor(Widget *widget);

/* This function receives a Widget pointer and a Color struct and sets the widget's background color field to it. */
void setBgColor(Widget *widget, Color color);

/* This function receives a Widget pointer and a Color struct and sets the widget's color key field to it. */
Color setColorKey(Widget *widget, Color color);

// TODO
int setText(Widget *widget, const char *text, int textPosX, int textPosY);

/* This function receives a Widget pointer and returns an int which represents the id of the widget. */
int getId(Widget *widget);

/* This function receives a Widget pointer and two ints x and y and sets the widget's posX and posY fields to it. */
void setCoords(Widget *widget, int x, int y);

/* This function receives a Widget pointer and two ints w and h and sets the widget's width and height fields to it. */
void setSize(Widget *widget, int w, int h);

/* This function receives a Widget pointer and returns an int which represents the X position of the widget. */
int getPosX(Widget *widget);

/* This function receives a Widget pointer and returns an int which represents the Y position of the widget. */
int getPosY(Widget *widget);

/* This function receives a Widget pointer and an int posX and sets the posX field to it. */
void setPosX(Widget *widget, int posX);

/* This function receives a Widget pointer and an int posY and sets the posY field to it. */
void setPosY(Widget *widget, int posY);

/* This function receives a Widget pointer and returns an int which represents the width of the widget. */
int getWidth(Widget *widget);

/* This function receives a Widget pointer and returns an int which represents the height of the widget. */
int getHeight(Widget *widget);

/* This function receives a Widget pointer and returns a Widget pointer which represents the parent of the widget. */
Widget *getParent(Widget *widget);

/* This function receives a Widget pointer and returns a ListRef struct which represents the children of the widget. */
ListRef getChildren(Widget *widget);

/* This function receives a Widget pointer and returns a SDL_Surface pointer which represents the image of the widget. */
SDL_Surface *getImage(Widget *widget);

/* This function receives a Widget pointer and returns a SDL_Surface pointer which represents the marked image of the widget. */
SDL_Surface *getMarkedImage(Widget *widget);

/* This function receives a Widget pointer and returns a SDL_Surface pointer which represents the disabled image of the widget. */
SDL_Surface *getDisabledImage(Widget *widget);

/* This function receives a Widget pointer and returns a SDL_Surface pointer which represents the screen of the widget. */
SDL_Surface *getScreen(Widget *widget);

/* This function receives a Widget pointer and a file name of an image and loads it to be the image of the widget. */
int setImage(Widget *widget, const char *filename);

/* This function receives a Widget pointer and a file name of an image and loads it to be the marked image of the widget. */
int setMarkedImage(Widget *widget, const char *filename);

/* This function receives a Widget pointer and a file name of an image and loads it to be the disabled image of the widget. */
int setDisabledImage(Widget *widget, const char *filename);

/* This function receives a Widget pointer and a SDL_surface pointer of a screen and sets it to be the screen of the widget. */
void setScreen(Widget *widget, SDL_Surface *screen);

/* This function receives two Widget pointers which represent the parent and the child and adds the child to the parent's children list. */
void addWidget(Widget *parent, Widget *child);

/* This function receives two Widget pointers which represent the parent and the child and removes the child from the parent's children list. */
void removeWidget(Widget *parent, Widget *child);

/* This function receives a Widget pointer and removes all of the children from the widget's children list. */
void removeAllChildren(Widget *widget);

/* This function receives a Widget pointer and a BitmapFont struct pointer of a bitmapFont and sets it to be the bitmapFont of the widget. */
void setBitmapFont(Widget *widget, BitmapFont *bitmapFont);

/* This function receives a Widget pointer and returns a BitmapFont struct pointer of the bitmapFont of the widget. */
BitmapFont *getBitmapFont(Widget *widget);

/* This function receives a Widget pointer and an int childIndex and returns a Widget pointer of the widget's child at childIndex. */
Widget *getChildAtindex(Widget *parent, int childIndex);

/* This function receives a Widget pointer and returns the number of children of the widget. */
int getChildrenNum(Widget *parent);

/* This function receives two Widget pointers which represent the parent and the child and returns an int which represents the child's index at the
parent's children list. */
int findChildIndex(Widget *parent, Widget *child);

/* This function receives a Widget pointer and returns the draw function of the widget. */
int (*getDrawFunc(Widget *widget))(Widget *widget);

/* This function receives a Widget pointer and frees everything attached to it and the widget at the end. */
void freeWidget(void *widgetPtr);

#endif
