#pragma once

#include <iostream>
#include <ctime>

using namespace std;

bool hasInputErrors();

bool isValidCoordinates(size_t x, size_t y, size_t fieldWidth, size_t fieldHeight);

bool isValidStartMenuInput(unsigned int option);

bool isValidGameMenuInput(unsigned int option);

unsigned int getInput();

void timeDelay(const int milliseconds);