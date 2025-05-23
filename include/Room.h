#pragma once //this is my header guard. its better to use this than Ifndef def endif
#include <string>
using namespace std;

class Room {
public:
    int id;
    string type;
    double price;
    bool isBooked;

    Room();
    Room(int id, const string& type, double price, bool isBooked);

    static void addRoom();
    static void displayRooms();
    static bool updateRoomStatus(int roomId, bool bookStatus);
};
