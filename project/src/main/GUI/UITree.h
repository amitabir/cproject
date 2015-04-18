#ifndef UITREE_H_
#define UITREE_H_

#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

void drawUITree(Widget *widget);
Widget *findWidgetFromTree(Uint16 x, Uint16 y, Widget *widget);

#endif
