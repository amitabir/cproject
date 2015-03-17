#ifndef BUTTON_H_
#define BUTTON_H_
#include <SDL.h>
#include "Widget.h"

void button_draw(Widget *button);
void button_handle_event(Widget *button, SDL_Event *event);
#endif
