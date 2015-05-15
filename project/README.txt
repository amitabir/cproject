##########################################################################################

README file for the CatAndMouse project (2015)
Partners: Amit Abir & Ofer Doron

##########################################################################################

Our design choices:
	We chose to stick with the MVP design pattern. 
	1) View: 
		Each presenter will create and hold a Window widget. The window widget has a list of children, just like any other widget, thus creating a tree - it is the UITree. When creating a view for a window, we start with the window widget which is always the root of the UITree, and then adding panels as children, then adding buttons and label to those panels. 
		We have four types of widgets: Window, Panel, Button, Label. When drawing the widgets, we go over the UITree in a DFS manner, thus the children widgets will be drawn over the parent widgets. 
		A widget has many properties, such as visible (true/false), clickable (true/false), disabled (true/false) and so on. A widget also has an image surface to display when drawing. A button widget may have several pictures, for the marked and disabled case. 
		We chose not to create images for the text labels. Instead, we have created a BitmapFont helper, which clip character images from a larger font picture, according to the given text. So every text that is not on a button in the game is *not an image*, but a composition of characters.
		We create widgets using the WidgetFactory, which creates the widgets with all properties initialized.
		
	2) Presenter
		There are many windows in the game with a very similar behavior - we call them *Selection* windows. By that we refer to the main menu, all configuration windows before the game (Choose Skill, Choose Type), and also the Load/Save/Edit game which we refer as World Selection. It was important to us to avoid code duplication, so we created the SelectionWindow presenter, which holds all the common logic of all the selection windows. Also, the game editor and the game play are very much alike, so we have created the GeneralGameWindow.
		SelectionWindow:
			The selection windows all behave in a very similar matter - they all have a marked button and we move the marked button using the 'TAB' key, all have back buttons, and all need to handle the configuration of the game. The selection window presenter handles the common events, and handles specific buttons using a function handler transferred to the handle function. Each presenter will implement the buttons handling in a different way (have different buttons), so this is necessary.
		GeneralGameWindow:
			Contains common logic for both the GameEditor and GamePlay windows, such as creating the grid panel and handling common events.
		
		All the selection windows uses most of the common logic in the SelectionWindow code, leaving them pretty thin and focused on the specific window logic. One can find in each one of them a handling method for the specific windows buttons, and that's about it.	
		The GamePlay and GameEditor presenters handles movement of players or other parts of the game on the grid board. 
		All of the windows uses services to handle the 'real' logic, such as advancing the game, reading world files and so on.
			 
	3) Model
		The same as with the gui, we also have the model building blocks: the game model and the game configuration model. The game configuration model contains information about metadata for the game: the skill levels, the players types and the world index. The game model holds a configuration model within, but also holds the game state data - who's turn it is, the number of turns, the board and the positions of the players. 
		We chose to represent the board as two dimensional character array, but holding only the wall tiles within it. The cat, mouse and cheese are all represented by BoardPoints (row, col) so we will not need to search for them every time we need to now their positions.
		Next, we use the building blocks to compose the models we need for the different windows:
		SelectionModel: 
			Used for the configuration before the game, so it holds a configuration model as a member in the struct. Also holds the currently marked button, which is a common property for all the selection windows. 
			The most important aspect of the selection model is the previous model pointer: as we move from one selection window to another, we attach the previous window model to the new model in the previous pointer, thus creating a list of previous model states. When pressing the 'back' button, we take the previous model and restore it as the primary model, freeing the model for the window where we pushed 'back'. 
		GamyPlay:
			For the game play, we simply use the game model as it is, without any extention. It is used to advance the game and keep the state.
		GameEditorModel:
			The editor model is based on the game model, but also has the current marked grid point and the StateID as it might be Create game or Edit game states.
		
##########################################################################################

List of modules:
	main - Contains the main program execute file, the console mode files, the states factory and the utility files ListUitls and MiniMax.
	presenters - These are the presenters that implement the GUIState behavior.
	gui - Contains all the views building blocks (widgets), the GUI handlers like UITree which handles the drawing of the windows and font utils.
	services - Contains all general services which are used from the presenters, like services for accessing world files and calculating points on the board.
	model - Contains the two main models for the application - the game model and the game configuration model. 

##########################################################################################

Utility evaluation function:
	High Level Description: Our evaulation function is not a symmetric one, with a different behaviour for the mouse and the cat. 
		We calculate the BFS shortest distance from the cat to the mouse and from mouse to the cheese. One more useful measure for how much the cat interrupts the mouse getting to the cheese is the difference between the distance from the mouse to cheese and the distance from the mouse to the cheese while ignoring the cat completely, we will call it the "Diff distance". We give different weights to those three parameters, and also taking into account the number of turns and the depth of the tree.
		
	Reasoning: First we will consider the number of turns left. If the mouse can't reach the cheese in the remaining turns, the mouse should simply run away and the cat should only be chasing after the mouse, so the only parameter considered is the distance between the mouse and the cat.
	If the mouse has enough turns to reach the cheese, then all the parameters should be consideres. The cat wants to be close to the mouse (small cat to mous distance), and also to interrupt the way for the mouse, but at a lower priority, so the diff distance will be multiplied by a lower weight.
	The mouse wants to get to the cheese at top priority, so this is the largest weight for the mouse. The second priority is to minimize the diff distance and the third would be to get away from the cat.
	We also change the winning score by taking into account the depth of the tree, which can be calculated using the remaining number of turns. If there are several leafs in the tree that leads to victory - we want the highest one, meaning the one whose "numTurns" variable is the largest.
	
	Running Time: Calculating BFS distance is done in time: O(|V| + |E|). In our case, |V| = n^2 and |E| = O(n^2), so we get O(n^2) complexity. Since this is the only time consuming part of the evaluation, the total complexity is O(n^2).

##########################################################################################
