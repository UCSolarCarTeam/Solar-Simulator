#include <iostream>

#include <GL/glew.h>

#include "Window.h"

Window::Window(int width, int height, const std::string& title)
{
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
