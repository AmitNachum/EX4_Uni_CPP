CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra -Icontainer

# Targets
TARGET = main
TEST_TARGET = test

# Source files
SRC = container/main.cpp
TEST_SRC = tests/test_container.cpp
CONTAINER_SRC = container/my_container.hpp

OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Build main program
main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Build test program with doctest
test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)
	./$(TEST_TARGET)

valgrind: main
	valgrind ./main

# Compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean all
clean:
	rm -f $(TARGET) $(TEST_TARGET) container/*.o tests/*.o
