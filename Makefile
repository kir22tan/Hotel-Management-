CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

SRC = src/main.cpp src/Hotel.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = hotel_management

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
