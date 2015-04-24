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
MODEL_PATH=src/main/Model
UTILS_PATH=src/main/Utils
SDL_COMPILE_FLAGS=`sdl-config --cflags`
SDL_EXEC_FLAGS=`sdl-config --libs`


all: test MiniMaxDemo ListUtilsDemo CatAndMouse
	
test: WorldFilesServiceTest GameLogicServiceTest EvaluationTest

clean:
	-rm $(EXEC_FILES) $(MAIN_O_FILES) $(GUI_O_FILES) $(TEST_EXEC_FILES) $(TESTS_O_FILES) $(EXTRA_O_FILES) $(EXTRA_EXEC_FILES)
	
######## GUI Files ########

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

######## Model Files ########

WorldFilesService.o: $(MODEL_PATH)/WorldFilesService.c $(MODEL_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
GameModel.o: $(MODEL_PATH)/GameModel.c $(MODEL_PATH)/GameModel.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
GameConfigModel.o: $(MODEL_PATH)/GameConfigModel.c $(MODEL_PATH)/GameConfigModel.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
GameLogicService.o: $(MODEL_PATH)/GameLogicService.c $(MODEL_PATH)/GameLogicService.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c	
	
BoardPoint.o: $(MODEL_PATH)/BoardPoint.c $(MODEL_PATH)/BoardPoint.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c

BoardUtils.o: $(MODEL_PATH)/BoardUtils.c $(MODEL_PATH)/BoardUtils.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
Evaluation.o: $(MODEL_PATH)/Evaluation.c $(MODEL_PATH)/Evaluation.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
MoveLogicService.o: $(MODEL_PATH)/MoveLogicService.c $(MODEL_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c

######## Utils files ########

ListUtils.o: $(UTILS_PATH)/ListUtils.c $(UTILS_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(UTILS_PATH)/$*.c
	
MiniMax.o: $(UTILS_PATH)/MiniMax.c $(UTILS_PATH)/MiniMax.h $(UTILS_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(UTILS_PATH)/$*.c
	
######## Game Windows Files ########

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
	
######## Test Files ########
	
GameLogicServiceTest.o: $(TEST_PATH)/GameLogicServiceTest.c $(MODEL_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/GameLogicServiceTest.c
	
GameLogicServiceTest: GameLogicServiceTest.o MoveLogicService.o BoardPoint.o BoardUtils.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o GameLogicService.o GameModel.o GameConfigModel.o
	gcc -o $@ $^ $(CFLAGS)
	
EvaluationTest.o: $(TEST_PATH)/EvaluationTest.c $(MODEL_PATH)/MoveLogicService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/EvaluationTest.c
	
EvaluationTest: EvaluationTest.o MoveLogicService.o BoardUtils.o BoardPoint.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o GameLogicService.o GameModel.o GameConfigModel.o
	gcc -o $@ $^ $(CFLAGS)

WorldFilesServiceTest.o: $(TEST_PATH)/WorldFilesServiceTest.c $(MODEL_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/WorldFilesServiceTest.c
	
WorldFilesServiceTest: WorldFilesServiceTest.o WorldFilesService.o BoardUtils.o
	gcc -o $@ $^ $(CFLAGS)

######## Demo Files ########

ListUtilsDemo.o : $(MAIN_PATH)/ListUtilsDemo.c $(UTILS_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo.o : $(MAIN_PATH)/MiniMaxDemo.c $(UTILS_PATH)/MiniMax.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo: MiniMaxDemo.o MiniMax.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)
	
ListUtilsDemo: ListUtilsDemo.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)

#Game Main Program
ConsoleMode.o: $(MAIN_PATH)/ConsoleMode.c $(MAIN_PATH)/ConsoleMode.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
CatAndMouse.o : $(MAIN_PATH)/CatAndMouse.c $(MAIN_PATH)/CatAndMouse.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)

CatAndMouse: $(MAIN_O_FILES) $(GUI_O_FILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_EXEC_FLAGS)
	


