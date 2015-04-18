#include "UITree.h"

void drawUITreeRec(Widget *widget) {
	Widget *currWidget = NULL;
	if (isVisible(widget)) {
		getDrawFunc(widget)(widget);
		ListRef curr = getChildren(widget);
		while (curr != NULL) {
			currWidget = (Widget *) headData(curr);
			drawUITreeRec(currWidget);
			curr = tail(curr);
		}
	}
}

void drawUITree(Widget *window) {
	drawUITreeRec(window);
	SDL_Flip(getScreen(window));
}

int isCoorsInWidget(Uint16 x, Uint16 y, Widget *widget){
	int widget_x = getPosX(widget);
	int widget_y = getPosY(widget);
	int widget_w = getWidth(widget);
	int widget_h = getHeight(widget);
	if( (widget_x < x) && (x < (widget_x + widget_w)) && (widget_y < y) && (y < (widget_y + widget_h))){
		return 1;
	} else {
		return 0;
	}
}

Widget *findWidgetFromTree(Uint16 x, Uint16 y, Widget *widget) {
	if (!hasChildren(widget)){
		return widget;
	}
	Widget *tempWidget = NULL;
	ListRef curr = getChildren(widget);
	while (curr != NULL) {
		tempWidget = (Widget *) headData(curr);
		if (isCoorsInWidget(x, y, tempWidget)) {
			tempWidget = findWidgetFromTree(x,y, tempWidget);
			return tempWidget;
		}
		curr = tail(curr);
	}
	return widget;
}
