#include <string.h>
#include <locale.h>
#include <time.h>
#include "utilCruci.h"

char paldelcruci[20];
char matsign[20][200];
Situada situadas[20];
void generarCruci();
void BuscarMatriz(Palabra matriz[][N]);
int logicoCruci(char matriz[][N], const Uint8 *state, int* pausa, Estado *estado);
int processCruci(SDL_Window *window, SDL_Rect pos[], SDL_Rect posc[][N], SDL_Rect pospalabras[], int *pausa,  char matriz[][N], Estado* estado,char matreal[][N]);//,TTF_Font* font, SDL_Renderer *renderer);
void iniciarCruci(char matriz[][N], char prueba[][N], Estado *estado);




int processCruci(SDL_Window *window, SDL_Rect pos[], SDL_Rect posc[][N], SDL_Rect pospalabras[], int *pausa,  char matriz[][N], Estado* estado,char matreal[][N])
{
	int eleccion = 0, comprobar= 0;
	char data = ' ';

		SDL_Event event;
		int x, y, numBOT = 3, send = 0;
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
				case SDL_KEYDOWN:
				{
					data =  event.key.keysym.sym;
					if(esletrachar(data)) // si es una palabra la insertada pasa al diccionario
						send = 1;

					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						return -1;
						break;
						case SDLK_SPACE:
							{
								if(*pausa == 0)
									*pausa=1;
								else if(!estado->win)
									*pausa=0;
								send= 0;
							}
							break;
						case SDLK_RETURN:
							{
								if(!(*pausa)) // si no esta pausado puede mandar la palabra
									comprobar = 1;
									send=0;
							}
							break;
						case SDLK_TAB:
							return 4;
						case SDLK_UP: //para mover con las flechas la seleccion
							if(estado->i-1 >= 0 && matriz[estado->i-1][estado->j] != ' ')//si se puede hacer el movimiento
								estado->i-=1;
							break;
						  case SDLK_DOWN:
							if(estado->i+1 < 15 && matriz[estado->i+1][estado->j] != ' ')//si se puede hacer el movimiento
								estado->i+=1;
							break;
						  case SDLK_RIGHT:
							if(estado->j+1 < 15 && matriz[estado->i][estado->j+1] != ' ')//si se puede hacer el movimiento
								estado->j+=1;
							break;
						  case SDLK_LEFT:
							if(estado->j-1 >= 0 && matriz[estado->i][estado->j-1] != ' ')//si se puede hacer el movimiento
								estado->j-=1;
							break;
					}
					break;
				}

				case SDL_QUIT:
				//sale del juego
				return -1;
				break;
				case SDL_MOUSEBUTTONDOWN: //si aprieta un boton
				{
					x = event.button.x;
					y = event.button.y;
					if(*pausa)
						numBOT = 5;
					else
						numBOT = 3;
					for(int i = 0; i < numBOT; i++)
					{
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							return (i+1);
						}
					}

					if ( !(*pausa) ) //sie esta pausado, no deberia poder aceptar input
					{
						for(int i = 0; i < N; i++)
						{
							for(int j = 0; j < N; j++)
							{
								if(x >= posc[i][j].x && x <= posc[i][j].x + posc[i][j].w && y >= posc[i][j].y && y <= posc[i][j].y + posc[i][j].h)
								{
									if(matriz[i][j] != ' ')
									{
										estado->i=i;
										estado->j=j;
									}
								}
							}
						}
					}

					for(int i = 0; i < 20; i++)//significados
					{
						if(x>=pospalabras[i].x && x<=pospalabras[i].x+pospalabras[i].w && y>=pospalabras[i].y && y<=pospalabras[i].y+pospalabras[i].h)
						{
							//printf("%s\n", situadas[i].palabra);
							significado(matsign[i]);
						}
					}
					break;
				}
			}
		}
		if(!(*pausa) && !estado->win && send && esletrachar(data) && !comprobar) // si no esta pausado, todavia no gano, es una letra y no mando a comprobar
		{
			send = 0;
			matriz[estado->i][estado->j] = data;
		}
		if(comprobar)// si aprieta enter, para terminar
		{
			comprobar = 0;
			for(int i=0 ; i<15 ; i++)
			{
				for(int j=0 ; j<15 ; j++)
				{
					if(matreal[i][j] != matriz[i][j])
						return 4;
				}
			}
			return 6;
		}
	return eleccion;
}





void generarCruci(char cruci[][15]) //genera el crucigrama
{
	int k,i,j;

	setlocale(LC_ALL, "spanish");// para usar la Ñ

	char matpal[20][16];
	int uno= 0;
	while(uno < 19)
	{
		//ceramos todo aca por si se tiene que repetir

		for(i=0 ; i<15 ; i++){
			for(j=0 ; j<15 ; j++){ //Se llena la matriz con espacios en blanco
				cruci[i][j] = ' ';
			}
		}
		uno = 0;

		generarPalabras(matpal, matsign);//no ordenar por que o sino se pierde la posicion del significado

		strcpy(situadas[0].palabra, matpal[0]);
		situadas[0].used = 1;
		situadas[0].i = 1;
		situadas[0].j = 0;
		situadas[0].direc = 0;
		for (i=1; i<20; i++) // copia las palabras al vector
		{
			strcpy(situadas[i].palabra, matpal[i]);
			situadas[i].used = 0;
			situadas[i].i = -1;
			situadas[i].j = -1;
			situadas[i].direc = -1;
		}

		situarCruci(situadas[0], cruci); // pone la primera palabra del crucigrama

		int cpudo = 0;
		int direc;
		for (int pospalabra2=0; pospalabra2<20; pospalabra2++) //itera una vez mas por si puede encontrar mas palabras
		{
			for (int pospalabra=0; pospalabra<20; pospalabra++) // recorre todas las palabras
			{
				cpudo = 0; // cera que se pudo
				if(situadas[pospalabra].used == 0) // is no fue usada la palabra
				{
					for (k=0; k<15 && !cpudo; k++) // k es la posicion de la letra
					{
						for (i=0; i<15 &&!cpudo; i++) // busca en i de la matriz
						{
							for (j=0; j<15 && !cpudo; j++)// busca en j de la matriz
							{
								if(cruci[i][j] == situadas[pospalabra].palabra[k] && k<strlen(situadas[pospalabra].palabra))
								{
									int izq, der;
									int largo = strlen(situadas[pospalabra].palabra); //largo de la segunda palabra
									izq = k; // cantidad de bloques a un lado
									der = largo - 1 - izq; // der cantidad de bloques a la derecha

									if(cruci[i][j+1] == ' ' && cruci[i][j-1] == ' ')// si se puede poner verticalmente
									{
										direc= 0;
										if(entraSimple(i, j, 1, izq, der))//si entra en la matriz puesto verticalmente
										{
											cpudo = nochoca(i,j,cruci,situadas[pospalabra].palabra, 1,izq,der); //si no choca con una letra que no es igual o es un espacio
										}
									}
									if(cruci[i-1][j] == ' ' && !cpudo && cruci[i+1][j]== ' ') // si se puede poner horizontalmente
									{
										direc= 1;
										if(entraSimple(i, j, 0, izq, der)) //si entra en la matriz puesto horizontalmente
										{
											cpudo = nochoca(i,j,cruci,situadas[pospalabra].palabra, 0,izq,der);
										}
									}
									if (cpudo) // si se pudo situa en la matriz la palabra
									{
										situadas[pospalabra].direc= direc;
										situadas[pospalabra].i = i;
										situadas[pospalabra].j = j;
										if(direc) //dependiento de la direccion determina su posicion inicial
										{
											situadas[pospalabra].i -= k;
										}
										else
										{
											situadas[pospalabra].j -= k;
										}

										situadas[pospalabra].used = 1; // marca con usada

										uno++;

										situarCruci(situadas[pospalabra], cruci); // situa en el cruci
									}
								}
							}
						}
					}
				}
			}
		}
	}
    //imprime la matriz
	imprimirBien(cruci);

}



//cera el crucigrama
void iniciarCruci(char matriz[][N], char prueba[][N], Estado *estado)
{
    estado->win = 0;
    estado->puntos = 0;
    estado->nuevo = 0;
    estado->tempo = 0;
    generarCruci(matriz); // genera el crucigrama
    for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{

			if(matriz[i][j] != ' ')
			{
				prueba[i][j] = '/'; // si es una letra pasa a ser un caracter diferente, para diferenciar con los espacios reales
				estado->i=i; //determina la posicion inicial
				estado->j=j;
			}

			else
				prueba[i][j] = ' ';
		}
	}
	for(int i=0 ; i<20 ; i++) // copia a una lista las palabras situadas
	{
		if(situadas[i].direc)
			sprintf(palabras[i],"(%d, %d) vert.", situadas[i].i,situadas[i].j);
		else
			sprintf(palabras[i],"(%d, %d) hori.", situadas[i].i,situadas[i].j);
	}
}


