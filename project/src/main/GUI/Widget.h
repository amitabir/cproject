#ifndef WIDGET_H_
#define WIDGET_H_

#include <SDL.h>
#include <SDL_video.h>
#include "Color.h"
#include "ListUtils.h"

typedef enum {
        WINDOW,
        PANEL,
        BUTTON,
        LABEL
} WidgetType;

typedef struct widget Widget;

Widget *createWidget(Widget *parent, SDL_Rect position, char *caption, WidgetType type, void (*draw)(Widget*), void* (*onClick)(struct widget*), void* (*onMouseHover)(struct widget*));

void* handle_event(Widget *button, SDL_Event event);

int hasChildren(Widget *widget);
int isVisible(Widget *widget);
void setVisible(Widget *widget, int visible);
int isEnabled(Widget *widget);
void setEnabled(Widget *widget, int enabled);
char *getCaption(Widget *widget);
void setCaption(Widget *widget, char *caption);
Color getColor(Widget *widget);
void setTheColor(Widget *widget, Color color);

void setCoords(Widget *widget, Sint16 x, Sint16 y);
void setSize(Widget *widget, Uint16 w, Uint16 h);
SDL_Rect getPosition(Widget *widget);
Sint16 get_x_coor(Widget *widget);
Sint16 get_y_coor(Widget *widget);
Uint16 get_width(Widget *widget);
Uint16 get_height(Widget *widget);

Widget *getParent(Widget *widget);
ListRef getChildren(Widget *widget);
SDL_Surface *getImage(Widget *widget);
SDL_Surface *getScreen(Widget *widget);
void setImage(Widget *widget, SDL_Surface *image);
void setScreen(Widget *widget, SDL_Surface *screen);
void addWidget(Widget *parent, Widget *child);
void removeWidget(Widget *parent, Widget *child);

void (*getDrawFunc(Widget *widget))(Widget *widget);

#endif
