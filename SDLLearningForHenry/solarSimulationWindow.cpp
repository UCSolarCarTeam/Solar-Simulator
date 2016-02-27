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
void handleEvent(SDL_Event* e);
SDL_Rect createButton(int x, int y);

// In the future should change to textures if need performance
SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gSurface = NULL;
TTF_Font* gFont = NULL;
SDL_Texture* gTextTexture = NULL;

/*****************************************************************************/

bool init() {
	//Initialization flag
	bool success = true;
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

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
    SDL_FreeSurface(gSurface);
    TTF_CloseFont(gFont);
    SDL_DestroyTexture(gTextTexture);
	SDL_DestroyTexture(gTexture);
    SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
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
    if (gTextTexture != NULL) {
        SDL_DestroyTexture(gTextTexture);
        gTextTexture = NULL;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, buttonText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        gTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (gTextTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
    }
    SDL_FreeSurface(textSurface);
}

SDL_Rect createButton(int x, int y) {
    SDL_Rect button = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
    return button;
}

void handleEvent(SDL_Event* e, int buttonX, int buttonY) {
    if (e-> type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
            // Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            // Check if mouse is in button
            bool inside = true;

            // Checks if mouse is out of button
            if (x < buttonX){
                inside = false;
            } else if (x > buttonX + BUTTON_WIDTH) {
                inside = false;
            } else if (y < (buttonY + SCREEN_HEIGHT / 1.2)) {
                 inside = false;
            } else if (y > (buttonY + SCREEN_HEIGHT / 1.2) + BUTTON_HEIGHT) {
                inside = false;
            }

            if (inside) {
                switch(e->type) {
                    case SDL_MOUSEMOTION:
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                    printf("I am being pressed.\n");
                    break;

                    case SDL_MOUSEBUTTONUP:
                    printf("I am being released.\n");
                    break;
                }
            }

        }
}


/******************************************************************************/

int main( int argc, char* args[] ) {
	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Main loop flag
		bool quit = false;

        // Initialize variables (will migrate to classes later :P)
        int browseButtonX = 50;
        int browseButtonY = 50;
        SDL_Rect browseButton = createButton(browseButtonX, browseButtonY);
        gFont = TTF_OpenFont("SDLLearningForHenry/lazy.ttf", 12);
        if (gFont == NULL) {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        }
        // Create texture
        createTexture();

		//Event handler
		SDL_Event e;

        SDL_Color textColor = {0, 0, 0};

        SDL_Rect bottomViewport;
        bottomViewport.x = 0;
        bottomViewport.y = SCREEN_HEIGHT / 1.2;
        bottomViewport.w = SCREEN_WIDTH;
        bottomViewport.h = SCREEN_HEIGHT / 4;

		//While application is running
		while(!quit) {
			//Handle events on queue
			while(SDL_PollEvent(&e) != 0) {
				//User requests quit
				if(e.type == SDL_QUIT) {
					quit = true;
				}
                handleEvent(&e, browseButtonX, browseButtonY);
			}

            SDL_SetRenderDrawColor(gRenderer, 250, 250, 210, 255);
            SDL_RenderClear(gRenderer);

            SDL_RenderSetViewport(gRenderer, &bottomViewport);
            SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

            SDL_SetRenderDrawColor(gRenderer, 220, 220, 190, 255);
            SDL_RenderFillRect(gRenderer, &browseButton);

            loadFromRenderedText("Browse", textColor);
            SDL_RenderCopy(gRenderer, gTextTexture, NULL, &browseButton);

		    //Update the surface
		    SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
