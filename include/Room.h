#pragma once
#include <vector>
#include <string>

namespace std {

class Room {
public:
    int id;
    std::string type;
    double price;
    bool isBooked;
    bool isMaintenance;

    Room();
    Room(int id, const std::string& type, double price, bool isBooked = false, bool isMaintenance = false);

    static void loadRooms(std::vector<Room>& rooms);
    static void saveRooms(const std::vector<Room>& rooms);
    static void updateBookingStatus(std::vector<Room>& rooms);
    static void addRoom();
    static void displayRooms();
    static bool updateRoomStatus(int roomId, bool bookStatus);
    static bool roomExists(int roomId);
    static std::vector<Room> getAvailableRooms(const std::string& desiredType, const std::string& checkIn, const std::string& checkOut);
    static void manageMaintenance();
    static bool isRoomUnderMaintenance(int roomId);
};

} // namespace std
