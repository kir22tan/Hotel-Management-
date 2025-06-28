#pragma once
#include <bits/stdc++.h>
using namespace std;

const string COLOR_GREEN = "\033[1;32m";
const string COLOR_RED = "\033[1;31m";
const string COLOR_RESET = "\033[0m";

//this i did kyuki mujhe chhiye tha alag alag colors me dikhe
void printGreen(const string& text);
void printRed(const string& text);

void printLogo();
void printBanner();

// smartly , encrypting a date as an integer and checking its validity
int convertDateToInt(const string& date);
bool isValidDate(const string& date);

//basic utils
void clearScreen();
void pressEnterToContinue();
