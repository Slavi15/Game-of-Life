#include "Helpers.h"

bool hasInputErrors()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}

	return false;
}

bool isValidCoordinates(size_t x, size_t y, size_t fieldWidth, size_t fieldHeight)
{
	return x > 0 && y > 0 && x <= fieldWidth && y <= fieldHeight;
}

bool isValidStartMenuInput(unsigned int option)
{
	return option > 0 && option < 4;
}

bool isValidGameMenuInput(unsigned int option)
{
	return option > 0 && option < 9;
}

unsigned int getInput()
{
	unsigned int option = 0;

	do
	{
		cout << "Enter command: ";
		cin >> option;
	} while (hasInputErrors() && (!isValidStartMenuInput(option) || !isValidGameMenuInput(option))); // Checks whether the input option is of correct datatype

	return option;
}

void timeDelay(const int milliseconds)
{
	long pause;
	clock_t now, then;

	pause = milliseconds * (CLOCKS_PER_SEC / 1000);
	now = clock();
	then = clock();

	while ((now - then) < pause) {
		now = clock();
	}
}