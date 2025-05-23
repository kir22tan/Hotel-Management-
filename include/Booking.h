#pragma once
#include <string>
#include <vector>
#include "Room.h"

using namespace std;

class Booking {
public:
    int roomId;
    string customerName;
    string checkInDate;
    string checkOutDate;

    Booking();
    Booking(int roomId, const string& name, const string& in, const string& out);

    static void bookRoom();
    static void displayBookings();
    static bool isRoomBookedDuring(int roomId, const string& desiredCheckIn, const string& desiredCheckOut);
    static vector<Booking> getBookingsForRoom(int roomId);
};
