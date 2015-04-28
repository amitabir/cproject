#include "UITree.h"

int shouldDraw(Widget *parent, Widget *child) {
	if (getPosX(child) < getPosX(parent) || getPosX(child) > getPosX(parent) + getWidth(parent)) {
		printf("%d %d %d \n", getPosX(child) ,getPosX(parent), getPosX(parent) + getWidth(parent));
		return 0;
	}
	if (getPosY(child) < getPosY(parent) || getPosY(child) > getPosY(parent) + getHeight(parent)) {
		return 0;
	}
	return 1;
}

int drawUITreeRec(Widget *widget) {
	Widget *currWidget = NULL;
	if (isVisible(widget)) {
		if (getDrawFunc(widget)(widget) != 0) {
			return 1;
		}
		ListRef curr = getChildren(widget);
		while (curr != NULL) {
			currWidget = (Widget *) headData(curr);
			if (shouldDraw(widget, currWidget)) {
				if (drawUITreeRec(currWidget) != 0) {
					return 1;
				}
			}
			curr = tail(curr);
		}
	}
	return 0;
}

int drawUITree(Widget *window) {
	if (drawUITreeRec(window) != 0) {
		return 1;
	}
	if (SDL_Flip(getScreen(window)) != 0) {
		perror("ERROR: Failed to flip window buffer");
		return 1;
	}
	return 0;
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
