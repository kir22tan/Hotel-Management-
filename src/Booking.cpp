#include "Booking.h"
#include "Room.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

Booking::Booking() {}

Booking::Booking(int roomId, const string& name, const string& in, const string& out)
    : roomId(roomId), customerName(name), checkInDate(in), checkOutDate(out) {}

void Booking::bookRoom() {
    Booking b;

    printGreen("Enter Room ID to book: ");
    cin >> b.roomId;
    cin.ignore();

    if (!Room::roomExists(b.roomId)) {
        printRed("Room ID does not exist.\n");
        pressEnterToContinue();
        return;
    }

    if (Room::isRoomUnderMaintenance(b.roomId)) {
        printRed("Room is currently under maintenance and cannot be booked.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Customer Name: ");
    getline(cin, b.customerName);

    printGreen("Enter Check-In Date (DD-MM-YYYY): ");
    getline(cin, b.checkInDate);
    if (!isValidDate(b.checkInDate)) {
        printRed("Invalid Check-In date format. Use DD-MM-YYYY.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Check-Out Date (DD-MM-YYYY): ");
    getline(cin, b.checkOutDate);
    if (!isValidDate(b.checkOutDate)) {
        printRed("Invalid Check-Out date format. Use DD-MM-YYYY.\n");
        pressEnterToContinue();
        return;
    }

    if (convertDateToInt(b.checkInDate) >= convertDateToInt(b.checkOutDate)) {
        printRed("Check-Out date must be after Check-In date.\n");
        pressEnterToContinue();
        return;
    }

    if (isRoomBookedDuring(b.roomId, b.checkInDate, b.checkOutDate)) {
        printRed("Room is already booked for the selected dates.\n");
        pressEnterToContinue();
        return;
    }

    ofstream fout("data/bookings.csv", ios::app);
    if (!fout) {
        printRed("Failed to open bookings.csv.\n");
        pressEnterToContinue();
        return;
    }

    fout << b.roomId << "," << b.customerName << "," << b.checkInDate << "," << b.checkOutDate << "\n";
    fout.close();

    Room::updateRoomStatus(b.roomId, true);

    printGreen("Room booked successfully!\n");
    pressEnterToContinue();
}

void Booking::displayBookings() {
    ifstream fin("data/bookings.csv");
    if (!fin) {
        printRed("No booking records found.\n");
        pressEnterToContinue();
        return;
    }

    cout << left << setw(10) << "Room ID" << setw(20) << "Customer" << setw(15) << "Check-In" << setw(15) << "Check-Out" << "\n";
    cout << "-------------------------------------------------------------------\n";

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Booking b;
        getline(ss, line, ','); b.roomId = stoi(line);
        getline(ss, b.customerName, ',');
        getline(ss, b.checkInDate, ',');
        getline(ss, b.checkOutDate, ',');

        cout << left << setw(10) << b.roomId << setw(20) << b.customerName << setw(15) << b.checkInDate << setw(15) << b.checkOutDate << "\n";
    }

    fin.close();
    pressEnterToContinue();
}

bool Booking::isRoomBookedDuring(int roomId, const string& desiredCheckIn, const string& desiredCheckOut) {
    ifstream fin("data/bookings.csv");
    if (!fin) return false;

    string line;
    int desiredStart = convertDateToInt(desiredCheckIn);
    int desiredEnd = convertDateToInt(desiredCheckOut);

    while (getline(fin, line)) {
        stringstream ss(line);
        Booking b;

        getline(ss, line, ','); b.roomId = stoi(line);
        getline(ss, b.customerName, ',');
        getline(ss, b.checkInDate, ',');
        getline(ss, b.checkOutDate, ',');

        if (b.roomId != roomId) continue;

        int bookedStart = convertDateToInt(b.checkInDate);
        int bookedEnd = convertDateToInt(b.checkOutDate);

        // Check if desired booking overlaps with existing booking
        if (!(desiredEnd <= bookedStart || desiredStart >= bookedEnd)) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

vector<Booking> Booking::getBookingsForRoom(int roomId) {
    vector<Booking> bookings;
    ifstream fin("data/bookings.csv");
    if (!fin) return bookings;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Booking b;
        getline(ss, line, ','); b.roomId = stoi(line);
        getline(ss, b.customerName, ',');
        getline(ss, b.checkInDate, ',');
        getline(ss, b.checkOutDate, ',');

        if (b.roomId == roomId) {
            bookings.push_back(b);
        }
    }
    fin.close();
    return bookings;
}
