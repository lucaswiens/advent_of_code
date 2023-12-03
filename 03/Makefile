# Makefile for compiling the main.cpp program

CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp
TARGET = advent

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
