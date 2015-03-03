all: WorldFilesService

clean:
	-rm WorldFilesService.o WorldFilesService

sdl_test: WorldFilesService.o
	gcc -o WorldFilesService sdl_test.o -lm -std=c99 -pedantic-errors -g

sdl_test.o: WorldFilesService.c WorldFilesService.h Constants.h
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm WorldFilesService.c 
