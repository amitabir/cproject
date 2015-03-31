#ifndef WIDGETFACTORY_H_
#define WIDGETFACTORY_H_
#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

Widget *createWindow(int id, int posX, int posY, int width, int height, const char *caption);

Widget *createButton(int id, int posX, int posY, int width, int height, Color colorKey, char *text, int textPosX, int textPosY, char *imageFileName,
		char *markedImageFileName);

Widget *createPanel(int id, int posX, int posY, int width, int height);

Widget *createLabel(int id, int posX, int posY, int width, int height);

#endif
