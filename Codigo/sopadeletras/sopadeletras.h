#include "structSopa.h"
#include "logicaSopa.h"
#include "renderSopa.h"
int sopaDeLetras();



int sopaDeLetras()
{
	int mili = 0;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

	Uint32 delay, start;
    Palabra matriz[M][N];
    Estado estado;

	iniciarSopa(matriz, &estado); //genera la sopa de letras y reinicia todo

	delay = 60; // delay necesario par que no se queme la pc

	int menu = 320; // tamanho del menu

    //crea la ventana
    window = SDL_CreateWindow("Sopa de letras",            		// titulo
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial x
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial y
                            640+menu,                           // ancho
                            640,                                // altura
                            0                                   // min, 0, max 1
                            );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Font *font = TTF_OpenFont("cambriab.ttf", 25);// trae el tipo de texto
	TTF_Font *fontMenu = TTF_OpenFont("Cuad-Regular.ttf", 25);// trae el tipo de texto
	SDL_Rect pos[5]; // posicion de los botones
	SDL_Rect posc[M][N]; //hitbox de todas las letras

    int done = 0, eleccion, pausa = 0;

    while(done != -1 && done != 1)
    {
		start=SDL_GetTicks();

		eleccion = processSopa(window, pos, posc, &pausa, matriz, &estado);
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
				iniciarSopa(matriz, &estado);
				break;
			case 5: //resumir
				pausa = 0;
				break;
		}

		if((mili>1000)) // si paso un segundo aumenta la cantidad de segundos en 1
		{
			mili = 0; // para que no se exceda
			estado.tempo++;
		}
		renderSopa(renderer, font, fontMenu, pos, posc, pausa, matriz, estado); // renderizar lo sucedido

		if(delay>SDL_GetTicks()-start)//si tarda menos del delay dar delay de lo menos que tardo
		{
			SDL_Delay(delay-(SDL_GetTicks()-start));
		}
		if(!pausa)
			mili+= 60; // aumenta el tiempo, el delay es de 60 milisegundos entonces amuenta en 60
    }

    // cerrar la ventana
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // limpieza
    TTF_CloseFont(font);
    TTF_CloseFont(fontMenu);
    TTF_Quit();
    SDL_Quit();
    return done;
}
