#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void Update();
	bool IsClosed();
	void Clear(float red, float green, float blue, float alpha);

private:
	SDL_Window* window_;
	bool isClosed_;
	SDL_GLContext glContext_;
};

#endif 