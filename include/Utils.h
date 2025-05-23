#pragma once
#include <string>
#include <iostream>


#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

using namespace std;

int convertDateToInt(const string& date);
void printGreen(const string& text);
void printRed(const string& text);
void clearScreen();
void pressEnterToContinue();
void printBanner();
bool isValidDate(const string& date);

inline void printGreen(string& msg) {
    cout << COLOR_GREEN << msg << COLOR_RESET;
}
inline void printRed(string& msg) {
    cerr << COLOR_RED << msg << COLOR_RESET;
}