#include <bits/stdc++.h>
#include "Utils.h"
using namespace std;

//encrypted my string date to an int for easier manipulations
// eg: 20.03.2003 would be encrypted as 20030320 = year*1e4 + month*1e2 + day
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

//clearing screen depending on the system
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
}


bool isValidDate(const string& date) {
    
    // my format need : DD-MM-YYYY
    //so i first check if it is a correct format or not
    if(date.size()!=10) return 0;
    for(int i=0;i<(int)date.size();i++){
        if(i==2||i==5){
            if(date[i]!='-') return 0;
        }else{
            if(!isdigit(date[i])) return 0;
        }
    }
    
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    
    //validity only depends on day and month.
    //although i want my reservations to be after 1900 so i kept an extra check
    if (month < 1 || month > 12 || day < 1 || day > 31) return 0;
    if (year < 1900) return 0;
    
    // leap year is 
    // - div by 400 , or
    // - div by 4 and not div by 100
    // ye aisa ek std rule hai scientists-on ne maana banaya hai
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (month == 2 && leap) return day <= 29;
    else return day <= daysInMonth[month - 1];
}

// I was unable to print this one ->


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
