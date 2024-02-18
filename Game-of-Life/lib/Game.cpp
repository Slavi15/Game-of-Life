#include "Game.h"
#include "GameMenu.h"
#include "Helpers.h"

int gameField[MAX_WIDTH + 1][MAX_HEIGHT + 1] = { 0 };
int bufferField[MAX_WIDTH + 1][MAX_HEIGHT + 1] = { 0 };

void autoPlay(size_t& rows, size_t& columns)
{
	unsigned int N = 0, milliseconds = 0, steps = 0;

	do
	{
		cout << "Enter a number N for number of simulations: ";
		cin >> N;
		cout << "Enter time delay between evolutions (in milliseconds): ";
		cin >> milliseconds;
	} while (hasInputErrors());

	while (steps != N)
	{	
		refreshScreen();

		printMatrix(gameField, rows, columns);

		cout << "Step: " << steps << " of " << N << endl;

		stepForward(rows, columns);

		timeDelay(milliseconds);

		steps++;
	}
}

void stepForward(size_t& rows, size_t& columns)
{
	enlargeField(rows, columns, POSSIBLE_MOVES);

	for (size_t row = 1; row <= rows; row++)
		for (size_t column = 1; column <= columns; column++)
			bufferField[row][column] = isAlive(row, column, columns, rows, POSSIBLE_MOVES) ? 1 : 0;

	copyMatrices(rows, columns);
}

bool shouldEnlargeBottom(size_t rows, size_t columns, size_t directionsLength)
{
	for (size_t column = 1; column <= columns; column++)
		if (!gameField[column][rows] && liveNeighboursCount(column, rows, rows, columns, directionsLength) == 3)
			return true;

	return false;
}

bool shouldEnlargeRight(size_t rows, size_t columns, size_t directionsLength)
{
	for (size_t row = 1; row <= rows; row++)
		if (!gameField[columns + 1][row] && liveNeighboursCount(columns + 1, row, rows, columns, directionsLength) == 3)
			return true;

	return false;
}

bool shouldEnlargeTop(size_t rows, size_t columns, size_t directionsLength)
{
	for (size_t column = 1; column <= columns; column++)
		if (!gameField[column][0] && liveNeighboursCount(column, 0, rows, columns, directionsLength) == 3)
			return true;

	return false;
}

bool shouldEnlargeLeft(size_t rows, size_t columns, size_t directionsLength)
{
	for (size_t row = 1; row <= rows; row++)
		if (!gameField[0][row] && liveNeighboursCount(0, row, rows, columns, directionsLength) == 3)
			return true;

	return false;
}

void shiftRight(size_t positions, size_t& initialColumns)
{
	if (initialColumns + positions >= MAX_WIDTH || positions == 0)
		return;

	for (int column = initialColumns + positions; column >= positions; column--)
		for (size_t row = 0; row < MAX_HEIGHT; row++)
		{
			gameField[column][row] = gameField[column - positions][row];
			bufferField[column][row] = bufferField[column - positions][row];
		}

	initialColumns += positions;
}

void shiftBottom(size_t positions, size_t& initialRows)
{
	if (initialRows + positions >= MAX_HEIGHT || positions == 0)
		return;

	for (int row = initialRows + positions; row >= positions; row--)
		for (size_t column = 0; column < MAX_WIDTH; column++)
		{
			gameField[column][row] = gameField[column][row - positions];
			bufferField[column][row] = bufferField[column][row - positions];
		}

	initialRows += positions;
}

void enlargeField(size_t& initialRows, size_t& initialColumns, size_t directionsLength)
{
	if (shouldEnlargeLeft(initialRows, initialColumns, directionsLength) && initialColumns < MAX_WIDTH)
	{
		++initialColumns;
		shiftRight(1, initialColumns);
	}
	
	if (shouldEnlargeTop(initialRows, initialColumns, directionsLength) && initialRows < MAX_HEIGHT)
	{
		++initialRows;
		shiftBottom(1, initialRows);
	}
	
	if (shouldEnlargeRight(initialRows, initialColumns, directionsLength) && initialColumns < MAX_WIDTH)
		++initialColumns;

	if (shouldEnlargeBottom(initialRows, initialColumns, directionsLength) && initialRows < MAX_HEIGHT)
		++initialRows;
}

unsigned liveNeighboursCount(size_t row, size_t column, size_t fieldWidth, size_t fieldHeight, size_t directionsLength)
{
	unsigned int alive = 0;

	for (size_t moves = 0; moves < directionsLength; moves++)
	{
		size_t newRow = POSSIBLE_DIRECTIONS[moves][0] + row;
		size_t newColumn = POSSIBLE_DIRECTIONS[moves][1] + column;

		if (gameField[newRow][newColumn] == 1)
			alive++;
	}

	return alive;
}

bool isAlive(size_t row, size_t column, size_t fieldWidth, size_t fieldHeight, size_t directionsLength)
{
	unsigned int aliveCount = liveNeighboursCount(row, column, fieldWidth, fieldHeight, directionsLength);

	if (gameField[row][column] == 1 && aliveCount < 2)
		return false;
	else if (gameField[row][column] == 1 && (aliveCount == 2 || aliveCount == 3))
		return true;
	else if (aliveCount > 3)
		return false;
	else if (gameField[row][column] == 0 && aliveCount == 3)
		return true;

	return false;
}

void resizeField(size_t& initialRows, size_t& initialColumns)
{
	cout << "Current game field dimensions: " << initialColumns << " x " << initialRows << endl;

	size_t x = 0, y = 0;

	do
	{
		cout << "Enter new dimensions: ";
		cin >> x >> y;
	} while (hasInputErrors() && !isValidCoordinates(x, y, MAX_WIDTH, MAX_HEIGHT));

	initialRows = y;
	initialColumns = x;
}

void toggleCell(size_t fieldWidth, size_t fieldHeight)
{
	size_t x = 1, y = 1;

	do
	{
		cout << "Enter coordinates: ";
		cin >> x >> y;
	} while (hasInputErrors() && !isValidCoordinates(x, y, MAX_WIDTH, MAX_HEIGHT));

	gameField[y][x] = !gameField[y][x];
	bufferField[y][x] = !bufferField[y][x];
}

void clearField(size_t rows, size_t columns)
{
	for (size_t row = 1; row <= rows; row++)
		for (size_t column = 1; column <= columns; column++)
		{
			gameField[row][column] = 0;
			bufferField[row][column] = 0;
		}
}

void randomizeField(size_t rows, size_t columns)
{
	unsigned int N = 0;

	do
	{
		cout << "Enter a number N for randomization (1 in N probability for alive cell): ";
		cin >> N;
	} while (hasInputErrors());

	srand(time(NULL));

	for (size_t row = 1; row <= rows; row++)
		for (size_t column = 1; column <= columns; column++)
			if (N == 0)
			{
				gameField[row][column] = 0;
				bufferField[row][column] = 0;
			}
			else
			{
				gameField[row][column] = (rand() % N == 0);
				bufferField[row][column] = gameField[row][column];
			}
}

void copyMatrices(size_t rows, size_t columns)
{
	for (size_t row = 1; row <= rows; row++)
		for (size_t column = 1; column <= columns; column++)
			gameField[row][column] = bufferField[row][column];
}

void printMatrix(int matrix[][MAX_HEIGHT + 1], size_t rows, size_t columns)
{
	for (size_t row = 0; row <= rows; row++)
	{
		for (size_t column = 0; column <= columns; column++)
		{		
			if (row > 0 && column > 0)
				matrix[row][column] == 0 ? cout << setw(2) << '-' : cout << setw(2) << '@';
			else if (row == 0)
				column == 1 || column == columns ? cout << column : cout << setw(2) << ' ';
			else if (column == 0)
				row == 1 || row == rows ? cout << row : cout << ' ';
		}

		cout << endl;
	}
}