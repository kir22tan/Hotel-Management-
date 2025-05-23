#include "Booking.h"
#include "Room.h"
#include "Utils.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<Booking> Booking::bookings; // static member definition

Booking::Booking(const string& bookingId, int roomId, const string& guestName,
                 const string& checkIn, const string& checkOut)
    : bookingId(bookingId), roomId(roomId), guestName(guestName), checkIn(checkIn), checkOut(checkOut) {}

// Helper to split CSV line
static vector<string> splitCSVLine(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        result.push_back(token);
    }
    return result;
}

void Booking::loadBookings() {
    bookings.clear();
    ifstream fin("data/bookings.csv");
    if (!fin) {
        printRed("Cannot open bookings.csv\n");
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        vector<string> tokens = splitCSVLine(line);
        if (tokens.size() != 5) continue; // basic validation
        try {
            int roomId = stoi(tokens[1]);
            bookings.emplace_back(tokens[0], roomId, tokens[2], tokens[3], tokens[4]);
        } catch (...) {
            printRed("Error parsing booking line: " + line + "\n");
        }
    }
    fin.close();
}

void Booking::saveBookings() {
    ofstream fout("data/bookings.csv");
    for (const auto& b : bookings) {
        fout << b.bookingId << "," << b.roomId << "," << b.guestName << ","
             << b.checkIn << "," << b.checkOut << "\n";
    }
    fout.close();
}
static string normalizeRoomType(const string& input) {
    if (input.empty()) return "";
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    result[0] = toupper(result[0]);
    return result;
}
#include <algorithm>  // Add this at the top of your Booking.cpp

void Booking::bookRoom() {
    loadBookings();

    printGreen("Enter Guest Name: ");
    string guestName;
    getline(cin, guestName);
    if (guestName.empty()) {
        printRed("Guest name cannot be empty.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Check-in Date (dd-mm-yyyy): ");
    string checkIn;
    getline(cin, checkIn);
    if (!isValidDate(checkIn)) {
        printRed("Invalid check-in date format.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Check-out Date (dd-mm-yyyy): ");
    string checkOut;
    getline(cin, checkOut);
    if (!isValidDate(checkOut)) {
        printRed("Invalid check-out date format.\n");
        pressEnterToContinue();
        return;
    }

    if (convertDateToInt(checkOut) <= convertDateToInt(checkIn)) {
        printRed("Check-out date must be after check-in date.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Room Type to book (e.g., Single, Double, Suite): ");
    string roomType;
    getline(cin, roomType);
    if (roomType.empty()) {
        printRed("Room type cannot be empty.\n");
        pressEnterToContinue();
        return;
    }

    vector<Room> availableRooms = Room::getAvailableRooms(roomType, checkIn, checkOut);

    if (availableRooms.empty()) {
        printRed("No rooms available for the selected type and dates.\n");
        pressEnterToContinue();
        return;
    }

    // Sort availableRooms by price ascending
    std::sort(availableRooms.begin(), availableRooms.end(), [](const Room& a, const Room& b) {
        return a.price < b.price;
    });

    printGreen("\nAvailable Rooms (sorted by price):\n");
    for (const auto& r : availableRooms) {
        printGreen("Room ID: " + to_string(r.id) + ", Type: " + r.type + ", Price: " + to_string(r.price) + "\n");
    }

    printGreen("\nEnter Room ID to book: ");
    string roomIdStr;
    getline(cin, roomIdStr);
    int roomId;
    try {
        roomId = stoi(roomIdStr);
    } catch (...) {
        printRed("Invalid room ID input.\n");
        pressEnterToContinue();
        return;
    }

    bool found = false;
    for (const auto& r : availableRooms) {
        if (r.id == roomId) {
            found = true;
            break;
        }
    }

    if (!found) {
        printRed("Selected room is not available for the given dates.\n");
        pressEnterToContinue();
        return;
    }

    int nextNum = 1;
    if (!bookings.empty()) {
        string lastId = bookings.back().bookingId;
        try {
            nextNum = stoi(lastId.substr(1)) + 1;
        } catch (...) {
            nextNum = bookings.size() + 1;
        }
    }
    stringstream ss;
    ss << "B" << (nextNum < 10 ? "00" : (nextNum < 100 ? "0" : "")) << nextNum;
    string bookingId = ss.str();

    bookings.emplace_back(bookingId, roomId, guestName, checkIn, checkOut);
    saveBookings();

    printGreen("Booking successful! Your Booking ID: " + bookingId + "\n");
    pressEnterToContinue();
}

void Booking::displayBookings() {
    loadBookings();
    if (bookings.empty()) {
        printRed("No bookings found.\n");
        pressEnterToContinue();
        return;
    }

    // Centered heading (assuming 65 character console width)
    cout << "\n";
    cout << string(22, ' ') << "Current Bookings" << "\n\n";

    cout << "BookingID  RoomID  Guest Name               Check-in    Check-out\n";
    cout << "-----------------------------------------------------------------\n";

    for (const auto& b : bookings) {
        char line[100];
        snprintf(line, sizeof(line), "%-10s  %-6d  %-22s  %-10s  %-10s",
                 b.bookingId.c_str(),
                 b.roomId,
                 b.guestName.c_str(),
                 b.checkIn.c_str(),
                 b.checkOut.c_str());
        printGreen(string(line) + "\n");
    }

    pressEnterToContinue();
}


void Booking::cancelBooking() {
    loadBookings();

    if (bookings.empty()) {
        printRed("No bookings to cancel.\n");
        pressEnterToContinue();
        return;
    }

    printGreen("Enter Booking ID to cancel: ");
    string id;
    getline(cin, id);

    auto it = bookings.begin();
    for (; it != bookings.end(); ++it) {
        if (it->bookingId == id) break;
    }

    if (it == bookings.end()) {
        printRed("Booking ID not found.\n");
        pressEnterToContinue();
        return;
    }

    bookings.erase(it);
    saveBookings();

    printGreen("Booking canceled successfully.\n");
    pressEnterToContinue();
}
