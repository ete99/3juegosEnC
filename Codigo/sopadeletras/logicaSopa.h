#include "utilSopa.h"

int logicoSopa(Palabra matriz[][N], const Uint8 *state, int* pausa, Estado *estado);
int processSopa(SDL_Window *window, SDL_Rect pos[], SDL_Rect posc[][N], int *pausa, const Palabra matriz[][N], Estado* estado);
void iniciarSopa(Palabra matriz[][N], Estado *estado);



int processSopa(SDL_Window *window, SDL_Rect pos[], SDL_Rect posc[][N], int *pausa, const Palabra matriz[][N], Estado* estado)
{
	int eleccion = 0;
	if(estado->tempo < 1200) //si no supera los 20 minutos
	{
		SDL_Event event;
		int x, y, numBOT = 3, send = 0;
		static int longitud = 0;

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
					return -1;
					}
					break;
				}
				case SDL_KEYDOWN: // si aprieta un boton
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						return -1;
						break;
						case SDLK_p:
						*pausa=1;
						break;
						case SDLK_SPACE: //si aprieta espacio pausa
							{
								if(*pausa == 0)
									*pausa=1;
								else if(!estado->win)
									*pausa=0;
							}
							break;
						case SDLK_r: // si aprieta r
							{
								iniciarSopa(matriz, estado);//reinicia el juego
								*pausa=1;
							}
							break;
						case SDLK_RETURN:
							{
								if(!(*pausa)) // si no esta pausado puede mandar la palabra
									send = 1;
							}
							break;
					}
					break;
				}

				case SDL_QUIT:
				//sale del juego
				return -1;
				break;
				case SDL_MOUSEBUTTONDOWN:
				{
					x = event.button.x;
					y = event.button.y;
					if(*pausa)
						numBOT = 5;
					else
						numBOT = 3;
					for(int i = 0; i < numBOT; i++) // si aprieta un boton
					{
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							return (i+1);
						}
					}

					if (longitud < 15 && !(*pausa)) //sie esta pausado, no deberia poder aceptar input
					{
						for(int i = 0; i < 12; i++)
						{
							for(int j = 0; j < 15; j++)
							{
								if(x >= posc[i][j].x && x <= posc[i][j].x + posc[i][j].w && y >= posc[i][j].y && y <= posc[i][j].y + posc[i][j].h)
								{
									if(estado->matbin[i][j] == 0)
									{
										estado->matbin[i][j] = 1;
										longitud++;
									}
									else
									{
										estado->matbin[i][j] = 0;
										longitud--;
									}

								}
							}
						}
					}
					break;
				}
			}
		}
		if(!(*pausa) && !estado->win && send)//si no esta pausado y no gano y mando
		{
			send = 0;
			longitud = 0;
			const Uint8 *state = SDL_GetKeyboardState(NULL); //lee es estado y pasa el estado al logico
			eleccion = logicoSopa(matriz, state, pausa, estado);//si logico verifica si supero los limites
		}
	}
	else //si se excedio en el tiempo
	{
		iniciarSopa(matriz, estado);//reinicia el juego
		*pausa=1; //pone pausa
	}
	return eleccion;
}





int logicoSopa(Palabra matriz[][N], const Uint8 *state, int* pausa, Estado *estado)
{
	static int total = 0;
	int done = 0, largo = 0;
	Palabra seleccion[TAM]; // creae un vector del las posiciones

	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if(estado->matbin[i][j]) // busca en la matriz las palabras encontradas
			{
				seleccion[largo] = matriz[i][j];
				largo++;
			}
		}
	}
	seleccion[largo].posx = -1; // determina que es el ultimo caracter
	int pertenece = estaEncontrado(seleccion);
	if( pertenece == 1) // si esta entre las palabras "encontradas" en la sopa de letras
	{
		for(int i = 0; i < largo; i++)
		{
			matriz[seleccion[i].posy][seleccion[i].posx].high = 1; //highlightea las palabras en la poscion si pertenece
		}
		total++;// suma al total de las palabras encontradas
	}
	else if(pertenece != -1) // si no pertence al diccionario pregunta si es una palabra real
	{
		if( palabraDesconocida(seleccion, estado) )
		{
			for(int i = 0; i < largo; i++) // si eligio que es una palabra real highlightea
			{
				matriz[seleccion[i].posy][seleccion[i].posx].high = 1;
			}
			total++; // suma al total de las palabras encontradas
		}
	}
	if(total > 20) // si entonctro gana el juego
	{
		estado->win = 1;
		total = 0;
		*pausa = 1;
	}
	//cera la matriz binaria ya que ya no es necesaria
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			estado->matbin[i][j] = 0; // cera la matriz binaria de seleccion
		}
	}
	return done;
}






//cera todo y genera la matriz
void iniciarSopa(Palabra matriz[][N], Estado *estado)
{
    estado->win = 0;
    estado->puntos = 0;
    estado->nuevo = 0;
    estado->tempo = 0;
    for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			estado->matbin[i][j] = 0;
			matriz[i][j].high = 0;
		}
	}

	for (int i=0; i<cantENC; i++)
	{
		encontrados[i][0].posx = -1;
	}
	cantENC = 0;
	cantENCU = 0;// reinicia los contadores de palabras de las listas
	generarSopa(matriz);
}


