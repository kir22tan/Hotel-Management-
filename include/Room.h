#pragma once
#include <vector>
#include <string>

using namespace std;

class Room {
public:
    
    // ==  Core Room Data ==
    int id;
    string type;
    double price;
    bool isBooked;
    bool isMaintenance;

    // == My Constructors == 
    Room();
    Room(int id, const string& type, double price, bool isBooked = false, bool isMaintenance = false);

    // === Room Data File I/O ===
    // Load from CSV and  Save to CSV
    static void loadRooms();           
    static void saveRooms();          

    // === Room Booking & Availability ===
    static void getBookingStatuses(); // refresh isBooked flags from bookings.csv
    static bool updateRoomStatus(int roomId, bool bookStatus); // manually change booking flag
    static vector<Room> getAvailableRooms( // available room filter
        const string& desiredType,
        const string& checkIn,
        const string& checkOut
    );
    
    // === Admin Room Management ===
    static void addRoom();            // Add a new room
    static void displayRooms();       // Display all rooms
    static void manageMaintenance();  // Toggle maintenance status
    static bool roomExists(int roomId);                            
    static bool isRoomUnderMaintenance(int roomId); // [UNUSED]

private:
    static vector<Room> rooms;  // private internal static storage
};
