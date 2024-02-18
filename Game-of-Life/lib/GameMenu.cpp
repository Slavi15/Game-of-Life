#include "GameMenu.h"
#include "Game.h"
#include "Helpers.h"

void startMenu()
{
	bool exitCommand = false;

	do
	{
		refreshScreen();

		cout << "Welcome to Game of Life!" << endl;
		cout << "1. Start New Game" << endl;
		cout << "2. Load file" << endl;
		cout << "3. Exit" << endl;

		unsigned int startMenuOption = getInput();

		switch (startMenuOption)
		{
		case 1:
			gameMenu();
			break;
		case 2:
			break;
		case 3:
		{
			cout << "You have exited successfully!" << endl;
			exitCommand = true;
		}
		break;
		}

	} while (!exitCommand);
}

void gameMenu()
{
	bool exitCommand = false;

	size_t INITIAL_ROWS = 8;
	size_t INITIAL_COLUMNS = 16;

	do
	{
		refreshScreen();

		copyMatrices(INITIAL_ROWS, INITIAL_COLUMNS);
		printMatrix(gameField, INITIAL_ROWS, INITIAL_COLUMNS);

		cout << "1. Auto Play" << endl;
		cout << "2. Step forward" << endl;
		cout << "3. Resize" << endl;
		cout << "4. Toggle cell" << endl;
		cout << "5. Clear" << endl;
		cout << "6. Randomize" << endl;
		cout << "7. Save to file" << endl;
		cout << "8. Exit" << endl;

		unsigned int gameMenuOption = getInput();

		switch (gameMenuOption)
		{
		case 1:
			autoPlay(INITIAL_ROWS, INITIAL_COLUMNS);
			break;
		case 2:
			stepForward(INITIAL_ROWS, INITIAL_COLUMNS);
			break;
		case 3:
			resizeField(INITIAL_ROWS, INITIAL_COLUMNS);
			break;
		case 4:
			toggleCell(MAX_WIDTH, MAX_HEIGHT);
			break;
		case 5:
			clearField(INITIAL_ROWS, INITIAL_COLUMNS);
			break;
		case 6:
			randomizeField(INITIAL_ROWS, INITIAL_COLUMNS);
			break;
		case 7:
			break;
		case 8:
		{
			clearField(INITIAL_ROWS, INITIAL_COLUMNS);
			cout << "You have exited successfully!" << endl;
			exitCommand = true;
		}
		break;
		}

	} while (!exitCommand);
}

void refreshScreen() {
#ifdef _WIN32
	system("CLS");
#else
	system("clear");
#endif
}