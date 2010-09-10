CC=g++
CFLAGS=-c -Wall `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
SOURCES=mbox.cpp main.cpp window.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mbox

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

