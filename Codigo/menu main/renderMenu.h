void renderMenu(SDL_Renderer *rendermenu, TTF_Font* font, int colorSet, SDL_Rect pos[], int hover);
int processMenu(SDL_Window *menus,SDL_Renderer *rendermenu, TTF_Font* font);

int processMenu(SDL_Window *menus,SDL_Renderer *rendermenu, TTF_Font* font)
{
    //crea la ventana
	menus = SDL_CreateWindow("El menu",                     		// titulo
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial x
                            SDL_WINDOWPOS_UNDEFINED,            // pos inicial y
                            640+320,                           // ancho
                            640,                                // altura
                            0                                   // min, 0, max 1
                            );

    //crea el renderizador de la ventana
    rendermenu = SDL_CreateRenderer(menus, -1, SDL_RENDERER_ACCELERATED);
	int done = -1, x,y,corriendo=1;
	int selected[4] = {0};
	SDL_Event event;
	SDL_Rect pos[4]; //hitbox de los botones
	Uint32 start;
	renderMenu(rendermenu, font, -1, pos, 0);

	while(corriendo)
	{
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT_CLOSE:
				{
					if(menus)
                    {
                    return -1;
                    }
				}
				break;
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							return -1;
						break;
					}
				}
				break;
				case SDL_QUIT:
					return -1;
				break;

				case SDL_MOUSEMOTION: // si el cursor pasa por un boton
				{
					x = event.motion.x;
					y = event.motion.y;

					for(int i = 0; i < 4; i++)
					{
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
								renderMenu(rendermenu, font, -1, pos, i); //highlightea la palabra
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN: // si se aprieta un boton con el mouse hace la animacion del boton
				{
					x = event.motion.x;
					y = event.motion.y;

					for(int i = 0; i < 4; i++)
					{
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							if(!selected[i])
							{
								selected[i] = 1;
								renderMenu(rendermenu, font, i, pos, -1);
							}
						}
						else
						{
							if(selected[i])
							{
								selected[i] = 0;
								renderMenu(rendermenu, font, -1, pos, -1);
							}
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONUP: //si se levanta un boton con el mouse
					{
						x = event.button.x;
						y = event.button.y;
						for(int i = 0; i < 4; i += 1)
						{
							if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
							{
								SDL_DestroyWindow(menus);
								SDL_DestroyRenderer(rendermenu); //cierra la ventana y abre el juego
								return i;
							}
						}
						for(int i = 0; i < 4; i++)
						{
							selected[i] = 0;
							renderMenu(rendermenu, font, -1, pos ,-1); // quita los seleccionados
						}
					}
					break;
			}
		}

		SDL_RenderPresent(rendermenu);
		if(15>SDL_GetTicks()-start)
		{ //si tarda menos del delay dar delay de lo menos que tardo
			SDL_Delay(60-(SDL_GetTicks()-start));
		}
	}
	return done;
}

//dibuja los elementos del menus
void renderMenu(SDL_Renderer *rendermenu, TTF_Font* font, int colorSet, SDL_Rect pos[], int hover)
{
		//renderizado
		//coloca el color base en gris
		SDL_SetRenderDrawColor(rendermenu, 127, 127, 127, 255);

		// limpia en color gris
		SDL_RenderClear(rendermenu);
		int marg = 0, sobre = 0;
		const int NUMMENU = 4;
        const char* labels[] = {"sopa de letras", "crucigrama", "snake", "salir"};
        SDL_Surface* menus[NUMMENU];  //superficie del menu
        SDL_Color color[2] = {{174,0,1,255},{255, 0, 0, 255}};
		SDL_Color colorletra[2] = {{10,10,10,255},{255, 255, 255, 255}};
        SDL_Rect cuadroTex, cuadroTexFondo;

		for (int i = 0; i < 4; ++i) // imprime los botones
		{
			marg = (colorSet == i); // si es el seleccionado marg es 1 y cambia los colores y tamanhos
			sobre = (hover == i);

			menus[i] = TTF_RenderText_Solid(font,labels[i], colorletra[marg || sobre]); // crea la superficie del texto para renderizar
			SDL_Texture *texture = SDL_CreateTextureFromSurface(rendermenu, menus[i]);// transforma la superficie a una textura

			pos[i].x = 480 - menus[i]->clip_rect.w/2; // posiciona los cuadrados de las texturas
			pos[i].y = 75 + 100 * i + menus[i]->clip_rect.h/2;
			pos[i].h = menus[i]->clip_rect.h;// pone los anchos y largos de las texturas
			pos[i].w = menus[i]->clip_rect.w;

			cuadroTex.w = 480 - pos[0].w - marg * 50;
			cuadroTex.x = 480 - cuadroTex.w/2;
			cuadroTex.y = 70 + 100 * i + menus[i]->clip_rect.h/2;
			cuadroTex.h = menus[0]->clip_rect.h + 10;

			cuadroTexFondo.w = cuadroTex.w + 2;
			cuadroTexFondo.x = cuadroTex.x - 4;
			cuadroTexFondo.y = cuadroTex.y - 2;
			cuadroTexFondo.h = cuadroTex.h - 4;

			SDL_SetRenderDrawColor(rendermenu, 0, 0, 0,0);
			SDL_RenderFillRect(rendermenu, &cuadroTexFondo);// dibuja el fondo del boton

			SDL_SetRenderDrawColor(rendermenu, color[marg].r, color[marg].g, color[marg].b,255);//define el color del fondo del boton
			SDL_RenderFillRect(rendermenu, &cuadroTex);// dibuja el boton

			SDL_RenderCopy(rendermenu, texture, NULL, &pos[i]);// dibuja las letras

			SDL_DestroyTexture(texture);

		}
        //establece el hitbox de botones
		pos[0].w = pos[0].w;
		pos[0].x = 480 - cuadroTex.w/2;
		pos[0].y = 70 + 100 * 0 + menus[0]->clip_rect.h/2;
		pos[0].h = menus[0]->clip_rect.h + 10;

		SDL_FreeSurface(menus[0]);

		for (int i = 1; i < 4; ++i)
		{

			// para marcar el total del boton al senhalar
			pos[i].w = 480 - pos[0].w - marg * 50;
			pos[i].h = pos[0].h;
			pos[i].x = 480 - cuadroTex.w/2;
			pos[i].y = 70 + 100 * i + menus[i]->clip_rect.h/2;

			SDL_FreeSurface(menus[i]);
		}
}
