#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr size_t MAX_WIDTH = 70;
constexpr size_t MAX_HEIGHT = 70;

constexpr size_t POSSIBLE_MOVES = 8;
constexpr size_t PAIR_SIZE = 2;

const int POSSIBLE_DIRECTIONS[POSSIBLE_MOVES][PAIR_SIZE] = {
	{0, 1}, {1, 0}, {0, -1}, {-1, 0},
	{1, 1}, {-1, -1}, {1, -1}, {-1, 1}
};

extern int gameField[MAX_WIDTH + 1][MAX_HEIGHT + 1];
extern int bufferField[MAX_WIDTH + 1][MAX_HEIGHT + 1];

void autoPlay(size_t& rows, size_t& columns);

void stepForward(size_t& rows, size_t& columns);

bool shouldEnlargeRight(size_t rows, size_t columns, size_t directionsLength);

bool shouldEnlargeBottom(size_t rows, size_t columns, size_t directionsLength);

bool shouldEnlargeLeft(size_t rows, size_t columns, size_t directionsLength);

bool shouldEnlargeTop(size_t rows, size_t columns, size_t directionsLength);

void shiftRight(size_t positions, size_t& initialColumns);

void shiftBottom(size_t positions, size_t& initialRows);

void enlargeField(size_t& initialRows, size_t& initialColumns, size_t directionsLength);

unsigned liveNeighboursCount(size_t row, size_t column, size_t fieldWidth, size_t fieldHeight, size_t directionsLength);

bool isAlive(size_t row, size_t column, size_t fieldWidth, size_t fieldHeight, size_t directionsLength);

void resizeField(size_t& initialRows, size_t& initialColumns);

void toggleCell(size_t fieldWidth, size_t fieldHeight);

void clearField(size_t rows, size_t columns);

void randomizeField(size_t rows, size_t columns);

void copyMatrices(size_t rows, size_t columns);

void printMatrix(int matrix[][MAX_HEIGHT + 1], size_t rows, size_t columns);