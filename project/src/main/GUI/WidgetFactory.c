#include "WidgetFactory.h"


Widget *createWindow(SDL_Rect position, char *caption) {
	return createWidget(NULL, position, caption, WINDOW, window_draw, NULL, NULL);
}

Widget *createButton(SDL_Rect position, void* (*onClick)(struct widget*), void* (*onMouseHover)(struct widget*)) {
	return createWidget(NULL, position, NULL, BUTTON, button_draw, onClick, onMouseHover);
}

/*Widget *createPanel(SDL_Rect *position) {
	return createWidget(NULL, position, NULL, PANEL, panel_draw, panel_handle_event, panel_logic);
}

Widget *createLabel(SDL_Rect *position) {
	return createWidget(NULL, position, NULL, LABEL, label_draw, label_handle_event, label_logic);
}*/

