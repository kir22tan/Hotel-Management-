#include "Room.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

Room::Room() : id(0), price(0.0), isBooked(false), isMaintenance(false) {}

Room::Room(int id, const string& type, double price, bool isBooked, bool isMaintenance)
    : id(id), type(type), price(price), isBooked(isBooked), isMaintenance(isMaintenance) {}

void Room::addRoom() {
    Room room;

    printGreen("Enter Room ID: ");
    cin >> room.id;
    cin.ignore();

    printGreen("Enter Room Type (Single/Double/Suite): ");
    getline(cin, room.type);

    printGreen("Enter Price per Night: ");
    cin >> room.price;
    room.isBooked = false;
    room.isMaintenance = false;

    if (roomExists(room.id)) {
        printRed("Room ID already exists!\n");
        pressEnterToContinue();
        return;
    }

    ofstream fout("data/rooms.csv", ios::app);
    if (!fout) {
        printRed("Error opening rooms.csv for writing.\n");
        pressEnterToContinue();
        return;
    }

    fout << room.id << "," << room.type << "," << room.price << "," 
         << (room.isBooked ? "1" : "0") << "," << (room.isMaintenance ? "1" : "0") << "\n";
    fout.close();

    printGreen("Room added successfully!\n");
    pressEnterToContinue();
}

void Room::displayRooms() {
    ifstream fin("data/rooms.csv");
    if (!fin) {
        printRed("No room records found.\n");
        pressEnterToContinue();
        return;
    }

    cout << left << setw(10) << "ID" << setw(15) << "Type" << setw(10) << "Price" 
         << setw(10) << "Booked" << setw(15) << "Maintenance" << "\n";
    cout << "-------------------------------------------------------------\n";

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr, maintenanceStr;

        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');
        getline(ss, maintenanceStr, ',');

        try {
            r.id = stoi(idStr);
            r.price = stod(priceStr);
            r.isBooked = (bookedStr == "1" || bookedStr == "true");
            r.isMaintenance = (maintenanceStr == "1" || maintenanceStr == "true");
        } catch (...) {
            // Skip invalid record
            continue;
        }

        cout << left << setw(10) << r.id 
             << setw(15) << r.type 
             << setw(10) << fixed << setprecision(2) << r.price 
             << setw(10) << (r.isBooked ? "Yes" : "No") 
             << setw(15) << (r.isMaintenance ? "Under Maintenance" : "Available") << "\n";
    }

    pressEnterToContinue();
}

bool Room::updateRoomStatus(int roomId, bool bookStatus) {
    ifstream fin("data/rooms.csv");
    ofstream temp("data/temp.csv");

    if (!fin || !temp) {
        printRed("Error opening room files.\n");
        return false;
    }

    string line;
    bool updated = false;

    while (getline(fin, line)) {
        if (line.empty()) {
            temp << "\n";
            continue;
        }

        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr, maintenanceStr;

        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');
        getline(ss, maintenanceStr, ',');

        try {
            r.id = stoi(idStr);
            r.price = stod(priceStr);
            r.isBooked = (bookedStr == "1" || bookedStr == "true");
            r.isMaintenance = (maintenanceStr == "1" || maintenanceStr == "true");
        } catch (...) {
            // Write original line to temp if parsing fails to avoid data loss
            temp << line << "\n";
            continue;
        }

        if (r.id == roomId) {
            r.isBooked = bookStatus;
            updated = true;
        }

        temp << r.id << "," << r.type << "," << r.price << "," 
             << (r.isBooked ? "1" : "0") << "," << (r.isMaintenance ? "1" : "0") << "\n";
    }

    fin.close();
    temp.close();

    remove("data/rooms.csv");
    rename("data/temp.csv", "data/rooms.csv");

    return updated;
}

bool Room::roomExists(int roomId) {
    ifstream fin("data/rooms.csv");
    if (!fin) return false;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr;

        getline(ss, idStr, ',');
        try {
            if (stoi(idStr) == roomId) {
                return true;
            }
        } catch (...) {
            continue;
        }
    }
    return false;
}

vector<Room> Room::getAvailableRooms(const string& desiredType, const string& checkIn, const string& checkOut) {
    vector<Room> availableRooms;
    ifstream fin("data/rooms.csv");
    if (!fin) return availableRooms;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr, maintenanceStr;

        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');
        getline(ss, maintenanceStr, ',');

        try {
            r.id = stoi(idStr);
            r.price = stod(priceStr);
            r.isBooked = (bookedStr == "1" || bookedStr == "true");
            r.isMaintenance = (maintenanceStr == "1" || maintenanceStr == "true");
        } catch (...) {
            continue;
        }

        if (r.type != desiredType) continue;

        if (!r.isBooked && !r.isMaintenance) {
            availableRooms.push_back(r);
        }
    }
    return availableRooms;
}

void Room::manageMaintenance() {
    int roomId;
    printGreen("Enter Room ID to update maintenance status: ");
    cin >> roomId;

    if (!roomExists(roomId)) {
        printRed("Room ID does not exist!\n");
        pressEnterToContinue();
        return;
    }

    ifstream fin("data/rooms.csv");
    ofstream temp("data/temp.csv");
    if (!fin || !temp) {
        printRed("Error opening files.\n");
        pressEnterToContinue();
        return;
    }

    string line;
    bool updated = false;

    while (getline(fin, line)) {
        if (line.empty()) {
            temp << "\n";
            continue;
        }

        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr, maintenanceStr;

        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');
        getline(ss, maintenanceStr, ',');

        try {
            r.id = stoi(idStr);
            r.price = stod(priceStr);
            r.isBooked = (bookedStr == "1" || bookedStr == "true");
            r.isMaintenance = (maintenanceStr == "1" || maintenanceStr == "true");
        } catch (...) {
            temp << line << "\n";
            continue;
        }

        if (r.id == roomId) {
            cout << "Current maintenance status: " << (r.isMaintenance ? "Under Maintenance" : "Available") << "\n";
            printGreen("Set maintenance status (1 = Under Maintenance, 0 = Available): ");
            int status;
            cin >> status;
            r.isMaintenance = (status == 1);
            updated = true;
        }

        temp << r.id << "," << r.type << "," << r.price << "," 
             << (r.isBooked ? "1" : "0") << "," << (r.isMaintenance ? "1" : "0") << "\n";
    }

    fin.close();
    temp.close();

    remove("data/rooms.csv");
    rename("data/temp.csv", "data/rooms.csv");

    if (updated) {
        printGreen("Maintenance status updated successfully.\n");
    } else {
        printRed("Failed to update maintenance status.\n");
    }
    pressEnterToContinue();
}

bool Room::isRoomUnderMaintenance(int roomId) {
    ifstream fin("data/rooms.csv");
    if (!fin) return false;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Room r;
        string idStr, priceStr, bookedStr, maintenanceStr;

        getline(ss, idStr, ',');
        getline(ss, r.type, ',');
        getline(ss, priceStr, ',');
        getline(ss, bookedStr, ',');
        getline(ss, maintenanceStr, ',');

        try {
            r.id = stoi(idStr);
            r.price = stod(priceStr);
            r.isBooked = (bookedStr == "1" || bookedStr == "true");
            r.isMaintenance = (maintenanceStr == "1" || maintenanceStr == "true");
        } catch (...) {
            continue;
        }

        if (r.id == roomId) {
            return r.isMaintenance;
        }
    }
    return false;
}
