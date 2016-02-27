#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

#include <SDL2/SDL.h>

class Display
{
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();
    Display(const Display&) = delete;
    void operator=(const Display&) = delete;

    void Update();
    bool IsClosed();
    void Clear(float red, float green, float blue, float alpha);
	unsigned int getWidth();
	unsigned int getHeight();
private:
    SDL_Window* window_;
    bool isClosed_;
    SDL_GLContext glContext_;
	unsigned int width_;
	unsigned int height_;
};

#endif
