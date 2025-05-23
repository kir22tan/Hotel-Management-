#pragma once

#include <string>
using namespace std;

class Booking {
public:
    int bookingId;           // new unique ID for each booking
    int roomId;
    string customerName;
    string checkInDate;
    string checkOutDate;

    Booking();
    Booking(int bookingId, int roomId, const string& name, const string& in, const string& out);

    static void bookRoom();
    static void displayBookings();
};
