#pragma once
#include <vector>
#include <string>

using namespace std;

class Booking {
public:

    // == Core Booking Data ==
    string bookingId;
    int roomId;
    string guestName;
    string checkIn;
    string checkOut;

    // == My Constructors ==
    Booking();
    Booking(const string& bookingId, int roomId, const string& guestName,
            const string& checkIn, const string& checkOut);

    // === Booking Data File I/O ===
    static void loadBookings();        // Load from CSV
    static void saveBookings();        // Save to CSV

    // === Guest Booking Actions ===
    static void bookRoom();            // Create a new booking
    static void cancelBooking();       // Cancel a booking by ID
    static void displayBookings();     // Show all current bookings

private:
    static vector<Booking> bookings;   // In-memory list of all bookings
};
