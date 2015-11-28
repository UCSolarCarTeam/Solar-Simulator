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

#include "MusicBar.h"

MusicBar::MusicBar(SongPlayer *songPlayer)
{
    mPlayer = songPlayer;
    musicbarSurfaceWidth = 1080;
    musicbarSurfaceHeight = 64;
    longSongNameLocation = 150;
    getTimeInit = false;
    longSongNameInit = false;
    songTimeMark = 0;
    surface = SDL_CreateRGBSurface(0, musicbarSurfaceWidth, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    init();    
}

int MusicBar::init()
{
    int songNameFontSize; 
    int timeFontSize;
    
    songNameFontSize = 45;
    timeFontSize = 25;
    
    if (TTF_Init() !=0)
    {
        fprintf(stderr, "TTF_Init Failed%s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    songNameFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", songNameFontSize);
    if (songNameFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    
    timeFont = TTF_OpenFont("/usr/share/fonts/ArialUni.ttf", timeFontSize);
    if (timeFont == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Failed%s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

void MusicBar::drawSongName()
{
    std::string songName;
    int songStringLength;
    const char * songChar;
    int songWidth;
    int songHeight;

    songName = mPlayer->currentSong();
    songStringLength = songName.length();
    songName = songName.substr(12, songStringLength - 16); // removes SongLibrary/ and .mp3 from songName
    songChar = songName.c_str(); 
    
    double songCurrentTime;
    double songScrollDelay;
    int songScrollSpeed;
    int songStartPoint;
    int songEndPoint;
    int maxSongWidth;
    int shortSongLocation;

    songScrollSpeed = 5;
    songScrollDelay = 3;
    songStartPoint = 150;
    songEndPoint = 850;
    shortSongLocation = 500;
    maxSongWidth = songEndPoint - songStartPoint;

    songCurrentTime = mPlayer->getCurrentTime();
    
    if (songCurrentTime >= 0 && songCurrentTime <= songScrollDelay)
    {
        longSongNameLocation = songStartPoint;
        longSongNameInit = false;
    }

    if (longSongNameLocation >= songEndPoint)
    {
        longSongNameInit = true;
        getTimeInit = false;
    }
   
    if (longSongNameInit == true)
    {  
        if (longSongNameLocation <= songStartPoint)
        {
            if (getTimeInit == false)
            {
                songTimeMark = songCurrentTime;
                getTimeInit = true;
            }   
            if (songCurrentTime < (songTimeMark + songScrollDelay)) 
            {
                longSongNameLocation = songStartPoint;
            }       
        }
    }
    
    // Song Background Box Surface
    SDL_Surface *songBoxSurface;
    songBoxSurface = SDL_CreateRGBSurface(0, maxSongWidth, 52, 32, 0, 0, 0, 0);
    SDL_FillRect(songBoxSurface, NULL, SDL_MapRGB(songBoxSurface->format,35,35,35));
    SDL_Rect songBoxLocation = {songStartPoint, 6, 0, 0};
    SDL_BlitSurface(songBoxSurface, NULL, surface, &songBoxLocation);
    SDL_FreeSurface(songBoxSurface);

    // Song Name Surface
    SDL_Surface *songSurface;
    SDL_Rect songLocation;
    SDL_Color songColor = {255, 255, 255}; 
    songSurface = TTF_RenderUTF8_Blended(songNameFont, songChar, songColor);
    TTF_SizeText(songNameFont, songChar, &songWidth, &songHeight);

    if (songWidth >= maxSongWidth)
    {    
        songLocation = {longSongNameLocation, musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; 
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
        longSongNameLocation = longSongNameLocation - songScrollSpeed;
        if (longSongNameLocation + songWidth < songStartPoint)
        {
            longSongNameLocation = songEndPoint;
        }
    } 
    else 
    {
        songLocation = {shortSongLocation - (songWidth/2), musicbarSurfaceHeight/2 - songHeight/2, 0, 0}; //880 is start of volume bar, 50 is end of current time
        SDL_BlitSurface(songSurface, NULL, surface, &songLocation);
        SDL_FreeSurface(songSurface);
    }
    
    SDL_Surface *leftMaskSurface;
    leftMaskSurface = SDL_CreateRGBSurface(0, songStartPoint, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(leftMaskSurface, NULL, SDL_MapRGB(leftMaskSurface->format,43,43,43));
    SDL_Rect leftMaskLocation = {0,0,0,0};
    SDL_BlitSurface(leftMaskSurface, NULL, surface, &leftMaskLocation);
    SDL_FreeSurface(leftMaskSurface);

    SDL_Surface *rightMaskSurface;
    rightMaskSurface = SDL_CreateRGBSurface(0, musicbarSurfaceWidth - songEndPoint, musicbarSurfaceHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(rightMaskSurface, NULL, SDL_MapRGB(rightMaskSurface->format,43,43,43));
    SDL_Rect rightMaskLocation = {songEndPoint,0,0,0};
    SDL_BlitSurface(rightMaskSurface, NULL, surface, &rightMaskLocation);
    SDL_FreeSurface(rightMaskSurface);
}


std::string MusicBar::convertToString(int songIntTime)
{
    std::string songStringTime;

    std::stringstream convertSongIntTime;
    convertSongIntTime << songIntTime;
    songStringTime = convertSongIntTime.str();

    return songStringTime;
}

void MusicBar::drawSongTime()
{ 
    double songCurrentTime;
    int songCurrentMins;
    int songCurrentSecs;
    double songCurrentPercent;
    int songCurrentIntTime;
 
    std::string songCurrentStrTime;
    std::string songCurrentStrMins;
    std::string songCurrentStrSecs;
    const char * songCurrentCharTime; 

    double songTotalTime;
    int songTotalMins;
    int songTotalSecs;
    int songTotalIntTime;

    std::string songTotalStrTime;
    std::string songTotalStrMins;
    std::string songTotalStrSecs;
    const char * songTotalCharTime;

    int totalTimeWidth;
    int totalTimeHeight;

    songCurrentTime = mPlayer->getCurrentTime();
    songTotalTime = mPlayer->getSongLength();
    
    songCurrentPercent = songCurrentTime / songTotalTime; 
    songCurrentIntTime = songCurrentTime;
    songCurrentMins = songCurrentIntTime / 60; 
    songCurrentSecs = songCurrentIntTime % 60;

    //songTotalTime = songTotalTime - songCurrentTime; // Remove to stop end time increment
    songTotalIntTime = songTotalTime;
    songTotalMins = songTotalTime / 60; 
    songTotalSecs = songTotalIntTime % 60; 
    
    songCurrentStrMins = convertToString(songCurrentMins);
    songCurrentStrSecs = convertToString(songCurrentSecs);
    
    if (songCurrentSecs < 10) 
    {
        songCurrentStrTime = songCurrentStrMins + ":0" + 
                                songCurrentStrSecs;
    }
    else
    {
        songCurrentStrTime = songCurrentStrMins + ":" + songCurrentStrSecs;
    }
    
    songCurrentCharTime = songCurrentStrTime.c_str();

    songTotalStrMins = convertToString(songTotalMins);
    songTotalStrSecs = convertToString(songTotalSecs);
    
    if (songTotalSecs < 10) 
    {
        songTotalStrTime = songTotalStrMins + ":0" + songTotalStrSecs;
    }
    else
    {
        songTotalStrTime = songTotalStrMins + ":" + songTotalStrSecs;
    }

    songTotalCharTime =  songTotalStrTime.c_str();
     
    // SDL CALLS//
    
    SDL_Color songTimeColor = {255, 255, 255};
    
    SDL_Surface *songCurrentTimeSurface;
    songCurrentTimeSurface = TTF_RenderText_Blended(timeFont, songCurrentCharTime, songTimeColor);
    SDL_Rect songCurrentTimeLocation = {0, 4, 0, 0}; 
    SDL_BlitSurface(songCurrentTimeSurface, NULL, surface, &songCurrentTimeLocation);
    SDL_FreeSurface(songCurrentTimeSurface);
    
    SDL_Surface *songTotalTimeSurface;
    songTotalTimeSurface = TTF_RenderText_Blended(timeFont, songTotalCharTime, songTimeColor);
    TTF_SizeText(timeFont, songTotalCharTime, &totalTimeWidth, &totalTimeHeight);
    SDL_Rect songTotalTimeLocation = {musicbarSurfaceWidth - totalTimeWidth, 4, 0}; 
    SDL_BlitSurface(songTotalTimeSurface, NULL, surface, &songTotalTimeLocation);
    SDL_FreeSurface(songTotalTimeSurface);

    SDL_Surface *songTimebarSurface;
    songTimebarSurface = SDL_CreateRGBSurface(0, 0 + songCurrentPercent*musicbarSurfaceWidth, 3, 32, 0, 0, 0, 0); 
    SDL_FillRect(songTimebarSurface, NULL, SDL_MapRGB(songTimebarSurface->format,0,162,255));
    SDL_Rect songTimebarLocation = {0, 0, 0, 0};
    SDL_BlitSurface(songTimebarSurface, NULL, surface, &songTimebarLocation);
    SDL_FreeSurface(songTimebarSurface);
}

void MusicBar::drawVolumeBar()
{
    double songVolumeCurrent;
    double songVolumePercent;
    double songVolumeMax;
    songVolumeMax = 0.4;

    songVolumeCurrent = mPlayer->getVolume();
    
    songVolumePercent = songVolumeCurrent / songVolumeMax;
    
    // Volume Background Bar
    SDL_Surface *volumeBackgroundSurface;
    int volumeBarHeight;
    int volumeBarXLocation;
    int volumeBarYLocation;
    int volumeBarNumber;
    int i;
    int colorGreen;
    int volumeBarHeightIncrement;
    int volumeBarXLocationIncrement;
    int volumeBarYLocationIncrement;
    int greenGradientIncrement;

    volumeBarNumber = 20; 
    volumeBarHeight = 4;
    volumeBarHeightIncrement = 2;
    volumeBarXLocation = 880;
    volumeBarXLocationIncrement = 6;
    volumeBarYLocation = 50;
    volumeBarYLocationIncrement = 2;
    greenGradientIncrement = 8;


    for (i = 0; i < volumeBarNumber; i++)
    {
        volumeBackgroundSurface = SDL_CreateRGBSurface(0,4, volumeBarHeight,32,0,0,0,0);
        SDL_FillRect(volumeBackgroundSurface, NULL, SDL_MapRGB(volumeBackgroundSurface->format,0,0,0));
        SDL_Rect volumeBarLocation = {volumeBarXLocation,volumeBarYLocation,0,0};
        SDL_BlitSurface(volumeBackgroundSurface, NULL, surface, &volumeBarLocation);
        SDL_FreeSurface(volumeBackgroundSurface);

        //Increments for changing bar size
        volumeBarHeight += volumeBarHeightIncrement;
        volumeBarXLocation += volumeBarXLocationIncrement; 
        volumeBarYLocation -= volumeBarYLocationIncrement;
    }

    // Volume bar
    SDL_Surface *volumeSurface;
    
    volumeBarHeight = 4;
    volumeBarXLocation = 880;
    volumeBarYLocation = 50;
    colorGreen = 162;
    songVolumePercent = songVolumePercent * volumeBarNumber - 0.1;

    for (i = 0; i < songVolumePercent; i++) 
    {
        volumeSurface = SDL_CreateRGBSurface(0,4, volumeBarHeight, 32,0,0,0,0); 
        SDL_FillRect(volumeSurface, NULL, SDL_MapRGB(volumeSurface->format,255,colorGreen,0)); 
        SDL_Rect volumeBarLocation = {volumeBarXLocation, volumeBarYLocation, 0, 0}; 
        SDL_BlitSurface(volumeSurface, NULL, surface, &volumeBarLocation);
        SDL_FreeSurface(volumeSurface);
    
        // Increments for changing bar size and gradient
        volumeBarHeight += volumeBarHeightIncrement; 
        colorGreen -= greenGradientIncrement; 
        volumeBarXLocation += volumeBarXLocationIncrement; 
        volumeBarYLocation -= volumeBarYLocationIncrement; 
    }
}

void MusicBar::update()
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,43,43,43)); 
    drawSongName();
    drawSongTime();
    drawVolumeBar();
}

SDL_Surface* MusicBar::returnMusicBar()
{
    return surface;
}














