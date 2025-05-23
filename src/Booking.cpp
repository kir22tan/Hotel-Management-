#include "../include/Booking.h"
#include "../include/Room.h"
#include "../include/Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Default constructor
Booking::Booking()
    : bookingId(0), roomId(0), customerName(""), checkInDate(""), checkOutDate("") {}

// Parameterized constructor
Booking::Booking(int bookingId, int roomId, const string& name, const string& in, const string& out)
    : bookingId(bookingId), roomId(roomId), customerName(name), checkInDate(in), checkOutDate(out) {}

// Helper: Convert date string "DD-MM-YYYY" to integer YYYYMMDD for easy comparison
static int dateToInt(const string& date) {
    if (date.size() != 10) return 0;
    // Extract YYYYMMDD as int
    string year = date.substr(6, 4);
    string month = date.substr(3, 2);
    string day = date.substr(0, 2);
    return stoi(year + month + day);
}

// Generate next booking ID by reading last line of bookings.csv
static int generateBookingId() {
    ifstream fin("data/bookings.csv");
    if (!fin) return 1;  // No file means first ID = 1

    string line, lastLine;
    while (getline(fin, line)) {
        if (!line.empty()) lastLine = line;
    }
    fin.close();

    if (lastLine.empty()) return 1;

    stringstream ss(lastLine);
    string idStr;
    getline(ss, idStr, ',');  // bookingId is first field
    int lastId = stoi(idStr);
    return lastId + 1;
}

// Static method to book a room
void Booking::bookRoom() {
    Booking booking;

    cout << "Enter Room ID to book: ";
    cin >> booking.roomId;
    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, booking.customerName);

    cout << "Enter Check-In Date (DD-MM-YYYY): ";
    getline(cin, booking.checkInDate);
    if (!isValidDate(booking.checkInDate)) {
        cout << "Invalid date format. Use DD-MM-YYYY.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Enter Check-Out Date (DD-MM-YYYY): ";
    getline(cin, booking.checkOutDate);
    if (!isValidDate(booking.checkOutDate)) {
        cout << "Invalid date format. Use DD-MM-YYYY.\n";
        pressEnterToContinue();
        return;
    }

    // Validate that check-in < check-out
    if (dateToInt(booking.checkInDate) >= dateToInt(booking.checkOutDate)) {
        cout << "Check-Out date must be after Check-In date.\n";
        pressEnterToContinue();
        return;
    }

    // Update room status to booked
    bool success = Room::updateRoomStatus(booking.roomId, true);
    if (!success) {
        cout << "Room not available or does not exist.\n";
        pressEnterToContinue();
        return;
    }

    // Assign a unique booking ID
    booking.bookingId = generateBookingId();

    // Append booking to file: bookingId,roomId,customerName,checkInDate,checkOutDate
    ofstream fout("data/bookings.csv", ios::app);
    if (!fout) {
        cerr << "Error: Unable to open bookings.csv for writing.\n";
        pressEnterToContinue();
        return;
    }
    fout << booking.bookingId << ","
         << booking.roomId << ","
         << booking.customerName << ","
         << booking.checkInDate << ","
         << booking.checkOutDate << "\n";
    fout.close();

    cout << "Room booked successfully! Booking ID: " << booking.bookingId << "\n";
    pressEnterToContinue();
}

// Static method to display all bookings
void Booking::displayBookings() {
    ifstream fin("data/bookings.csv");
    if (!fin) {
        cout << "No booking records found.\n";
        pressEnterToContinue();
        return;
    }

    cout << left
         << setw(10) << "BookingID"
         << setw(10) << "RoomID"
         << setw(25) << "Customer"
         << setw(15) << "Check-In"
         << setw(15) << "Check-Out" << "\n";

    cout << string(75, '-') << "\n";

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Booking b;
        string bookingIdStr, roomIdStr;

        getline(ss, bookingIdStr, ',');
        getline(ss, roomIdStr, ',');
        getline(ss, b.customerName, ',');
        getline(ss, b.checkInDate, ',');
        getline(ss, b.checkOutDate);

        b.bookingId = stoi(bookingIdStr);
        b.roomId = stoi(roomIdStr);

        cout << left
             << setw(10) << b.bookingId
             << setw(10) << b.roomId
             << setw(25) << b.customerName
             << setw(15) << b.checkInDate
             << setw(15) << b.checkOutDate << "\n";
    }

    fin.close();
    pressEnterToContinue();
}
