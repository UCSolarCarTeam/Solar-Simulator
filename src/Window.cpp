#include <iostream>

#include <GL/glew.h>

#include "Window.h"

Window::Window(int width, int height, const std::string& title)
{
    initSDL();
    
    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); //SDL takes in a C string
    glContext_ = SDL_GL_CreateContext(window_);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cerr << "An error occured while initializing Glew." << std::endl;
    }
    isClosed_ = false;
}

void Window::Clear(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
	//glClear(GL_COLOR_BUFFER_BIT); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


bool Window::IsClosed()
{
    return isClosed_;
}

Window::~Window()
{
    SDL_GL_DeleteContext(glContext_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::initSDL()
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

void Window::Update() //swaps buffers
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