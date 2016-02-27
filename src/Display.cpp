#include <iostream>

#include <GL/glew.h>

#include "Display.h"

Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //256 different shades of red
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //Transparency
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //How much data(in bits) to allocate for each pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Space for second window to be drawn on

    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); //SDL takes in a C string
    glContext_ = SDL_GL_CreateContext(window_);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cerr << "An error occured while initializing Glew." << std::endl;
    }
    isClosed_ = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
    SDL_GL_DeleteContext(glContext_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Display::Update() //swaps buffers
{
    SDL_GL_SwapWindow(window_);

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            isClosed_ = true;
        }
    }
}

bool Display::IsClosed()
{
    return isClosed_;
}

void Display::Clear(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
	//glClear(GL_COLOR_BUFFER_BIT); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
