# 209294768 sagitmalka10@gmail.com
CXX = g++
CXXFLAGS = -std=c++11

VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

EXEC = test_main

SRCS = test_main.cpp Complex.cpp

HEADERS = tree.hpp Complex.hpp doctest.h

OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)


valgrind: $(EXEC)
	valgrind $(VALGRIND_FLAGS) ./$(EXEC)

.PHONY: all clean valgrind
