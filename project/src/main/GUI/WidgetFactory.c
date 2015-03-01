#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

Widget *createWindow(SDL_Rect position, char *caption) {
	return createWidget(NULL, position, caption, window_draw, window_handle_event);
}

Widget *createButton(SDL_Rect position) {
	return createWidget(NULL, position, NULL, button_draw, button_handle_event);
}

Widget *createPanel(SDL_Rect position) {
	return createWidget(NULL, position, NULL, panel_draw, panel_handle_event);
}

Widget *createLabel(SDL_Rect position) {
	return createWidget(NULL, position, NULL, label_draw, label_handle_event);
}

