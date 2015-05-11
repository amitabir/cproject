CFLAGS=-Wall -g -std=c99 -lm -pedantic-errors
MAIN_O_FILES=WorldFilesService.o MiniMax.o ListUtils.o GameModel.o GameConfigModel.o GameLogicService.o BoardPoint.o \
 	BoardUtils.o Evaluation.o MoveLogicService.o SelectionWindow.o GeneralGameWindow.o MainMenu.o WorldSelection.o ChooseType.o \
 	ChooseSkill.o GamePlay.o GameEditor.o Error.o GUIStatesFactory.o CatAndMouse.o LogicalEvents.o ConsoleMode.o
GUI_O_FILES=BitmapFont.o Widget.o Color.o WidgetFactory.o Button.o Window.o Label.o Panel.o UITree.o
TESTS_O_FILES=WorldFilesServiceTest.o GameLogicServiceTest.o EvaluationTest.o BoardUtilsTest.o
TEST_EXEC_FILES=WorldFilesServiceTest GameLogicServiceTest EvaluationTest BoardUtilsTest
EXEC_FILES=CatAndMouse
EXTRA_O_FILES=MiniMaxDemo.o ListUtilsDemo.o
EXTRA_EXEC_FILES=MiniMaxDemo ListUtilsDemo
TEST_PATH=test
MAIN_PATH=src/main
PRESENTERS_PATH=src/presenters
GUI_PATH=src/gui
MODEL_PATH=src/model
SERVICES_PATH=src/services
SDL_COMPILE_FLAGS=`sdl-config --cflags`
SDL_EXEC_FLAGS=`sdl-config --libs`

all: MiniMaxDemo ListUtilsDemo CatAndMouse
	
test: WorldFilesServiceTest GameLogicServiceTest EvaluationTest BoardUtilsTest

clean:
	-rm $(EXEC_FILES) $(MAIN_O_FILES) $(GUI_O_FILES) $(TEST_EXEC_FILES) $(TESTS_O_FILES) $(EXTRA_O_FILES) $(EXTRA_EXEC_FILES)
	
######## GUI Files ########

BitmapFont.o: $(GUI_PATH)/BitmapFont.c $(GUI_PATH)/BitmapFont.h $(GUI_PATH)/Color.h 
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)

Widget.o: $(GUI_PATH)/Widget.c $(GUI_PATH)/Widget.h $(MAIN_PATH)/ListUtils.h $(GUI_PATH)/BitmapFont.h $(GUI_PATH)/Color.h 
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Color.o: $(GUI_PATH)/Color.c $(GUI_PATH)/Color.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
WidgetFactory.o: $(GUI_PATH)/WidgetFactory.c $(GUI_PATH)/WidgetFactory.h $(GUI_PATH)/Widget.h $(GUI_PATH)/Panel.h $(GUI_PATH)/Label.h \
											 $(GUI_PATH)/Button.h $(GUI_PATH)/Window.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Button.o: $(GUI_PATH)/Button.c $(GUI_PATH)/Button.h $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Window.o: $(GUI_PATH)/Window.c $(GUI_PATH)/Window.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Label.o: $(GUI_PATH)/Label.c $(GUI_PATH)/Label.h $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Panel.o: $(GUI_PATH)/Panel.c $(GUI_PATH)/Panel.h $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
UITree.o: $(GUI_PATH)/UITree.c $(GUI_PATH)/UITree.h $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(GUI_PATH)/$*.c $(SDL_COMPILE_FLAGS)

######## Model Files ########

GameModel.o: $(MODEL_PATH)/GameModel.c $(MODEL_PATH)/GameModel.h $(MODEL_PATH)/GameConfigModel.h $(SERVICES_PATH)/BoardPoint.h  \
									   $(SERVICES_PATH)/BoardUtils.h $(SERVICES_PATH)/MoveLogicService.h 
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c
	
GameConfigModel.o: $(MODEL_PATH)/GameConfigModel.c $(MODEL_PATH)/GameConfigModel.h $(MODEL_PATH)/Constants.h
	gcc -c $(CFLAGS) $(MODEL_PATH)/$*.c

######## Services files ########

WorldFilesService.o: $(SERVICES_PATH)/WorldFilesService.c $(SERVICES_PATH)/WorldFilesService.h $(SERVICES_PATH)/BoardUtils.h $(MODEL_PATH)/Constants.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c
	
GameLogicService.o: $(SERVICES_PATH)/GameLogicService.c $(SERVICES_PATH)/GameLogicService.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c	

BoardPoint.o: $(SERVICES_PATH)/BoardPoint.c $(SERVICES_PATH)/BoardPoint.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c

BoardUtils.o: $(SERVICES_PATH)/BoardUtils.c $(SERVICES_PATH)/BoardUtils.h $(SERVICES_PATH)/BoardPoint.h $(MODEL_PATH)/Constants.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c

Evaluation.o: $(SERVICES_PATH)/Evaluation.c $(SERVICES_PATH)/Evaluation.h $(SERVICES_PATH)/BoardUtils.h $(SERVICES_PATH)/BoardPoint.h \
		 									$(MAIN_PATH)/MiniMax.h $(MAIN_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c

MoveLogicService.o: $(SERVICES_PATH)/MoveLogicService.c $(SERVICES_PATH)/MoveLogicService.h $(MODEL_PATH)/GameModel.h $(SERVICES_PATH)/BoardPoint.h \
		 			$(MAIN_PATH)/MiniMax.h $(MAIN_PATH)/ListUtils.h $(SERVICES_PATH)/BoardUtils.h $(MODEL_PATH)/Constants.h
	gcc -c $(CFLAGS) $(SERVICES_PATH)/$*.c

######## Presenters Files ########

LogicalEvents.o: $(PRESENTERS_PATH)/LogicalEvents.c $(PRESENTERS_PATH)/LogicalEvents.h 
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c	

SelectionWindow.o: $(PRESENTERS_PATH)/SelectionWindow.c $(PRESENTERS_PATH)/SelectionWindow.h $(GUI_PATH)/GUIConstants.h $(MODEL_PATH)/GameConfigModel.h \
														$(MODEL_PATH)/GameModel.h $(GUI_PATH)/UITree.h $(PRESENTERS_PATH)/LogicalEvents.h \
														$(GUI_PATH)/WidgetFactory.h $(GUI_PATH)/Widget.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)	
	
GeneralGameWindow.o: $(PRESENTERS_PATH)/GeneralGameWindow.c $(PRESENTERS_PATH)/GeneralGameWindow.h $(MODEL_PATH)/GameConfigModel.h \
															$(GUI_PATH)/Widget.h $(MODEL_PATH)/GameModel.h $(MODEL_PATH)/Constants.h \
															$(PRESENTERS_PATH)/LogicalEvents.h 
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)

MainMenu.o: $(PRESENTERS_PATH)/MainMenu.c $(PRESENTERS_PATH)/MainMenu.h $(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h \
												$(GUI_PATH)/UITree.h $(PRESENTERS_PATH)/SelectionWindow.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
WorldSelection.o: $(PRESENTERS_PATH)/WorldSelection.c $(PRESENTERS_PATH)/WorldSelection.h $(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h \
												$(GUI_PATH)/UITree.h $(PRESENTERS_PATH)/SelectionWindow.h $(MODEL_PATH)/Constants.h \
												$(SERVICES_PATH)/GameLogicService.h $(SERVICES_PATH)/WorldFilesService.h $(PRESENTERS_PATH)/LogicalEvents.h
			
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
ChooseType.o: $(PRESENTERS_PATH)/ChooseType.c $(PRESENTERS_PATH)/ChooseType.h $(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h \
												$(GUI_PATH)/UITree.h $(PRESENTERS_PATH)/SelectionWindow.h $(MODEL_PATH)/Constants.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
ChooseSkill.o: $(PRESENTERS_PATH)/ChooseSkill.c $(PRESENTERS_PATH)/ChooseSkill.h $(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h \
												$(GUI_PATH)/UITree.h $(PRESENTERS_PATH)/SelectionWindow.h $(MODEL_PATH)/Constants.h \
												$(PRESENTERS_PATH)/LogicalEvents.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)	
	
GamePlay.o: $(PRESENTERS_PATH)/GamePlay.c $(PRESENTERS_PATH)/GamePlay.h $(SERVICES_PATH)/BoardPoint.h $(MODEL_PATH)/GameModel.h \
											$(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h $(GUI_PATH)/UITree.h \
											$(MODEL_PATH)/Constants.h $(SERVICES_PATH)/WorldFilesService.h $(GUI_PATH)/GUIConstants.h \
											$(SERVICES_PATH)/GameLogicService.h $(PRESENTERS_PATH)/GeneralGameWindow.h $(PRESENTERS_PATH)/SelectionWindow.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)

GameEditor.o: $(PRESENTERS_PATH)/GameEditor.c $(PRESENTERS_PATH)/GameEditor.h $(SERVICES_PATH)/BoardPoint.h $(MODEL_PATH)/GameModel.h \
											$(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h $(GUI_PATH)/UITree.h \
											$(MODEL_PATH)/Constants.h $(SERVICES_PATH)/WorldFilesService.h $(GUI_PATH)/GUIConstants.h \
											$(SERVICES_PATH)/GameLogicService.h $(PRESENTERS_PATH)/GeneralGameWindow.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
Error.o: $(PRESENTERS_PATH)/Error.c $(PRESENTERS_PATH)/Error.h $(PRESENTERS_PATH)/GUIState.h $(GUI_PATH)/WidgetFactory.h $(GUI_PATH)/UITree.h \
		 							$(PRESENTERS_PATH)/SelectionWindow.h $(MODEL_PATH)/Constants.h $(GUI_PATH)/GUIConstants.h
	gcc -c $(CFLAGS) $(PRESENTERS_PATH)/$*.c $(SDL_COMPILE_FLAGS)

	
######## Test Files ########
	
GameLogicServiceTest.o: $(TEST_PATH)/GameLogicServiceTest.c $(SERVICES_PATH)/MoveLogicService.h $(SERVICES_PATH)/WorldFilesService.h \
															$(MODEL_PATH)/GameModel.h $(MODEL_PATH)/GameConfigModel.h $(SERVICES_PATH)/GameLogicService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/GameLogicServiceTest.c
	
GameLogicServiceTest: GameLogicServiceTest.o MoveLogicService.o BoardPoint.o BoardUtils.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o GameLogicService.o GameModel.o GameConfigModel.o
	gcc -o $@ $^ $(CFLAGS)
	
EvaluationTest.o: $(TEST_PATH)/EvaluationTest.c $(SERVICES_PATH)/Evaluation.h $(SERVICES_PATH)/BoardUtils.h $(SERVICES_PATH)/BoardPoint.h \
												$(MODEL_PATH)/Constants.h $(MAIN_PATH)/MiniMax.h
	gcc -c $(CFLAGS) $(TEST_PATH)/EvaluationTest.c
	
EvaluationTest: EvaluationTest.o MoveLogicService.o BoardUtils.o BoardPoint.o Evaluation.o MiniMax.o ListUtils.o WorldFilesService.o \
				GameLogicService.o GameModel.o GameConfigModel.o
	gcc -o $@ $^ $(CFLAGS)

WorldFilesServiceTest.o: $(TEST_PATH)/WorldFilesServiceTest.c $(SERVICES_PATH)/WorldFilesService.h
	gcc -c $(CFLAGS) $(TEST_PATH)/WorldFilesServiceTest.c
	
WorldFilesServiceTest: WorldFilesServiceTest.o WorldFilesService.o BoardUtils.o ListUtils.o BoardPoint.o
	gcc -o $@ $^ $(CFLAGS)

BoardUtilsTest.o: $(TEST_PATH)/BoardUtilsTest.c $(SERVICES_PATH)/BoardUtils.h $(SERVICES_PATH)/BoardPoint.h
	gcc -c $(CFLAGS) $(TEST_PATH)/BoardUtilsTest.c
	
BoardUtilsTest: BoardUtilsTest.o BoardUtils.o ListUtils.o BoardPoint.o
	gcc -o $@ $^ $(CFLAGS)

######## Demo Files ########

ListUtilsDemo.o : $(MAIN_PATH)/ListUtilsDemo.c $(MAIN_PATH)/ListUtils.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo.o : $(MAIN_PATH)/MiniMaxDemo.c $(MAIN_PATH)/MiniMax.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMaxDemo: MiniMaxDemo.o MiniMax.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)
	
ListUtilsDemo: ListUtilsDemo.o ListUtils.o
	gcc -o $@ $^ $(CFLAGS)

######## Main Files ########

GUIStatesFactory.o: $(MAIN_PATH)/GUIStatesFactory.c $(MAIN_PATH)/GUIStatesFactory.h $(PRESENTERS_PATH)/MainMenu.h $(PRESENTERS_PATH)/WorldSelection.h \
													$(PRESENTERS_PATH)/ChooseType.h $(PRESENTERS_PATH)/ChooseSkill.h $(PRESENTERS_PATH)/GamePlay.h \
													$(PRESENTERS_PATH)/GameEditor.h $(PRESENTERS_PATH)/Error.h $(PRESENTERS_PATH)/SelectionWindow.h \
													$(PRESENTERS_PATH)/GUIState.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)
	
ListUtils.o: $(MAIN_PATH)/ListUtils.c $(MAIN_PATH)/ListUtils.h
		gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
MiniMax.o: $(MAIN_PATH)/MiniMax.c $(MAIN_PATH)/MiniMax.h $(MAIN_PATH)/ListUtils.h
		gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c

ConsoleMode.o: $(MAIN_PATH)/ConsoleMode.c $(MAIN_PATH)/ConsoleMode.h $(MODEL_PATH)/Constants.h $(SERVICES_PATH)/Evaluation.h \
										  $(SERVICES_PATH)/GameLogicService.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c
	
CatAndMouse.o : $(MAIN_PATH)/CatAndMouse.c $(MAIN_PATH)/CatAndMouse.h $(PRESENTERS_PATH)/GUIState.h $(PRESENTERS_PATH)/LogicalEvents.h \
										   $(MAIN_PATH)/GUIStatesFactory.h $(MAIN_PATH)/ConsoleMode.h
	gcc -c $(CFLAGS) $(MAIN_PATH)/$*.c $(SDL_COMPILE_FLAGS)

CatAndMouse: $(MAIN_O_FILES) $(GUI_O_FILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_EXEC_FLAGS)
