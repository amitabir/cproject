all: WorldFilesServiceTest

clean:
	-rm WorldFilesServiceTest.o WorldFilesServiceTest

WorldFilesServiceTest: WorldFilesServiceTest.o
	gcc -o WorldFilesServiceTest WorldFilesServiceTest.o -lm -std=c99 -pedantic-errors -g

sdl_test.o: sdl_test.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm WorldFilesServiceTest.c
