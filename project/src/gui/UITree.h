#ifndef UITREE_H_
#define UITREE_H_

#include <SDL.h>
#include "Widget.h"

/* This function receives a Widget pointer and draws the widget and all of his descendants in The UITree. */
int drawUITree(Widget *widget);

/* This function receives two Uint16 x, y and a widget pointer and returns a pointer to the widget which the
 x and y fall in his territory. */
Widget *findWidgetFromTree(Uint16 x, Uint16 y, Widget *widget);

#endif
