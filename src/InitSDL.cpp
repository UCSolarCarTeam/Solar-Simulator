#include <iostream>

#include <GL/glew.h>

#include "InitSDL.h"
#include <stdlib.h>  
#include <SDL2/SDL.h>

InitSDL::InitSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //256 different shades of red 
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //Transparency
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //How much data(in bits) to allocate for each pixel
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Space for second window to be drawn on 

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

}

InitSDL::~InitSDL()
{

}

