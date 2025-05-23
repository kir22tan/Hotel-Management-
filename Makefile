CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

SRC = src/main.cpp src/Hotel.cpp src/Room.cpp src/Booking.cpp src/Utils.cpp
OBJ = $(patsubst src/%.cpp,obj/%.o,$(SRC))

EXEC = hotel_management

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@

obj/%.o: src/%.cpp
	if not exist obj mkdir obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if exist obj rmdir /s /q obj
	if exist $(EXEC) del $(EXEC)
