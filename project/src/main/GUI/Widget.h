#include <SDL.h>
#include "color.h"

typedef struct widget {
	SDL_Rect position;
    Color bgColor;
    int visible;
    int enabled;
    char *caption;
	Widget *parent;
	ListRef children;
	SDL_Surface *image;
	
	void (*draw)(struct widget*);
	void (*handle_event)(struct widget*, SDL_Event*);
} Widget;

Widget *createWidget(Widget *parent, SDL_Rect position, char *caption, (*draw)(Widget*), (*handle_event)(Widget*, SDL_Event*));

int isVisible(Widget *widget);
void setVisible(Widget *widget, int visible);
int isEnabled(Widget *widget);
void setEnabled(Widget *widget, int enabled);
char *getCaption(Widget *widget);
void setCaption(Widget *widget, char *caption);
Color getColor(Widget *widget);
void setColor(Widget *widget, Color color);

void setCoords(Sint16 x, Sint16 y);
void setSize(Uint16 w, Uint16 h);
SDL_Rect getPosition(Widget *widget);

Widget *getParent(Widget *widget);
void addWidget(Widget *parent, Widget *child);
void removeWidget(Widget *parent, Widget *child);

