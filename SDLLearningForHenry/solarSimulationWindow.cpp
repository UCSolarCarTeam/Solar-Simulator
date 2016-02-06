// Libraries
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <cmath>


// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

bool init();
void close();
void createMenu();

// In the future should change to textures if need performance
SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect button = {20, 700, BUTTON_WIDTH, BUTTON_HEIGHT};


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Solar Simulation Window", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
    {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 250, 250, 210, 255);
      }
			/*Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
      SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 255  255, 255));
      */
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow( gWindow );
  SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
  gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

/**************************************************************************/

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
        SDL_SetRenderDrawColor(gRenderer, 250, 250, 210, 255);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 220, 220, 190, 255);
        SDL_RenderFillRect(gRenderer, &button);

				//Update the surface
				SDL_RenderPresent(gRenderer);
			}
		}

	//Free resources and close SDL
	close();

	return 0;
}
