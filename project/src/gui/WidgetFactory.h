#ifndef WIDGETFACTORY_H_
#define WIDGETFACTORY_H_
#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"

/* This function receives two ints which represents the width and height, a const char* caption and a 
Color struct which represents a background color and creates a window widget and return a pointer to it. */
Widget *createWindow(int width, int height, const char *caption, Color bgColor);

/* This function receives an int which represents id, two ints which represents posX and posY coordinates, two ints which represents the width and height, a char* text,
 two ints which represents the text coordinates and two const char* which represents the images' file names which belong to the button. The function creates
the button widget and returns a pointer to it. */
Widget *createButton(int id, int posX, int posY, int width, int height, Color colorKey, char *text, int textPosX, int textPosY, const char *imageFileName,
		const char *markedImageFileName);

/* This function receives two ints which represents the posX and posY coordinates, two ints which represents the width and height, and a 
Color struct which represents a background color and creates a panel widget and return a pointer to it. */
Widget *createPanel(int posX, int posY, int width, int height, Color bgColor);

/* This function receives two ints which represents the posX and posY coordinates, two ints which represents the width and height
 and creates a panel widget and return a pointer to it. */
Widget *createLabel(int posX, int posY, int width, int height);

#endif
