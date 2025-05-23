#include <bits/stdc++.h>
#include "Hotel.h"
#include "Room.h"
#include "Booking.h"
#include "Utils.h"

using namespace std;

void Hotel::mainMenu() {
    int choice;

    while (true) {
        clearScreen();
        printBanner();

        printGreen("Main Menu:\n");
        printGreen("1. Add Room\n");
        printGreen("2. View Rooms\n");
        printGreen("3. Book Room\n");
        printGreen("4. View Bookings\n");
        printGreen("5. Cancel Booking\n");
        printGreen("6. Manage Room Maintenance\n");
        printRed("7. Exit\n");

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();
        printBanner();

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
                Booking::cancelBooking();
                break;
            case 6:
                Room::manageMaintenance();
                break;
            case 7:
                printGreen("Thank you for using the Hotel Reservation System!\n");
                pressEnterToContinue();
                return;
            default:
                printRed("Invalid choice. Please try again.\n");
                pressEnterToContinue();
                break;
        }
    }
}
