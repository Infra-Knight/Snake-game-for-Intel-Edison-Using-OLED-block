CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=spi/spi_port_edison.cpp spi/spi_device_edison.cpp Source.cpp oled/Edison_OLED.cpp gpio/gpio_edison.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=oled_snake

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)