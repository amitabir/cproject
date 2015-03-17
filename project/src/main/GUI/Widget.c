#include "Widget.h"

struct widget{
        SDL_Rect position;
        Color bgColor;
	WidgetType type;
        int visible;
        int enabled;
        char *caption;
        struct widget *parent;
        ListRef children;
        SDL_Surface *image;
        SDL_Surface *screen;
        
	void (*draw)(struct widget*);
        void *(*onClick)(struct widget*);
	void *(*onMouseHover)(struct widget*);
};

Widget *createWidget(Widget *parent, SDL_Rect position, char *caption, WidgetType type, void (*draw)(Widget*), void* (*onClick)(struct widget*), void* (*onMouseHover)(struct widget*)){
	Widget *widget =(Widget *) malloc(sizeof(struct widget));
	widget->parent = parent;
	widget->position = position;
	if (parent != NULL){
		widget->position.x += parent->position.x;
		widget->position.y += parent->position.y;
	}
	widget->type = type;
	widget->draw = draw;
	widget->visible = 0;
	widget->enabled = 0;
	widget->caption = caption;
	widget->children = NULL;
	widget->image = NULL;
	widget->screen = NULL;
	widget->onClick = onClick;
	widget->onMouseHover = onMouseHover;
	return widget;
}

void* handle_event(Widget *widget, SDL_Event event){
        switch(event.type){
                case SDL_MOUSEMOTION :
                        return widget->onMouseHover(widget);
                case SDL_MOUSEBUTTONUP :
			if(widget->type == BUTTON){
                        	if (event.button.button == SDL_BUTTON_LEFT){
                                	return widget->onClick(widget);
                        	}
			}
			break;
                //case?
                default :
                        return NULL;
        }
	return NULL;
}

int hasChildren(Widget *widget){
	if(widget->children == NULL){
		return 0;
	} else {
		return 1;
	}
}

int isVisible(Widget *widget){
	return widget->visible;
}

void setVisible(Widget *widget, int visible){
	widget->visible = visible;
}

int isEnabled(Widget *widget){
	return widget->enabled;
}

void setEnabled(Widget *widget, int enabled){
	widget->enabled = enabled;
}

char *getCaption(Widget *widget){
	return widget->caption;
}

void setCaption(Widget *widget, char *caption){
	widget->caption = caption;
}

Color getColor(Widget *widget){
	return widget->bgColor;
}

void setTheColor(Widget *widget, Color color){
	widget->bgColor = color;
}

void setCoords(Widget *widget, Sint16 x, Sint16 y){
	widget->position.x = x;
	widget->position.y = y;
}

void setSize(Widget *widget, Uint16 w, Uint16 h){
	widget->position.w = w;
	widget->position.h = h;
}

SDL_Rect getPosition(Widget *widget){
	return widget->position;
}

Sint16 get_x_coor(Widget *widget){
	return widget->position.x;
}

Sint16 get_y_coor(Widget *widget){
	return widget->position.y;
}

Uint16 get_width(Widget *widget){
	return widget->position.w;
}

Uint16 get_height(Widget *widget){
	return widget->position.h;
}

Widget *getParent(Widget *widget){
	return widget->parent;
}

ListRef getChildren(Widget *widget){
	return widget->children;
}

SDL_Surface *getImage(Widget *widget){
	return widget->image;
}

SDL_Surface *getScreen(Widget *widget){
	return widget->screen;
}

void setImage(Widget *widget, SDL_Surface *image){
	widget->image = image;
}

void setScreen(Widget *widget, SDL_Surface *screen){
	widget->screen = screen;
}


void addWidget(Widget *parent, Widget *child){
	if(parent->children == NULL){
		parent->children = newList(NULL);
	}
	append(parent->children, child);
}
void removeWidget(Widget *parent, Widget *child){
	// TODO
}

void (*getDrawFunc(Widget *widget))(Widget *widget){
	return widget->draw;
}
