#include "Utils.h"
#include <iostream>
#include <regex>

using namespace std;

int convertDateToInt(const string& date) {
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    return year * 10000 + month * 100 + day;
}

void printGreen(const string& text) {
    cout << "\033[32m" << text << "\033[0m";
}

void printRed(const string& text) {
    cout << "\033[31m" << text << "\033[0m";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
}

void printBanner() {
    cout << "=============================================\n";
    cout << "         HOTMAN SYSTEM - SIDDHARTH GAUTAM       \n";
    cout << "=============================================\n\n";
}

bool isValidDate(const string& date) {
    regex dateFormat(R"(^\d{2}-\d{2}-\d{4}$)");
    if (!regex_match(date, dateFormat)) return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12 || day < 1) return false;

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month == 2 && leap) return day <= 29;
    else return day <= daysInMonth[month - 1];
}
