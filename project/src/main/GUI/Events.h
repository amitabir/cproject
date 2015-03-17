#ifndef EVENTS_H_
#define EVENTS_H_
#include "Widget.h"

Widget *findWidgetFromTree(Uint16 x, Uint16 y, Widget *widget);

void activateEvent(SDL_Event event, Widget *widget);

#endif
