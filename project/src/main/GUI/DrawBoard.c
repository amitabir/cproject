#include "DrawBoard.h"

void draw_board_rec(Widget *widget) {
	Widget *currWidget = NULL;
	if (isVisible(widget)) {
		getDrawFunc(widget)(widget);
		ListRef curr = getChildren(widget);
		while (curr != NULL) {
			currWidget = (Widget *) headData(curr);
			draw_board_rec(currWidget);
			curr = tail(curr);
		}
	}
}

void draw_board(Widget *window) {
	draw_board_rec(window);
	SDL_Flip(getScreen(window));
}
