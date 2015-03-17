EXTRA_O_FILES=ListUtils.o Widget.o Color.o WidgetFactory.o Button.o Window.o Label.o Panel.o DrawBoard.o Events.o

all: MainMenu

clean:
	-rm MainMenu MainMenu.o $(EXTRA_O_FILES)

ListUtils.o: ListUtils.h ListUtils.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm ListUtils.c `sdl-config --cflags`

Widget.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Widget.c `sdl-config --cflags`

Color.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Color.c `sdl-config --cflags`

WidgetFactory.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm WidgetFactory.c `sdl-config --cflags`

Button.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Button.c `sdl-config --cflags`

Window.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Window.c `sdl-config --cflags`

Label.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Label.c `sdl-config --cflags`

Panel.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Panel.c `sdl-config --cflags`

DrawBoard.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm DrawBoard.c `sdl-config --cflags`

Events.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Events.c `sdl-config --cflags`

MainMenu.o:
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm MainMenu.c `sdl-config --cflags`

MainMenu: ListUtils.o Widget.o WidgetFactory.o Button.o Window.o DrawBoard.o MainMenu.o Events.o Color.o
	gcc  -o MainMenu *.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`
