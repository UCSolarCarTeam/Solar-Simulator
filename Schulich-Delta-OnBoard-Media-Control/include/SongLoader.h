/**
 *  Schulich Delta OnBoard Media Control
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the Schulich Delta OnBoard Media Control
 *
 *  The Schulich Delta OnBoard Media Control is free software: 
 *  you can redistribute it and/or modify it under the terms 
 *  of the GNU Affero General Public License as published by 
 *  the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  The Schulich Delta OnBoard Media Control is distributed 
 *  in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 *  without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero 
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General 
 *  Public License along with the Schulich Delta OnBoard Media 
 *  Control.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#ifndef SONG_LOADER_H
#define SONG_LOADER_H
#include <string>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>

//Headers for Randomizing
#include <algorithm>
#include <vector>
#include <random>

class SongLoader
{
    int counter, song, noLibrary; 
    std::vector<std::string> container;
    std::string CurrentSong;
    int readSongNames(); //Read all the songs in the directory

public:
    SongLoader();
    int libraryLoad();
    int shuffleSongNames(); //Shuffle all the songs in the directory
    std::string nextSong(); //Returns Next song
    std::string previousSong(); //Returns Last song
    std::string currentSong(); //Returns the current song
};
#endif
