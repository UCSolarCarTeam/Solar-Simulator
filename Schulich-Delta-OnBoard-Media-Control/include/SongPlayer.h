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

#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include <ao/ao.h>
#include <mpg123.h>
#include <string>
#include "SongLoader.h"
#include <cstring>
#include <unistd.h>
#include "threadClass.hpp"

#define BITS 8

class SongPlayer : public I_ThreadClass
{
    public:
        SongPlayer();

        int initSongPlayer();
        void closeSongPlayer();

        /*Song Control*/
        int previousSong();
        int nextSong();
        int playPause();
        void changeVolume(double change);

        /*For the time bar*/
        double getCurrentTime();
        double getSongLength();
        double getVolume();
        double getMaxVolume();
        std::string currentSong();

        void songQuit();
    protected:
        void ThreadFunction();

    private: 
        double MAX_VOLUME;

        int freeMusic();
        int loadSong(char* songName);
        SongLoader loader;
        double volume;

        /*mpg123 specific variables*/ 
        unsigned char *buffer;
        size_t buffer_size;
        bool loaded;
        mpg123_handle *mh;
        ao_sample_format format;
        ao_device *dev;
        int channels, encoding;
        long rate;
        bool quitSong;

        /*Modes*/
        enum threadMode { PLAY, NEXT, PREVIOUS, SHUFFLE, PAUSE};
        threadMode mode;
};

#endif /* SONGPLAYER_H */

