#include "structdatos.h"
#include "logica.h"



int snakeGame()
{
	Uint32 tempo=0;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
	Uint32 delay, start;
    Snk snk;
    Cola cola;

	delay = 60; // delay necesario par que no se queme la pc

	iniciarJuego(&snk, &cola);

	int menu = 320; // tamanho del menu

    //crea la ventana
    window = SDL_CreateWindow("Snake",                     		// titulo
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial x
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial y
                            640+menu,                           // ancho
                            640,                                // altura
                            0                                   // min, 0, max 1
                            );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Font *font = TTF_OpenFont("Cuad-Regular.ttf", 25);// trae el tipo de texto
	SDL_Rect pos[5]; // posicion de los botones

    int done = 0, eleccion, pausa = 0;
    while(done != -1 && done != 1)
    {
		start=SDL_GetTicks();

		eleccion = processSnake(window, &snk, &cola, tempo, pos, &pausa);
		switch(eleccion)
		{
			case -1: // salir del programa
				done = -1;
				break;
			case 0: // seguir corriendo
				done = 0;
				break;
			case 1: //volver al menu
				done = 1;
				break;
			case 2: //pausar
				pausa = 1;
				break;
			case 3: // salir del programa
				done = -1;
				break;
			case 4: //reiniciar
				pausa = 1;
				iniciarJuego(&snk, &cola);
				break;
			case 5: //resumir
				pausa = 0;
				break;
		}
		render(renderer, &snk, &cola, font, pos, pausa); // renderizar lo sucedido
		tempo++; // aumenta el tempo
		tempo=tempo%1001; // para que no se exceda
		if(delay>SDL_GetTicks()-start){ //si tarda menos del delay dar delay de lo menos que tardo
			SDL_Delay(delay-(SDL_GetTicks()-start));
		}
		//printf("%d\n", (start - tiempo)/60);
    }

    // cerrar la ventana
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // limpiar
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return done;
}
