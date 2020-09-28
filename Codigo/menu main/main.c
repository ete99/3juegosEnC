#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "renderMenu.h"
#include "../sopadeletras/sopadeletras.h"//trae el juego sopa de letras
#include "../crucigrama/crucigrama.h" //trae el juego crucigrama
#include "../snake/snake.h" //trae el juego snake

int main(int argc, char *argv[])
{
    SDL_Window *menus; //
    SDL_Renderer *rendermenu;
    SDL_Init(SDL_INIT_VIDEO); // se inicia SDL
    TTF_Init();              // se inicia TTF para los textos

	Uint32 delay, start;
	srand(time(NULL));

	delay = 60; //delay se usa para que no renderice

	TTF_Font *font = TTF_OpenFont("CWG Sans.ttf", 25);// se trae el tipo de texto

    int done = 0,eleccion=0;

	//procesa los eventos
    while(done != -1)
    {
		start = SDL_GetTicks();//el tiempo que paso desde que se abrio el main

		eleccion = processMenu(menus, rendermenu, font); //se llama a procesar menu, que tiene la parte logica y el renderizado del menu

		//eleccion es el boton apretado en el menu
		switch(eleccion)
		{
			case -1:
				done = -1;
				break;
			case 0:
				done = sopaDeLetras();//llama al juego sopa de letras
				break;
			case 1:
				done = crucigrama();//llama al juego crucigrama
				break;
			case 2:
				done = snakeGame(); //llama al juego snake
				break;
			case 3:
				done = -1; // salir del programa
				break;
		}
		if(delay > SDL_GetTicks() - start) //SDL_GetTicks() es el tiempo actual, start es el tiempo cuando se comenzo
		{
		//si tarda menos del delay dar delay de lo menos que tardo, para que no se queme la pc
			SDL_Delay(delay-(SDL_GetTicks()-start));
		}
    }

    // cerrar la ventana, para liberar memoria
	SDL_DestroyWindow(menus);
	SDL_DestroyRenderer(rendermenu);


    // Limpiar las librerias
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
