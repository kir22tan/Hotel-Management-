#pragma once
#include <string>
#include <vector>

using namespace std;

class Booking {
public:
    string bookingId;
    int roomId;
    string guestName;
    string checkIn;
    string checkOut;

    Booking();
    Booking(const string& bookingId, int roomId, const string& guestName, const string& checkIn, const string& checkOut);

    static void loadBookings();
    static void saveBookings();

    static void displayBookings();
    static void bookRoom();
    static void cancelBooking();

private:
    static vector<Booking> bookings;
};
