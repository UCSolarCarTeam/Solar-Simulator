#pragma once

#include <string>

#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;

    void initSDL();
    void Update();
    bool IsClosed();
    void Clear(float red, float green, float blue, float alpha);

private:
    SDL_Window* window_;
    bool isClosed_;
    SDL_GLContext glContext_;
};


