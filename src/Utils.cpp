#include <bits/stdc++.h>
#include "Utils.h"

using namespace std;

int convertDateToInt(const string& date) {
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    return year * 10000 + month * 100 + day;
}

void printGreen(const string& text) {
    cout << COLOR_GREEN << text << COLOR_RESET;
}

void printRed(const string& text) {
    cerr << COLOR_RED << text << COLOR_RESET;
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
    cin.get();
}

void printBanner() {
    cout << "=============================================\n";
    cout << "         HOTMAN SYSTEM - SIDDHARTH GAUTAM       \n";
    cout << "=============================================\n\n";
}

void printLogo(){
        constexpr auto RESET = "\033[0m";
    constexpr auto RED = "\033[31m";
    constexpr auto CYAN = "\033[36m";
    constexpr auto BOLD = "\033[1m";

    cout << BOLD << RED << R"(
 H     H   O O O   T T T T T          M     M     A      N     N
 H     H  O     O      T              M M M M    A A     N N   N
 H.....H  O     O      T       -      M  M  M   A...A    N  N  N
 H     H  O     O      T              M     M  A     A   N   N N
 H     H   O O O       T              M     M A       A  N     N
)" << RESET << endl;

    // Centered subtitle
    cout << BOLD << CYAN << "  \t   Siddharth - The Arctic Wolf - Gautam" << RESET << endl;
    cout<<"\n";
    // cout<<"\n";
}

// void printLogo() {
//     cout << R"(
//   ██╗  ██╗ ██████╗ ████████╗    ███╗  ███╗ █████╗ ███╗   ██╗
//   ██║  ██║██╔═══██╗╚══██╔══╝    ████╗ ████║██╔══██╗████╗  ██║
//   ███████║██║   ██║   ██║       ██╔████╔██║███████║██╔██╗ ██║
//   ██╔══██║██║   ██║   ██║       ██║╚██╔╝██║██╔══██║██║╚██╗██║
//   ██║  ██║╚██████╔╝   ██║       ██║ ╚═╝ ██║██║  ██║██║ ╚████║
//   ╚═╝  ╚═╝ ╚═════╝    ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝

//          SIDDHARTH - THE ARCTIC WOLF - GAUTAM
//     )" << endl;
// }

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
