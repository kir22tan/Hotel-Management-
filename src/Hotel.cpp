#include "Hotel.h"
#include <iostream>

Hotel::Hotel(const std::string& hotelName, int rooms) : name(hotelName), roomsAvailable(rooms) {}

void Hotel::bookRoom() {
    if (roomsAvailable > 0) {
        roomsAvailable--;
        std::cout << "Room booked successfully!" << std::endl;
    } else {
        std::cout << "No rooms available." << std::endl;
    }
}

void Hotel::cancelBooking() {
    roomsAvailable++;
    std::cout << "Booking canceled." << std::endl;
}

int Hotel::getAvailableRooms() const {
    return roomsAvailable;
}
