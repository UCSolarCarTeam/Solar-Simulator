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

#include <cv.h>
#include "opencv2/opencv.hpp"
#include "SongLoader.h"
#include "SongPlayer.h"
#include "videoStream.hpp"
#include <MusicBar.h>

//for the rasperry pi
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C" {
    #include <SDL.h>
    #include <SDL_ttf.h>
}
#include <stdio.h>
#include <unistd.h>

#ifdef __amd64__
    #ifndef RUNNINGONINTEL
    #define RUNNINGONINTEL
    #endif
#else
    #ifndef RUNNINGONPI
    #define RUNNINGONPI
    #endif
    #include "WiringPiButtons.hpp"
#endif

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1232

void processEvents();
void signalToQuit();
void close();

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

SDL_Rect videoRect;
SDL_Rect musicBarRect;
int noSongs;

VideoStream backupCamera;

int quit;

SongPlayer musicPlayer;
MusicBar gordonMusic(&musicPlayer);

/***********************************************************************
/*                          SDL functions
/***********************************************************************/
// Initializes SDL window / renderer for use

bool init_SDL()
{
    bool success = true;

    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Video Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                printf("Creating a software renderer instead\n");
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                if (renderer == NULL)
                {
                    printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                    success = false;                    
                    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            }
        }
    }
    return success;
}

bool init_CameraSettings()
{
    int w, h;
    bool success = true;
    SDL_GetWindowSize(window, &w, &h);
    videoRect.x = 0;
    videoRect.y = 0;
    videoRect.w = w;
    videoRect.h = h-50; //change 50 to whatever height we want for the PI cam

    musicBarRect.x = 0;
    musicBarRect.y = h-49;
    musicBarRect.w = w; 
    musicBarRect.h = 49;
    //cameraWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    //cameraHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    //printf("Camera Width %d, Camera Height %d \n",cameraWidth,cameraHeight);
    
    return success;
}


// Shows an individual frame of the supplied video
int show_Camera()
{
    if(backupCamera.imageReady())
    {
        IplImage* img = NULL;
        img = backupCamera.getFrame();
        SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
            img->width,
            img->height,
            img->depth * img->nChannels,
            img->widthStep,
            0xff0000, 0x00ff00, 0x0000ff, 0
            );

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        surface = NULL;
        #ifdef RUNNINGONPI
        SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
        #else
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        #endif
        SDL_RenderCopyEx(renderer, texture, NULL, &videoRect ,0, NULL, flip);
        SDL_DestroyTexture(texture);
        return 1;
    }
    return 0;
}

void processEvents()
{
    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    printf("SDL_QUIT was called\n");
                    signalToQuit();
                    close();
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            printf("Esc was Pressed!\n");
                            signalToQuit();
                            close();
                            break;
                        case SDLK_LEFT:
                            printf("Left arrow was Pressed!\n");
                            musicPlayer.previousSong();
                            break;
                        case SDLK_RIGHT:
                            printf("Right arrow was Pressed!\n");
                            musicPlayer.nextSong();
                            break;
                        case SDLK_UP:
                            musicPlayer.changeVolume(0.02);
                            break;
                        case SDLK_DOWN:
                            musicPlayer.changeVolume(-0.02);
                            break;
                        case SDLK_SPACE:
                            printf("Space was pressed!\n");
                            musicPlayer.playPause();
                    }
            }
        }
}
#ifdef RUNNINGONPI
void processGPIO(WiringPiButtons::Button button)
{
    switch(button)
    {
        case WiringPiButtons::PREVIOUS:
	    musicPlayer.previousSong();
	    break;
	case WiringPiButtons::NEXT:
	    musicPlayer.nextSong();
	    break;
	case WiringPiButtons::VOLUMEUP:
	    musicPlayer.changeVolume(0.02);
	    break;
	case WiringPiButtons::VOLUMEDOWN:
	    musicPlayer.changeVolume(-0.02);
	    break;
	case WiringPiButtons::TOGGLEPLAY:
	    musicPlayer.playPause();
	default:
	    break;
    }
}
#endif

/* Signals all the threads to quit and then waits for the threads */
void signalToQuit()
{
    backupCamera.signalToQuit();
    musicPlayer.songQuit();
}

/* Cleans up and should free everything used in the program*/
void close()
{
    musicPlayer.closeSongPlayer();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    exit(0);
}

int main(int argc, char* argv[])
{
    #ifdef RUNNINGONPI
        WiringPiButtons buttonManager;
    #endif  

    if (!init_SDL())
    {
        fprintf(stderr, "Could not initialize SDL!\n");
        return -1;
    }
    if (!init_CameraSettings())
    {
        printf("Failed to load settings!\n");
        return -1;
    }

    if (musicPlayer.initSongPlayer())
    {
        fprintf(stderr, "No SongLibrary Folder! Not creating Music Thread!\n");
    }
    else 
    {
        musicPlayer.StartThread();
    }
    backupCamera.StartThread();


    while (!quit)
    {
        processEvents();
        #ifdef RUNNINGONPI
        processGPIO(buttonManager.getEvents());
        #endif

        if (show_Camera())
        {
            SDL_Surface* surfaceBar;
            gordonMusic.update();
            surfaceBar = gordonMusic.returnMusicBar();
            #ifdef RUNNINGONPI
            SDL_RendererFlip flip = SDL_RendererFlip((int)SDL_FLIP_HORIZONTAL | (int)SDL_FLIP_VERTICAL);
            #else
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            #endif
            SDL_Texture* textureMusicBar = SDL_CreateTextureFromSurface(renderer, surfaceBar);
            SDL_RenderCopyEx(renderer, textureMusicBar, NULL, &musicBarRect ,0, NULL, flip);
            SDL_DestroyTexture(textureMusicBar);
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }
    }

    musicPlayer.WaitForThreadToExit();
    backupCamera.WaitForThreadToExit();
    return 0;
}
