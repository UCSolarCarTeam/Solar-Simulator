# Source Files
OBJS = src/*.cpp src/Logic/*.c src/Logic/*.cpp src/Presenter/*.cpp src/Data/*.cpp src/View/*.cpp

# Additional Flags
COMPILE_FLAGS = -g -std=c++11 -Werror

#Program Name
OUTPUT_NAME = SolarSimulator

# Required Libraries to Link
LINK_FLAGS =`fltk-config --use-gl --use-images --cxxflags --ldflags --ldstaticflags` `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -ltiff 
-lGLEW -lGL -lGLU -pthread

# Headers to Include
INCLUDE_FLAGS = -Ilib -Iinclude 

all :
	$(CXX) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) $(LIBS) -o $(OUTPUT_NAME) 

clean :
	rm $(OUTPUT_NAME)
