#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	void Update();
	bool IsClosed();
	void Clear(float red, float green, float blue, float alpha);
	virtual ~Display();
protected:
private:
	Display(const Display& other);
	void operator=(const Display& other);
	SDL_Window* m_window;
	bool m_isClosed;
};

#endif 