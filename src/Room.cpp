#pragma once
#include "Room.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

const string ROOMS_FILE = "data/rooms.csv";
const string BOOKINGS_FILE = "data/bookings.csv";

Room::Room() : id(0), type(""), price(0), isBooked(false), isMaintenance(false) {}

Room::Room(int id, const string& type, double price, bool isBooked, bool isMaintenance)
    : id(id), type(type), price(price), isBooked(isBooked), isMaintenance(isMaintenance) {}

void Room::loadRooms(vector<Room>& rooms) {
    rooms.clear();
    ifstream file(ROOMS_FILE);
    if (!file) {
        printRed("Cannot open " + ROOMS_FILE + "\n");
        pressEnterToContinue();
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, type, priceStr, bookedStr, maintStr;

        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, type, ',')) continue;
        if (!getline(ss, priceStr, ',')) continue;
        if (!getline(ss, bookedStr, ',')) continue;
        if (!getline(ss, maintStr, ',')) continue;

        int id = stoi(idStr);
        double price = stod(priceStr);
        bool isBooked = (bookedStr == "1");
        bool isMaintenance = (maintStr == "1");

        rooms.emplace_back(id, type, price, isBooked, isMaintenance);
    }
    file.close();
}

void Room::saveRooms(const vector<Room>& rooms) {
    ofstream file(ROOMS_FILE);
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

void Room::updateBookingStatus(vector<Room>& rooms) {
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
    vector<Room> rooms;
    loadRooms(rooms);

    int id;
    string type;
    double price;

    cout << "Enter new room ID (4-digit): ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (roomExists(id)) {
        printRed("Room already exists.\n");
        pressEnterToContinue();
        return;
    }

    cout << "Enter room type: ";
    getline(cin, type);

    cout << "Enter price: ";
    cin >> price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    rooms.emplace_back(id, type, price, false, false);
    saveRooms(rooms);

    printGreen("Room added successfully.\n");
    pressEnterToContinue();
}

void Room::displayRooms() {
    vector<Room> rooms;
    loadRooms(rooms);
    updateBookingStatus(rooms);

    // Sort rooms by type alphabetically and then by price ascending
    sort(rooms.begin(), rooms.end(), [](const Room& a, const Room& b) {
        if (a.type == b.type)
            return a.price < b.price;
        return a.type < b.type;
    });

    printGreen("RoomID\tType\t\tPrice\tBooked\tMaintenance\n");
    printGreen("-------------------------------------------------------\n");
    for (const auto& room : rooms) {
        printf("%04d\t%-10s\t%.2f\t%s\t%s\n",
               room.id,
               room.type.c_str(),
               room.price,
               (room.isBooked ? "Yes" : "No"),
               (room.isMaintenance ? "Yes" : "No"));
    }
    pressEnterToContinue();
}

bool Room::updateRoomStatus(int roomId, bool bookStatus) {
    vector<Room> rooms;
    loadRooms(rooms);

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
    saveRooms(rooms);
    return true;
}

bool Room::roomExists(int roomId) {
    vector<Room> rooms;
    loadRooms(rooms);

    auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) { return r.id == roomId; });
    return it != rooms.end();
}

vector<Room> Room::getAvailableRooms(const string& desiredType, const string& checkIn, const string& checkOut) {
    vector<Room> rooms;
    loadRooms(rooms);
    updateBookingStatus(rooms);

    vector<Room> available;
    for (const auto& room : rooms) {
        if (!room.isBooked && !room.isMaintenance && room.type == desiredType) {
            available.push_back(room);
        }
    }
    return available;
}

void Room::manageMaintenance() {
    vector<Room> rooms;
    loadRooms(rooms);

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

    it->isMaintenance = !it->isMaintenance;
    if (it->isMaintenance) {
        it->isBooked = false; // maintenance rooms can't be booked
        printGreen("Room " + to_string(id) + " marked as under maintenance.\n");
    } else {
        printGreen("Room " + to_string(id) + " removed from maintenance.\n");
    }

    saveRooms(rooms);
    pressEnterToContinue();
}

bool Room::isRoomUnderMaintenance(int roomId) {
    vector<Room> rooms;
    loadRooms(rooms);

    auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& r) { return r.id == roomId; });
    if (it == rooms.end()) return false;

    return it->isMaintenance;
}
