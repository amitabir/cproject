#ifndef CONSOLE_MODE_H_
#define CONSOLE_MODE_H_

/* This function performs the console mode procedure of receiving the number of turns left, whose turn is it to play next and the board
and executing the score function on the game state. The score is printed each time the data is received from the user and this function
exits it's loop when 'q\n' is entered by the user. */
int runConsoleMode(int isMousePlayer);

#endif
