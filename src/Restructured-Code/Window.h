#ifndef Window_H
#define Window_H

#include <string>

#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;

    void Update();
    bool IsClosed();
    void Clear(float red, float green, float blue, float alpha);

private:
    SDL_Window* window_;
    bool isClosed_;
    SDL_GLContext glContext_;
};

#endif
