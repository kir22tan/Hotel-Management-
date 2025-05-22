#include <iostream>
#include "Hotel.h"

int main() {
    Hotel myHotel("Grand Palace", 10);

    std::cout << "Rooms available: " << myHotel.getAvailableRooms() << std::endl;
    myHotel.bookRoom();
    std::cout << "Rooms available after booking: " << myHotel.getAvailableRooms() << std::endl;

    std::cin.get();
    
    return 0;
}
