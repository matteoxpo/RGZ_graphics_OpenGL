.PHONY: all, clean, rebuild

CC = g++
CFLAGS = -c
GLFLAGS = -lglut -lGL -lGLU

BUILD_PATH = ./build/
SOURCES =  fractal.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = MAIN

all: $(OBJECTS)
	$(CC) $(BUILD_PATH)$(OBJECTS) -o $(BUILD_PATH)$(EXECUTABLE) $(GLFLAGS)
	$(BUILD_PATH)$(EXECUTABLE)


rebuild: clean all

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(BUILD_PATH)$@

clean:
	-rm  $(BUILD_PATH)*