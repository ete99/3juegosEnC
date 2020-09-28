char palabras[21][25];

typedef struct{
    int direc; //0 para horizontal,1 para vertical
    char palabra[16];
    int used;
    int j;	//Pos inicial en x de la palabra	x=columnas
    int i;	//Pos inicial en y de la palabra 	y=filas
}Situada;

#include "logicaCruci.h"
#include "renderCruci.h"
int crucigrama();




int crucigrama()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
	Uint32 delay, start;
    char cruci[N][N];
    char prueba[N][N];

    Estado estado;
    //inicia el crucigrama
	iniciarCruci(cruci, prueba, &estado);

	delay = 60; // delay necesario par que no se queme la pc

    //crea la ventana
    window = SDL_CreateWindow("Crucigrama",            		// titulo
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial x
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial y
                            640+320,                           // ancho
                            640,                                // altura
                            0                                   // min, 0, max 1
                            );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Font *font = TTF_OpenFont("cambriab.ttf", 25);// trae el tipo de texto
	TTF_Font *fontMenu = TTF_OpenFont("Cuad-Regular.ttf", 25);// trae el tipo de texto
	SDL_Rect pos[5]; // posicion de los botones
	SDL_Rect posc[N][N];
	SDL_Rect pospalabras[20];

    int done = 0, eleccion, pausa = 0,info = 1;

    while(done != -1 && done != 1)
    {
		start=SDL_GetTicks();
        //Check for events

		eleccion = processCruci(window, pos, posc,pospalabras, &pausa, prueba, &estado, cruci);//,font,renderer);
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
				iniciarCruci(cruci, prueba, &estado);
				break;
			case 5: //resumir
				pausa = 0;
				break;
			case 6: //gano
				winpopup();
				pausa = 1;
				iniciarCruci(cruci, prueba, &estado);
				break;
		}

		renderCruci(renderer, font, fontMenu, pos, posc, pospalabras, pausa, prueba, estado); // renderizar lo sucedido
		if(info || pausa) // si es la primera vez o esta "pausado"
			{
				popup();
				info = 0;
				pausa = 0;
			}
		if(delay>SDL_GetTicks()-start)//si tarda menos del delay dar delay de lo menos que tardo
		{
			SDL_Delay(delay-(SDL_GetTicks()-start));
		}
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
