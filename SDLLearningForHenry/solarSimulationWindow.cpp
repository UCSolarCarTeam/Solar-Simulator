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

// Function declarations
bool init();
void close();
void createMenu();
void createTexture();
void loadFromRenderedText(std::string buttonText, SDL_Color textColor);

// In the future should change to textures if need performance
SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gSurface = NULL;
TTF_Font* gFont = NULL;
SDL_Texture* gTextTexture = NULL;
SDL_Rect button = {50, 50, BUTTON_WIDTH, BUTTON_HEIGHT};

/*****************************************************************************/

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Solar Simulation Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if(gWindow == NULL) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			// Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 250, 250, 210, 255);

                // Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
		}
	}
	return success;
}

void createTexture() {

    gSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurface, NULL, SDL_MapRGB(gSurface->format, 255, 228, 181));
    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

}

void close() {
	//Destroy texture, renderer, window
	SDL_DestroyTexture(gTexture);
    SDL_DestroyTexture(gTextTexture);
    SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
    SDL_FreeSurface(gSurface);
    TTF_CloseFont(gFont);
	gTexture = NULL;
    gFont = NULL;
    gTextTexture = NULL;
	gRenderer = NULL;
	gWindow = NULL;
    gSurface = NULL;

	//Quit SDL subsystems
    TTF_Quit();
	SDL_Quit();
}

void loadFromRenderedText(std::string buttonText, SDL_Color textColor) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, buttonText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        gTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    }
    SDL_FreeSurface(textSurface);
}


/******************************************************************************/

int main( int argc, char* args[] ) {
	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Main loop flag
		bool quit = false;
        gFont = TTF_OpenFont("SDLLearningForHenry/lazy.ttf", 12);
        if (gFont == NULL) {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        }

        // Create texture
        createTexture();

		//Event handler
		SDL_Event e;

		//While application is running
		while(!quit) {
			//Handle events on queue
			while(SDL_PollEvent(&e) != 0) {
				//User requests quit
				if(e.type == SDL_QUIT) {
					quit = true;
				}
			}

            SDL_SetRenderDrawColor(gRenderer, 250, 250, 210, 255);
            SDL_RenderClear(gRenderer);

            SDL_Color textColor = {0, 0, 0};

            SDL_Rect bottomViewport;
            bottomViewport.x = 0;
            bottomViewport.y = SCREEN_HEIGHT / 1.2;
            bottomViewport.w = SCREEN_WIDTH;
            bottomViewport.h = SCREEN_HEIGHT / 4;

            SDL_RenderSetViewport(gRenderer, &bottomViewport);
            SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

            SDL_SetRenderDrawColor(gRenderer, 220, 220, 190, 255);
            SDL_RenderFillRect(gRenderer, &button);

            loadFromRenderedText("Browse", textColor);
            SDL_RenderCopy(gRenderer, gTextTexture, NULL, &button);

		    //Update the surface
		    SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
