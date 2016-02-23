# Source Files
OBJS = src/*.cpp 

# Compiler
CXX = g++

# Additional Flags
COMPILE_FLAGS = -w -g -std=c++0x -Wall

# Required Libraries to Link
LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lGLEW -lGL -lGLU

#Program Name
OUTPUT_NAME = SolarSimulator

# Headers to Include
INCLUDE_FLAGS = -Ilib -Iinclude 

all :
	 $(CXX) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) $(LIBS) -o $(OUTPUT_NAME) -pthread

clean :
	rm hello
