CFLAGS=-Wall -g -std=c99 -pedantic-errors
MAIN_O_FILES=WorldFilesService.o MiniMax.o ListUtils.o
TESTS_O_FILES=WorldFilesServiceTest.o
TEST_EXEC_FILES=WorldFilesServiceTest
EXTRA_O_FILES=MiniMaxDemo.o ListUtilsDemo.o
EXTRA_EXEC_FILES=MiniMaxDemo ListUtilsDemo
TEST_PATH=test
MAIN_PATH=src/main

all: test MiniMaxDemo ListUtilsDemo
	
test: WorldFilesServiceTest

clean:
	-rm $(MAIN_O_FILES) $(TEST_EXEC_FILES) $(TESTS_O_FILES) $(EXTRA_O_FILES) $(EXTRA_EXEC_FILES)

WorldFilesService.o: $(MAIN_PATH)/WorldFilesService.c $(MAIN_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
WorldFilesServiceTest.o: $(TEST_PATH)/WorldFilesServiceTest.c $(MAIN_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/WorldFilesServiceTest.c
	
WorldFilesServiceTest: WorldFilesServiceTest.o WorldFilesService.o
	gcc -o $@ $^ $(CFLAGS)
	
ListUtils.o: $(MAIN_PATH)/ListUtils.c $(MAIN_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
ListUtilsDemo.o : $(MAIN_PATH)/ListUtilsDemo.c $(MAIN_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMax.o: $(MAIN_PATH)/MiniMax.c $(MAIN_PATH)/MiniMax.h $(MAIN_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo.o : $(MAIN_PATH)/MiniMaxDemo.c $(MAIN_PATH)/MiniMax.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo: MiniMaxDemo.o MiniMax.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)
	
ListUtilsDemo: ListUtilsDemo.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)