#include "DrawBoard.h"

void draw_board_rec(Widget *widget){
	Widget *temp_widget = NULL;
	getDrawFunc(widget)(widget);
	ListRef curr = getChildren(widget);
	while (curr != NULL){
		temp_widget = (Widget *) headData(curr);
		setScreen(temp_widget,getScreen(widget));
		draw_board_rec(temp_widget);
		curr = tail(curr);
	}
}

void draw_board(Widget *window){
	draw_board_rec(window);
	SDL_Flip(getScreen(window));
}
