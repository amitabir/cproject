#include "WidgetFactory.h"

Widget *createWindow(int posX, int posY, int width, int height, const char *caption, Color bgColor) {
	Widget *window = createWidget(0, NULL, posX, posY, width, height, caption, WINDOW, windowDraw);
	setBgColor(window, bgColor);
	return window;
}

Widget *createButton(int id, int posX, int posY, int width, int height, Color colorKey, char *text, int textPosX, int textPosY, const char *imageFileName,
		const char *markedImageFileName) {
	Widget *button = createWidget(id, NULL, posX, posY, width, height, NULL, BUTTON, buttonDraw);
	//setColorKey(button, colorKey);
	setText(button, text, textPosX, textPosY);
	if (imageFileName != NULL) {
		if (setImage(button, imageFileName) != 0) {			
			freeWidget(button);
			return NULL;
		}
	}
	if (markedImageFileName != NULL) {
		if (setMarkedImage(button, markedImageFileName) != 0) {
			freeWidget(button);
			return NULL;
		}
	}
	return button;
}

Widget *createPanel(int posX, int posY, int width, int height, Color bgColor) {
	Widget *panel = createWidget(0 ,NULL, posX, posY, width, height, NULL, PANEL, panelDraw);
	setBgColor(panel, bgColor);
	return panel;
}

Widget *createLabel(int posX, int posY, int width, int height) {
	return createWidget(0 ,NULL, posX, posY, width, height, NULL, LABEL, labelDraw);
}

