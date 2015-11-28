#OBJS = files to compile
OBJS = src/Main.cpp src/SongLoader.cpp src/SongPlayer.cpp src/MusicBar.cpp include/threadClass.hpp src/videoStream.cpp src/WiringPiButtons.cpp


#CC = compiler used
CC = g++

#COMPLIE_FLAGS = additional flags
COMPILE_FLAGS = -w -g -std=c++0x

LINK_FLAGS = `sdl2-config --cflags` `sdl2-config --libs` `pkg-config opencv --cflags` `pkg-config opencv --libs` -lSDL2_image -lSDL2_ttf -ltiff -lao -lmpg123 -lwiringPi -pthread


#OUTPUT_NAME = final name
OUTPUT_NAME = BackupCamera

#INCLUDE FLAGS
INCLUDE_FLAGS = -Ilib -Iinclude

all :
	 $(CC) $(OBJS) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(COMPILE_FLAGS) -o $(OUTPUT_NAME) -pthread

clean :
	rm BackupCamera

