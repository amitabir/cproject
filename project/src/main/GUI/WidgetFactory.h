#ifndef WIDGETFACTORY_H_
#define WIDGETFACTORY_H_
#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

Widget *createWindow(int posX, int posY, int width, int height, const char *caption, Color bgColor);

Widget *createButton(int id, int posX, int posY, int width, int height, Color colorKey, char *text, int textPosX, int textPosY, const char *imageFileName,
		const char *markedImageFileName);

Widget *createPanel(int posX, int posY, int width, int height, Color bgColor);

Widget *createLabel(int posX, int posY, int width, int height);

#endif
