#include "Events.h"

int coors_in_widget(Uint16 x, Uint16 y, Widget *widget){
	int widget_x = get_x_coor(widget);
	int widget_y = get_y_coor(widget);
	int widget_w = get_width(widget);
	int widget_h = get_height(widget);
	if( (widget_x < x) && (x < (widget_x + widget_w)) && (widget_y < y) && (y < (widget_y + widget_h))){
		return 1;
	} else {
		return 0;
	}
}

Widget *findWidgetFromTree(Uint16 x, Uint16 y, Widget *widget){
	if (!hasChildren(widget)){
		return widget;
	}
	Widget *tempWidget = NULL;
	ListRef curr = getChildren(widget);
	while (curr != NULL){
		tempWidget = (Widget *) headData(curr);
		if(coors_in_widget(x, y, tempWidget)){
			tempWidget = findWidgetFromTree(x,y, tempWidget);
			return tempWidget;
		}
		curr = tail(curr);
	}
	return widget;
}

void activateEvent(SDL_Event event, Widget *widget){
	handle_event(widget, event);
}
