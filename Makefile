CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRC = src/Task.cpp src/TaskManager.cpp src/helper_functions.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = todo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)