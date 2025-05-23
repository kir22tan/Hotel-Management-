#include "../include/Room.h"
#include "../include/Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

Room::Room() : id(0), type(""), price(0.0), isBooked(false) {}

Room::Room(int id, const string& type, double price, bool isBooked)
    : id(id), type(type), price(price), isBooked(isBooked) {}

// Static method to add a new room
void Room::addRoom() {
    Room room;
    cout << "Enter Room ID: ";
    cin >> room.id;
    cin.ignore(); // Clear input buffer

    cout << "Enter Room Type (Single/Double/Suite): ";
    getline(cin, room.type);

    cout << "Enter Price per Night: ";
    cin >> room.price;

    room.isBooked = false;  // New rooms are initially not booked

    ofstream fout("data/rooms.csv", ios::app);
    if (!fout) {
        cerr << "Error: Unable to open rooms.csv for writing.\n";
        return;
    }

    // Write room details in CSV format
    fout << room.id << "," << room.type << "," << room.price << "," << (room.isBooked ? 1 : 0) << "\n";
    fout.close();

    cout << "Room added successfully!\n";
    pressEnterToContinue();
}

// Static method to display all rooms
void Room::displayRooms() {
    ifstream fin("data/rooms.csv");
    if (!fin) {
        cout << "No room records found.\n";
        pressEnterToContinue();
        return;
    }

    cout << left << setw(10) << "ID" << setw(15) << "Type" << setw(10) << "Price" << setw(10) << "Booked" << "\n";
    cout << string(45, '-') << "\n";

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr;

        // Parse CSV line
        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');

        r.id = stoi(idStr);
        r.price = stod(priceStr);
        r.isBooked = (bookedStr == "1");

        cout << left << setw(10) << r.id
             << setw(15) << r.type
             << setw(10) << fixed << setprecision(2) << r.price
             << setw(10) << (r.isBooked ? "Yes" : "No") << "\n";
    }

    fin.close();
    pressEnterToContinue();
}

// Static method to update the booking status of a room by its ID
bool Room::updateRoomStatus(int roomId, bool bookStatus) {
    ifstream fin("data/rooms.csv");
    ofstream temp("data/temp.csv");

    if (!fin || !temp) {
        cerr << "Error: Unable to open room files.\n";
        return false;
    }

    string line;
    bool updated = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr;

        // Parse CSV line
        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');

        r.id = stoi(idStr);
        r.price = stod(priceStr);
        r.isBooked = (bookedStr == "1");

        // Update booking status if room matches
        if (r.id == roomId) {
            r.isBooked = bookStatus;
            updated = true;
        }

        temp << r.id << "," << r.type << "," << r.price << "," << (r.isBooked ? 1 : 0) << "\n";
    }

    fin.close();
    temp.close();

    // Replace original file with updated temp file
    remove("data/rooms.csv");
    rename("data/temp.csv", "data/rooms.csv");

    return updated;
}
