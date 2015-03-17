#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include "Widget.h"

void window_draw(Widget *winodw);
void window_handle_event(Widget *window, SDL_Event *event);
#endif
