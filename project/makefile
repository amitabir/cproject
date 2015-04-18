CFLAGS=-Wall -g -std=c99 -lm -pedantic-errors
MAIN_O_FILES=WorldFilesService.o MiniMax.o ListUtils.o GameModel.o GameConfigModel.o GameLogicService.o BoardPoint.o \
 	BoardUtils.o Evaluation.o MoveLogicService.o SelectionWindow.o GeneralGameWindow.o MainMenu.o WorldSelection.o ChooseType.o \
 	ChooseSkill.o GamePlay.o GameEditor.o Error.o GUIStatesFactory.o CatAndMouse.o LogicalEvents.o ConsoleMode.o
GUI_O_FILES=BitmapFont.o Widget.o Color.o WidgetFactory.o Button.o Window.o Label.o Panel.o UITree.o
TESTS_O_FILES=WorldFilesServiceTest.o GameLogicServiceTest.o EvaluationTest.o
TEST_EXEC_FILES=WorldFilesServiceTest GameLogicServiceTest EvaluationTest
EXEC_FILES=CatAndMouse
EXTRA_O_FILES=MiniMaxDemo.o ListUtilsDemo.o
EXTRA_EXEC_FILES=MiniMaxDemo ListUtilsDemo
TEST_PATH=test
MAIN_PATH=src/main
GUI_PATH=src/main/GUI
SDL_COMPILE_FLAGS=`sdl-config --cflags`
SDL_EXEC_FLAGS=`sdl-config --libs`


all: test MiniMaxDemo ListUtilsDemo CatAndMouse
	
test: WorldFilesServiceTest GameLogicServiceTest EvaluationTest

clean:
	-rm $(EXEC_FILES) $(MAIN_O_FILES) $(GUI_O_FILES) $(TEST_EXEC_FILES) $(TESTS_O_FILES) $(EXTRA_O_FILES) $(EXTRA_EXEC_FILES)
	
#GUI Files:

BitmapFont.o: $(GUI_PATH)/BitmapFont.c $(GUI_PATH)/BitmapFont.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)

Widget.o: $(GUI_PATH)/Widget.c $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Color.o: $(GUI_PATH)/Color.c $(GUI_PATH)/Color.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
WidgetFactory.o: $(GUI_PATH)/WidgetFactory.c $(GUI_PATH)/WidgetFactory.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Button.o: $(GUI_PATH)/Button.c $(GUI_PATH)/Button.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Window.o: $(GUI_PATH)/Window.c $(GUI_PATH)/Window.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Label.o: $(GUI_PATH)/Label.c $(GUI_PATH)/Label.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Panel.o: $(GUI_PATH)/Panel.c $(GUI_PATH)/Panel.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
UITree.o: $(GUI_PATH)/UITree.c $(GUI_PATH)/UITree.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)

#Game Files

WorldFilesService.o: $(MAIN_PATH)/WorldFilesService.c $(MAIN_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
WorldFilesServiceTest.o: $(TEST_PATH)/WorldFilesServiceTest.c $(MAIN_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/WorldFilesServiceTest.c
	
WorldFilesServiceTest: WorldFilesServiceTest.o WorldFilesService.o BoardUtils.o
	gcc -o $@ $^ $(CFLAGS)

GameModel.o: $(MAIN_PATH)/GameModel.c $(MAIN_PATH)/GameModel.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c

GameConfigModel.o: $(MAIN_PATH)/GameConfigModel.c $(MAIN_PATH)/GameConfigModel.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c

GameLogicService.o: $(MAIN_PATH)/GameLogicService.c $(MAIN_PATH)/GameLogicService.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c	

BoardPoint.o: $(MAIN_PATH)/BoardPoint.c $(MAIN_PATH)/BoardPoint.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
BoardUtils.o: $(MAIN_PATH)/BoardUtils.c $(MAIN_PATH)/BoardUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
Evaluation.o: $(MAIN_PATH)/Evaluation.c $(MAIN_PATH)/Evaluation.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
ConsoleMode.o: $(MAIN_PATH)/ConsoleMode.c $(MAIN_PATH)/ConsoleMode.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MoveLogicService.o: $(MAIN_PATH)/MoveLogicService.c $(MAIN_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
LogicalEvents.o: $(MAIN_PATH)/LogicalEvents.c $(MAIN_PATH)/LogicalEvents.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c	

SelectionWindow.o: $(MAIN_PATH)/SelectionWindow.c $(MAIN_PATH)/SelectionWindow.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)	
	
GeneralGameWindow.o: $(MAIN_PATH)/GeneralGameWindow.c $(MAIN_PATH)/GeneralGameWindow.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)	

MainMenu.o: $(MAIN_PATH)/MainMenu.c $(MAIN_PATH)/MainMenu.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
WorldSelection.o: $(MAIN_PATH)/WorldSelection.c $(MAIN_PATH)/WorldSelection.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
ChooseType.o: $(MAIN_PATH)/ChooseType.c $(MAIN_PATH)/ChooseType.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
ChooseSkill.o: $(MAIN_PATH)/ChooseSkill.c $(MAIN_PATH)/ChooseSkill.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
GamePlay.o: $(MAIN_PATH)/GamePlay.c $(MAIN_PATH)/GamePlay.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)

GameEditor.o: $(MAIN_PATH)/GameEditor.c $(MAIN_PATH)/GameEditor.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Error.o: $(MAIN_PATH)/Error.c $(MAIN_PATH)/Error.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
GUIStatesFactory.o: $(MAIN_PATH)/GUIStatesFactory.c $(MAIN_PATH)/GUIStatesFactory.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
GameLogicServiceTest.o: $(TEST_PATH)/GameLogicServiceTest.c $(MAIN_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/GameLogicServiceTest.c
	
GameLogicServiceTest: GameLogicServiceTest.o MoveLogicService.o BoardPoint.o BoardUtils.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o GameLogicService.o GameModel.o GameConfigModel.o
	gcc -o $@ $^ $(CFLAGS)
	
EvaluationTest.o: $(TEST_PATH)/EvaluationTest.c $(MAIN_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/EvaluationTest.c
	
EvaluationTest: EvaluationTest.o MoveLogicService.o BoardUtils.o BoardPoint.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o GameLogicService.o GameModel.o GameConfigModel.o
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

#Game Main Program
CatAndMouse.o : $(MAIN_PATH)/CatAndMouse.c $(MAIN_PATH)/CatAndMouse.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)

CatAndMouse: $(MAIN_O_FILES) $(GUI_O_FILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_EXEC_FLAGS)

