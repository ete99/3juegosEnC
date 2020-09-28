#include "rend.h"


int logico(Snk *snk, const Uint8 *state, Uint32 tempo, Cola *cola, int* pausa);
void generarManz(Snk* snk, const Cola *cola);
void checkeo(const Snk *snk, const Cola *cola, int matcomp[][18]);
int processSnake(SDL_Window *window, Snk *snk, Cola *cola, Uint32 tempo, SDL_Rect pos[], int *pausa);
int colision(Snk *snk,Cola *cola);
void iniciarJuego(Snk *snk, Cola* cola);
int dificultad();



int processSnake(SDL_Window *window, Snk *snk, Cola *cola, Uint32 tempo, SDL_Rect pos[], int *pausa)
{
	SDL_Event event;
	int eleccion = 0, x, y, numBOT = 3;
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
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE: // si aprieta escape cierra el juego
					return -1;
					break;
					case SDLK_p:
					*pausa=1;
					break;
					case SDLK_SPACE: // si aprieta espacio pausa y despausa
						{
							if(*pausa == 0)
								*pausa=1;
							else if(!snk->win)
								*pausa=0;
						}
						break;
					case SDLK_r: //si aprieta r reinicia
						{
							iniciarJuego(snk, cola);
							*pausa=1;
						}
					break;
				}
				break;
			}
			case SDL_QUIT:
			//Sale del juego
			return -1;
			break;
			case SDL_MOUSEBUTTONDOWN: // checkea si se apreto un boton
			{
				x = event.button.x;
				y = event.button.y;
				if(*pausa)
					numBOT = 5;
				else
					numBOT = 3;
				for(int i = 0; i < numBOT; i++) // el numero de botones que estan disponibles
				{
					if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
					{
						return (i+1);
					}
				}
				break;
			}
		}
	}

	if(!(*pausa) && !snk->win) // si no esta pausado y no gano todavia
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL); // obtiene el elctor de estados
		eleccion = logico(snk, state, tempo, cola, pausa);//logico mueve la vibora
	}
	return eleccion;
}




int logico(Snk *snk, const Uint8 *state, Uint32 tempo, Cola *cola, int* pausa)
{
	int done=0;
	//lee el estado de las teclas y chequea que no se salio de la matriz
	if(state[SDL_SCANCODE_LEFT] && snk->r==0 && snk->x>=0)
	{
		snk->l=1;
		snk->d=snk->r=snk->u=0;
	}
	else if(state[SDL_SCANCODE_UP] && snk->d==0 && snk->y>0)
	{
		snk->u=1;
		snk->d=snk->r=snk->l=0;
	}
	else if(state[SDL_SCANCODE_DOWN] && snk->u==0 && snk->y<608)
	{
		snk->d=1;
		snk->l=snk->r=snk->u=0;
	}
	else if(state[SDL_SCANCODE_RIGHT] && snk->l==0 && snk->x<608)
	{
		snk->r=1;
		snk->d=snk->l=snk->u=0;
	}

	//mueve la sepiente
	if(tempo%2==0) // para que no corra tan rapido limita devuelta
	{
	    //desplaza la cola de la serpiente
		for(int i=cola->longitud; i > 0 ; i--)
		{
			cola->pos[i].x=cola->pos[i-1].x;
			cola->pos[i].y=cola->pos[i-1].y;
		}
		cola->pos[0].x = snk->x;
		cola->pos[0].y = snk->y;

        //verifica la direccion y la nueva direccion dada de la serpiente y mueve
		if(snk->l && snk->x>0 && snk->rpas != 1)
		{
			snk->x -= snk->dim;
			snk->lpas = 1;
			snk->upas=snk->dpas=snk->rpas=0;
		}
		else if(snk->u && snk->y>0 && snk->dpas != 1)
		{
			snk->y -= snk->dim;
			snk->upas = 1;
			snk->dpas=snk->lpas=snk->rpas=0;
		}
		else if(snk->d && snk->y<608 && snk->upas != 1)
		{
			snk->y += snk->dim;
			snk->dpas = 1;
			snk->upas=snk->lpas=snk->rpas=0;
		}
		else if(snk->r && snk->x<608 && snk->lpas != 1)
		{
			snk->x += snk->dim;
			snk->rpas = 1;
			snk->upas=snk->lpas=snk->dpas=0;
		}
		snk->pasos++; // amuenta la cantidad de pasos dados
		done = colision(snk, cola); // si colisiona con algo
		if(cola->longitud == snk->maximo)// si llego al maximo puesto
			{
				*pausa = 1;
				snk->win = 1;
			}
	}

	//resuelve el error de quedarse quieto al apretar dos teclas
	if(snk->u != snk->upas)
	{
		snk->u=snk->upas;
	}
	if(snk->d != snk->dpas)
	{
		snk->d=snk->dpas;
	}
	if(snk->r != snk->rpas)
	{
		snk->r=snk->rpas;
	}
	if(snk->l != snk->lpas)
	{
		snk->l=snk->lpas;
	}

	return done;
}




//chequea colisiones con la comida, consiigomismo y con los limites
int colision(Snk *snk,Cola *cola)
{
	int done = 0;

	if(snk->x == snk->manz.x && snk->y == snk->manz.y)//si come la comida
	{
		if(cola->longitud+1 != 324)
			generarManz(snk, cola);// si gana no...
		snk->puntos += cola->longitud/log((snk->pasos)) + 1;
		cola->longitud++;
		snk->pasos=1;

	}
	else if (!(snk->x<640-snk->dim && snk->x>0 && snk->y>0 && snk->y<640-snk->dim)) // si supera los limites
	{
		done = 4;
	}
	else
	{
		for(int i = 1; i<cola->longitud; i++)
		{
			if(snk->x == cola->pos[i].x && snk->y == cola->pos[i].y) //si se come a si mismo
			{
				done = 4;
				break;
			}
		}
	}
	return done;
}




//genera aleatoriamente
void generarManz(Snk* snk, const Cola *cola)
{
	int kk=0,lugar;
	Pos rvec[325];// maximo que va a poder tener subir si no tiene limites la longuitud
	int matcomp[18][18];
	checkeo(snk, cola, matcomp);// guarda todo los lugares en los que no esta el snake

	for (int i=0; i<18; i++)
	{
		for (int j=0; j<18; j++)
		{
			if((matcomp[i][j]))// si
			{
				rvec[kk].y = (i+1)*32;
				rvec[kk].x = (j+1)*32;
				kk++;
			}
		}
	}
	lugar= rand()%kk;//elije un valor al azar de las posiciones habiles del vector con valores
	snk->manz.x = rvec[lugar].x;
	snk->manz.y = rvec[lugar].y;
}




//chequea las posiciones en las que puede ponerse la comida
void checkeo(const Snk *snk, const Cola *cola, int matcomp[][18])
{
    int posible;

    for (int i=0; i<18; i++)
    {
        for (int j=0; j<18; j++)
        {
            matcomp[i][j]=0;
        }
    }
    for (int i=0; i<18; i++)
    {
        for (int j=0; j<18; j++)
        {
            posible = 1;
            if(i*32 + 32 == snk->y && j*32 + 32 == snk->x)
            {
                posible = 0;
            }
            for(int k = 0; k < cola->longitud; k++)
            {
                if(i*32 + 32 == cola->pos[k].y && j*32 + 32 == cola->pos[k].x)
                {
                    posible=0;
                }
            }

            if(posible)
            {
                matcomp[i][j]=1;
            }
        }
    }
}




//pone en cero el juego
void iniciarJuego(Snk *snk, Cola* cola)
{
	snk->x = 128;//pos inicial
    snk->y = 320;
    snk->d = snk->u = snk->l = 0;
    snk->r=1; // direccion actual
    snk->dpas = snk->upas = snk->lpas = 0;
	snk->rpas=1; // direccion pasada
    snk->dim = 32;
    snk->pasos = 1;
    snk->puntos = 0;
    snk->win = 0;
    cola->pos[0].x=snk->x-snk->dim;
    cola->pos[0].y=snk->y;
    cola->longitud=1; // logitud de la cola
	snk->manz.x=416; // posicion de la comida
	snk->manz.y=320;
	int resp = dificultad(); // pregunta que tan largo quiere que sea el juego
	if(resp ==0)
	{
		snk->maximo = 5;
	}
	else if(resp == 1)// bastantes comiditas
	{
		snk->maximo = 100;
	}
	else
	{
		snk->maximo = 324; // el total que puede comer
	}
}




 // pregunta que tan largo quiere que sea el juego
int dificultad()
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "Corto" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Largo" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "Eternidad" },
    };
    const SDL_MessageBoxColorScheme colorScheme = { // colores
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {    // datos del mensaje
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "        Longitud", /* .title */
        "Que tan largo quiere que sea el juego?", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {    //manda el mensaje
        SDL_Log("error en el mensaje de texto");
        //return 1;
    }
    if (buttonid == -1) {
        //SDL_Log("no hubo seleccion");
    } else {
        //SDL_Log("selection was %s", buttons[buttonid].text);
        return buttonid;
    }
}
