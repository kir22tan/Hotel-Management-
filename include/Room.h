#pragma once
#include <string>
#include <vector>

using namespace std;

class Room {
public:
    int id;
    string type;
    double price;
    bool isBooked;
    bool isMaintenance;  // New field

    Room();
    Room(int id, const string& type, double price, bool isBooked, bool isMaintenance = false);

    static void addRoom();
    static void displayRooms();
    static bool updateRoomStatus(int roomId, bool bookStatus);
    static bool roomExists(int roomId);
    static vector<Room> getAvailableRooms(const string& desiredType, const string& checkIn, const string& checkOut);
    static void manageMaintenance();  // New method
    static bool isRoomUnderMaintenance(int roomId) ;
};
