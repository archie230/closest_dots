CXX = g++
CXXFLAGS = -g -std=c++17

.PHONY: all clean

OBJECTS = main.o closest_dots.o
TARGET = closest_dots

all: $(TARGET)

closest_dots.o: src/closest_dots.cc
	$(CXX) -c $(CXXFLAGS) $<

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@


clean:
	rm -f $(TARGET) *.o
