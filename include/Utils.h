#pragma once
#include <bits/stdc++.h>

using namespace std;

const string COLOR_GREEN = "\033[1;32m";
const string COLOR_RED = "\033[1;31m";
const string COLOR_RESET = "\033[0m";

void printGreen(const string& text);
void printRed(const string& text);

void printLogo();
void printBanner();

int convertDateToInt(const string& date);
bool isValidDate(const string& date);

void clearScreen();
void pressEnterToContinue();
