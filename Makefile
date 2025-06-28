# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Source and object files
SRC = src/main.cpp src/Hotel.cpp src/Room.cpp src/Booking.cpp src/Utils.cpp
OBJ = $(patsubst src/%.cpp,obj/%.o,$(SRC))

# Output executable
EXEC = hotel_management

.PHONY: all clean

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@

# Compilation rule
obj/%.o: src/%.cpp
	if not exist obj (mkdir obj)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Cleanup
clean:
	if exist obj rmdir /s /q obj
	if exist $(EXEC).exe del /q $(EXEC).exe

