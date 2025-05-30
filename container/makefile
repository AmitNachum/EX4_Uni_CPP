CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
LDFLAGS = 

# Files
TARGET = main
TEST_TARGET = test

SRC = main.cpp
TEST_SRC = test_container.cpp

OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Build main program
main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Build test program with doctest
test: $(TEST_OBJ) my_container.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) my_container.o
	./$(TEST_TARGET)

# Run test with valgrind
valgrind: main
	valgrind --leak-check=full ./main

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
