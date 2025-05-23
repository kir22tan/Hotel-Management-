#pragma once
#include <bits/stdc++.h>

using namespace std;

const string COLOR_GREEN = "\033[1;32m";
const string COLOR_RED = "\033[1;31m";
const string COLOR_RESET = "\033[0m";

int convertDateToInt(const string& date);

void printGreen(const string& text);

void printRed(const string& text);

void clearScreen();

void pressEnterToContinue();

void printBanner();

bool isValidDate(const string& date);
