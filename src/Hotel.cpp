    #include "Hotel.h"
    #include "Utils.h"

    #include <iostream>

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
        printGreen("5. Manage Room Maintenance\n");  // New option
        printRed("6. Exit\n");  // Changed Exit option number
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

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
                Room::manageMaintenance();  // Call your new maintenance handler here
                break;
            case 6:
                printGreen("Thank you for using Hotel Reservation System!\n");
                return;
            default:
                printRed("Invalid choice. Please try again.\n");
                pressEnterToContinue();
                break;
        }

        clearScreen();
        printBanner();
    }
}

