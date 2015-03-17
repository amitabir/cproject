#ifndef WIDGETFACTORY_H_
#define WIDGETFACTORY_H_
#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

Widget *createWindow(SDL_Rect position, char *caption);

Widget *createButton(SDL_Rect position, void* (*onClick)(struct widget*), void* (*onMouseHover)(struct widget*));

//Widget *createPanel(SDL_Rect *position, void (*logic)(struct widget*, SDL_Event*));

//Widget *createLabel(SDL_Rect *position, void (*logic)(struct widget*, SDL_Event*));
#endif
