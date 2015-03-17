#include <SDL.h>
#include "Widget.h"
#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"
#include "DrawBoard.h"
#include "WidgetFactory.h"
#include "Events.h"
#include "Color.h"

#define ScreenWidth 800
#define ScreenHeight 800

void* onClick(Widget *widget){
	printf("Clicked\n");
	return NULL;
}

SDL_Surface *load_image(char *fileName){
	SDL_Surface *loaded_image = SDL_LoadBMP(fileName);
	return loaded_image;
}

Widget* create_main_menu(Widget *window){
	Widget *button = NULL;
	SDL_Rect window_position;
	window_position.x = 0;
	window_position.y = 0;
	window_position.w = ScreenWidth;
	window_position.h = ScreenHeight;
	window = createWindow(window_position, "Main Menu");
	setImage(window, load_image("main_menu_background.bmp"));
	SDL_Rect button_position;
	button_position.x = 150;
	button_position.y = 150;
	button_position.w = 200;
	button_position.h = 200;
	button = createButton(button_position, onClick, NULL);
	setImage(button, load_image("button.bmp"));
	addWidget(window, button);
	draw_board(window);
	return window;
}

int main(int argc, char* args[]){
	int quit = 0;
	SDL_Event event;
	Widget *window = NULL;
	window = create_main_menu(window);
	while (!quit){
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = 1;
			} else if(event.type == SDL_MOUSEBUTTONUP){
				Widget *widget = findWidgetFromTree(event.button.x,event.button.y,window);
				activateEvent(event, widget);
			}
		}
	}
}
