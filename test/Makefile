OBJS = $(filter-out ../src/main.cpp, $(../src/*.cpp)) ../src/Logic/*.c ../src/Logic/*.cpp ../src/Presenter/*.cpp ../src/Data/*.cpp ../src/View/*.cpp

COMPILE_FLAGS = -g -std=c++11 -Werror

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lGLEW -lGL -lGLU -pthread

OUTPUT_NAME = RunTests

INCLUDE_FLAGS = -I../src -Ilib

all :
	 $(CXX) $(INCLUDE_FLAGS) $(OBJS) $(LINK_FLAGS) $(COMPILE_FLAGS) libgmock.a -o $(OUTPUT_NAME)

clean :
	rm run-tests
