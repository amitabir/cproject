#ifndef LABEL_H_
#define LABEL_H_

#include <SDL.h>
#include "Widget.h"

void label_draw(Widget *winodw);
void label_handle_event(Widget *window, SDL_Event *event);
#endif
