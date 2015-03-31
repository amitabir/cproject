#ifndef PANEL_H_
#define PANEL_H_
#include <SDL.h>
#include "Widget.h"

void panel_draw(Widget *panel);
void panel_handle_event(Widget *window, SDL_Event *event);
#endif
