#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
typedef struct
{
  int x, y;
  short life;
  char *name;
} Man;

int processEvents(SDL_Window *window, Man *man)//, TTF_Font *font)
{
	SDL_Event event;
	int done = 0;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			if(window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					done = 1;
				break;
			}
		}
		break;
		case SDL_QUIT:
		//quit out of the game
		done = 1;
		break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_LEFT])
	{
		man->x -= 10;
	}
	if(state[SDL_SCANCODE_RIGHT])
	{
		man->x += 10;
	}
	if(state[SDL_SCANCODE_UP])
	{
		man->y -= 10;
	}
	if(state[SDL_SCANCODE_DOWN])
	{
		man->y += 10;
	}

return done;
}

void doRender(SDL_Renderer *renderer, Man *man)//, TTF_Font *font)
	{
	//set the drawing color to blue
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//Clear the screen (to blue)
	SDL_RenderClear(renderer);

	//set the drawing color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = { man->x, man->y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect);
	/*
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect cuadrado = { 5, 10, 300, 100 };
	SDL_RenderFillRect(renderer, &cuadrado);
	*/
	#if 0
	SDL_Color color = { 174, 0, 1,255};
	SDL_Surface * surface = TTF_RenderText_Solid(font,"hola putos", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

#endif
	//We are done drawing, "present" or show to the screen what we've drawn
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
	TTF_Init();
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  Man man;
  man.x = 220;
  man.y = 140;

  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640 + 320,                               // width, in pixels
                            640,                               // height, in pixels
                            0                                  // flags
                            );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font * font = TTF_OpenFont("Lato-Regular.ttf", 25);
	SDL_Event event;
	#if 1
	//TTF_Font * font = TTF_OpenFont("Lato-Regular.ttf", 25);
	printf("%p", font);//la dir de fonts
	SDL_Color color = { 174, 0, 1,255};
	SDL_Surface * surface = TTF_RenderText_Solid(font,"hola putos", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	int quit=0;
    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
        }
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
    }
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	#endif
#if 1
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;

  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &man);//, font);

    //Render display
    doRender(renderer, &man);//, font);

    //don't burn up the CPU
    SDL_Delay(10);
  }

#endif
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  // Clean up
  //TTF_Quit();
  SDL_Quit();
  return 0;
}
