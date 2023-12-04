# Makefile for compiling the main.cpp program

CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = main.cpp ../utility/utility.cpp
OBJS = $(SRCS:.cpp=.o)  # Create object file names
TARGET = advent

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
