OBJS = $(wildcard src/*.cpp) $(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp))

COMPILE_FLAGS = -g -std=c++11 -Werror

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` -lGLEW -lGL -lGLU -pthread

OUTPUT_NAME = run-tests

INCLUDE_FLAGS = -I../src -Ilib

all :
	 $(CXX) -isystem gtest_include -isystem gmock_include $(INCLUDE_FLAGS) $(OBJS) $(LINK_FLAGS) $(COMPILE_FLAGS) libgmock.a -o $(OUTPUT_NAME)

clean :
	rm run-tests
