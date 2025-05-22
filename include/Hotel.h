#ifndef HOTEL_H
#define HOTEL_H

#include <string>

class Hotel {
private:
    std::string name;
    int roomsAvailable;

public:
    Hotel(const std::string& hotelName, int rooms);

    void bookRoom();
    void cancelBooking();
    int getAvailableRooms() const;
};

#endif
