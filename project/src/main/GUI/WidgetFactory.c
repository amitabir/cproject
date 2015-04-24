#include "WidgetFactory.h"

Widget *createWindow(int id, int posX, int posY, int width, int height, const char *caption) {
	return createWidget(id, NULL, posX, posY, width, height, caption, WINDOW, windowDraw);
}

Widget *createButton(int id, int posX, int posY, int width, int height, Color colorKey, char *text, int textPosX, int textPosY, char *imageFileName,
		char *markedImageFileName) {
	Widget* button = createWidget(id, NULL, posX, posY, width, height, NULL, BUTTON, buttonDraw);
	setColorKey(button, colorKey);
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

Widget *createPanel(int id, int posX, int posY, int width, int height) {
	return createWidget(id ,NULL, posX, posY, width, height, NULL, PANEL, panelDraw);
}

Widget *createLabel(int id, int posX, int posY, int width, int height) {
	return createWidget(id ,NULL, posX, posY, width, height, NULL, LABEL, labelDraw);
}

