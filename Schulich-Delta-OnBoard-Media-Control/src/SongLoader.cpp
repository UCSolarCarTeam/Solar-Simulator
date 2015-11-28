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

#include "SongLoader.h"


SongLoader::SongLoader()
{
    counter=0;
    song=-1;
    noLibrary = readSongNames();
    shuffleSongNames();
}

int SongLoader::libraryLoad()
{
    return noLibrary;
}

int SongLoader::readSongNames()
{

    DIR *dir;
    struct dirent *ent;
    // Change string to directory with songs in it
    if ((dir = opendir("/home/Music")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {

            if (ent->d_name[0] != '.')
            {
                container.push_back(ent->d_name);
                counter++;
            }

        }
    }
    else
    {
        return 1;
    }

    return 0;
}

int SongLoader::shuffleSongNames()
{
    if (counter != 0)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle ( container.begin(), container.end(), g );
        song=-1;
        return 0;
    }
    return 1;
}


std::string SongLoader::nextSong()
{
    if(song>=(counter-1))
    {
        shuffleSongNames();
        song = 0;
    }
    else
    {
        song++;
    }

    CurrentSong=container[song];

    if (counter == 0)
        return "";
    return ("/home/Music/" + CurrentSong);
}

std::string SongLoader::previousSong()
{
    if(song<=0)
    {
        song=counter-1;
    }
    else
    {
        song--;
    }

    CurrentSong=container[song];

    if (counter == 0)
        return "";
    return ("/home/Music/" + CurrentSong);
}

std::string SongLoader::currentSong()
{
    if (song == -1)
        song++;
    if (counter == 0)
        return "";
    return ("/home/Music/" + container[song]);
}











