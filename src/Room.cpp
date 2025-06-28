#include "Room.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

const string ROOMS_FILE = "data/rooms.csv";
const string BOOKINGS_FILE = "data/bookings.csv";

// static member initialization
vector<Room> Room::rooms;

Room::Room() : id(0), type(""), price(0), isBooked(false), isMaintenance(false) {}

Room::Room(int id, const string& type, double price, bool isBooked, bool isMaintenance)
    : id(id), type(type), price(price), isBooked(isBooked), isMaintenance(isMaintenance) {
        //constructor initialiser list ke through maine Room bana diya
    }

void Room::loadRooms() {
    // clears existing vector and fills it with fresh data from CSV
    // aap ise cache refresh type samajhiye...
    rooms.clear();
    
    ifstream file;
    file.open(ROOMS_FILE);

    if (!file) {
        printRed("Cannot open " + ROOMS_FILE + "\n");
        pressEnterToContinue();
        return;
    }

    string line;
    while (getline(file,line)) {
        stringstream ss(line);
        string idStr, type, priceStr, bookedStr, maintStr;

        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, type, ',')) continue;
        if (!getline(ss, priceStr, ',')) continue;
        if (!getline(ss, bookedStr, ',')) continue;
        if (!getline(ss, maintStr, ',')) continue;
        // getline reads from stream passed as first param till delimiter (comma here) and stores in string passed as second param
        int id = stoi(idStr);
        double price = stod(priceStr);
        bool isBooked = (bookedStr == "1");
        bool isMaintenance = (maintStr == "1");

        rooms.emplace_back(id, type, price, isBooked, isMaintenance);
    }
    file.close();
}

void Room::saveRooms() {
    //puri output file ko ham over write krrhe hain
    ofstream file;
    file.open(ROOMS_FILE);

    if (!file) {
        printRed("Cannot open " + ROOMS_FILE + " for writing\n");
        pressEnterToContinue();
        return;
    }
    for (const auto& room : rooms) {
        file << room.id << "," << room.type << "," << room.price << ","
             << (room.isBooked ? "1" : "0") << "," << (room.isMaintenance ? "1" : "0") << "\n";
    }
    file.close();
}

void Room::getBookingStatuses() {
    // unbooks all (except maintenance) and rebooks from bookings.csv

    ifstream file(BOOKINGS_FILE);
    if (!file) {
        printRed("Cannot open " + BOOKINGS_FILE + "\n");
        pressEnterToContinue();
        return;
    }

    // Reset bookings except maintenance rooms
    for (auto& room : rooms) {
        if (!room.isMaintenance)
            room.isBooked = false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string bookingId, roomIdStr, guestName, checkIn, checkOut;

        if (!getline(ss, bookingId, ',')) continue;
        if (!getline(ss, roomIdStr, ',')) continue;
        if (!getline(ss, guestName, ',')) continue;
        if (!getline(ss, checkIn, ',')) continue;
        if (!getline(ss, checkOut, ',')) continue;

        int roomId = stoi(roomIdStr);

        auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) {
            return r.id == roomId;
        });
        if (it != rooms.end() && !it->isMaintenance) {
            it->isBooked = true;
        }
    }
    file.close();
}

void Room::addRoom() {
    loadRooms(); // == refresh karna important h yahan bhi ==

    int id;
    string type;
    double price;

    cout << "Enter new room ID (4-digits): ";
    cin >> id;
    //stream.ignore function - classic - ah yes. 
    // used here to tackle spaces - to flush leftover input (like spaces/newlines) before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (roomExists(id)) {
        printRed("Room already exists.\n");
        pressEnterToContinue();
        return;
    }

    cout << "Enter room type: (Suite/Single/Double) ";
    getline(cin, type);

    cout << "Enter price / night: ";
    cin >> price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    rooms.emplace_back(id, type, price, false, false);
    saveRooms();

    printGreen("Room added successfully.\n");
    pressEnterToContinue();
}

void Room::displayRooms() {
    loadRooms(); // == fresh data load here bhi zaruri hai ==
    getBookingStatuses();

    // Group rooms by type
    vector<string> roomTypes = {"Suite", "Single", "Double"};

    printGreen("RoomID\tType\t\tPrice\tStatus\n");
    printGreen("-------------------------------------------------------\n");

    for (const auto& type : roomTypes) {
        // Filter rooms of this type
        vector<Room> group;
        for (const auto& room : rooms) {
            if (room.type == type) {
                group.push_back(room);
            }
        }

        // Sort by price ascending
        sort(group.begin(), group.end(), [](const Room& a, const Room& b) {
            return a.price < b.price;
        });

        if (group.empty()) continue; // skip if none

        // Print rooms in this group
        for (const auto& room : group) {
            stringstream ss;
            ss << setw(4) << setfill('0') << room.id << "\t"
            << setfill(' ') << left << setw(10) << room.type << "\t"
            << fixed << setprecision(2) << room.price << "\t";


            if (room.isMaintenance) {
                ss << "Maintenance\n";
                printRed(ss.str());
            }
            else if (room.isBooked) {
                ss << "Booked\n";
                cout << ss.str();
            }
            else {
                ss << "Available\n";
                printGreen(ss.str());
            }
        }
        cout << "\n\n"; // 2 blank lines between groups
    }

    pressEnterToContinue();
}


bool Room::updateRoomStatus(int roomId, bool bookStatus) {
    loadRooms(); // == work on latest data before modifying ==

    auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) { return r.id == roomId; });
    if (it == rooms.end()) {
        printRed("Room not found.\n");
        pressEnterToContinue();
        return false;
    }

    if (it->isMaintenance) {
        printRed("Room under maintenance cannot be booked.\n");
        pressEnterToContinue();
        return false;
    }

    it->isBooked = bookStatus;
    saveRooms();
    return true;
}

bool Room::roomExists(int roomId) {
    loadRooms(); // == cache clear, fresh load ==

    auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) { return r.id == roomId; });
    return it != rooms.end();
}

vector<Room> Room::getAvailableRooms(const string& desiredType, const string& checkIn, const string& checkOut) {
    loadRooms(); // == booking status ke pehle fresh room data load hoga ==
    getBookingStatuses();

    vector<Room> available;
    for (const auto& room : rooms) {
        if (!room.isBooked && !room.isMaintenance && room.type == desiredType) {
            available.push_back(room);
        }
    }
    return available;
}

void Room::manageMaintenance() {
    loadRooms(); // == aur yahan bhi fresh load zaruri hai ==
    getBookingStatuses();  // <<<<< Important: sync booking info here!

    int id;
    cout << "Enter room ID to toggle maintenance status: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = find_if(rooms.begin(), rooms.end(), [id](const Room& r) { return r.id == id; });
    if (it == rooms.end()) {
        printRed("Room not found.\n");
        pressEnterToContinue();
        return;
    }

    if (!it->isMaintenance) {
        if (it->isBooked) {
            printRed("Cannot put a booked room under maintenance. Please cancel the booking first.\n");
            pressEnterToContinue();
            return;
        }
        it->isMaintenance = true;
        it->isBooked = false;
        printGreen("Room " + to_string(id) + " marked as under maintenance.\n");
    }
    else {
        it->isMaintenance = false;
        printGreen("Room " + to_string(id) + " removed from maintenance.\n");
    }

    saveRooms();
    pressEnterToContinue();
}
