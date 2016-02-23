# Source Files
OBJS = src/*.cpp 

# Compiler
CXX = g++

# Additional Flags
COMPILE_FLAGS = -g -std=c++11 -Werror

# Required Libraries to Link
LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lGLEW -lGL -lGLU -pthread

#Program Name
OUTPUT_NAME = SolarSimulator

# Headers to Include
INCLUDE_FLAGS = -Ilib -Iinclude 

all :
    $(CXX) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) $(LIBS) -o $(OUTPUT_NAME) 

clean :
    rm $(OUTPUT_NAME)
