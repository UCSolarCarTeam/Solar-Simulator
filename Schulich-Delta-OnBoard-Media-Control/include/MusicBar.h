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

#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "SongPlayer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>


class MusicBar
{
    SDL_Surface* surface;
    TTF_Font *songNameFont;
    TTF_Font *timeFont;
    SongPlayer *mPlayer;
    
    void drawSongName();
    void drawSongTime();  
    void drawVolumeBar();
    std::string convertToString(int songIntTime);
    int init();

    int musicbarSurfaceWidth;
    int musicbarSurfaceHeight;
    int longSongNameLocation;
    double songTimeMark;
    bool getTimeInit;
    bool longSongNameInit;

public:
    void update();
    MusicBar(SongPlayer *songPlayer);
    SDL_Surface* returnMusicBar();

};

#endif
