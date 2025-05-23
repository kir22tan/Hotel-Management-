#include "../include/Utils.h"
#include<bits/stdc++.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush input buffer
    cin.get();
    clearScreen();
}

void printBanner() {
    cout << "=============================================\n";
    cout << "         HOTEL ROOM RESERVATION SYSTEM       \n";
    cout << "=============================================\n\n";
}

bool isValidDate(const string& date) {
    // Basic format check: DD-MM-YYYY
    regex dateFormat(R"(^\d{2}-\d{2}-\d{4}$)");
    if (!regex_match(date, dateFormat)) {
        return false;
    }

    // Extract components
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Leap year check
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && leap) {
        if (day > 29) return false;
    } else {
        if (day > daysInMonth[month - 1]) return false;
    }

    return true;
}
