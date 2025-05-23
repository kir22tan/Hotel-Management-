#include "../include/Hotel.h"
#include "../include/Utils.h"
#include "../include/Room.h"
#include "../include/Booking.h"

#include <iostream>
#include <limits>

using namespace std;

void Hotel::mainMenu() {
    int choice;

    while (true) {
        printBanner();
        cout << "Main Menu:\n";
        cout << "1. Add Room\n";
        cout << "2. View Rooms\n";
        cout << "3. Book Room\n";
        cout << "4. View Bookings\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            cout << "Invalid input. Please enter a number.\n";
            pressEnterToContinue();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();

        switch (choice) {
            case 1:
                Room::addRoom();
                break;
            case 2:
                Room::displayRooms();
                break;
            case 3:
                Booking::bookRoom();
                break;
            case 4:
                Booking::displayBookings();
                break;
            case 5:
                cout << "Thank you for using Hotel Reservation System!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
                break;
        }
    }
}
