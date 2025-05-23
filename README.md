
# 🏨 HOT-MAN - Hotel Reservation System | C++ 

A terminal-based **Hotel Reservation System** built in C++ that allows users to:

- Book rooms
- Cancel reservations
- View available rooms
- Manage room types and maintenance
- Store all data in `.csv` files (no external databases needed)

![image](https://github.com/user-attachments/assets/3d8aa13e-6270-420c-a222-d92ecaae1fa4)

---
## 📂 File Structure

```plaintext
Hotel-Management-/
├── data/
│   ├── bookings.csv       # Stores all bookings
│   └── rooms.csv          # Stores room data
├── include/               # .h headers
│   ├── Booking.h      
│   ├── Hotel.h      
│   ├── Room.h      
│   ├── Utils.h      
├── obj/                   # .o object files
├── src/                   # .cpp src codes
│   ├── Booking.cpp      
│   ├── Hotel.cpp      
│   ├── Room.cpp      
│   ├── Utils.cpp      
│   ├── main.cpp           
├── hotel_management.exe   # executable file
├── Makefile              
├── README.md              # This file
└── ...
```

---

## 🛠️ How to Build & Run Using Makefile

### Windows 
0. Clone the repository.
1. Make sure to have MinGW installed.
2. Open a terminal in the project directory.
   ```bash
   cd \Directory-of-this-project
   ```
3. Run:
   ```bash
   mingw32-make
   ```
4. To execute the program:
   ```bash
   hotel_management.exe
   ```
5. Clean the obj files.
   ```bash
   mingw32-make clean
   ```
---

### Linux / macOS
0. Clone the repository.
1. Open a terminal in the project directory.
2. Make sure `make` and `g++` are installed:
   ```bash
   sudo apt install build-essential  # Ubuntu/Debian
   ```
3. Then run:
   ```bash
   make
   ```
4. Execute:
   ```bash
   ./hotel
   ```
5. Clean the obj files.
   ```bash
   make clean
   ```
---



##  Credits

Authored by **Siddharth Gautam**  
GitHub: [@kir22tan](https://github.com/kir22tan)

---
