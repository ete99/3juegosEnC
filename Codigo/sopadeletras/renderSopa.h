void renderSopa(SDL_Renderer *renderer, TTF_Font *font,TTF_Font *fontMenu, SDL_Rect pos[], SDL_Rect posc[][N], int pausa, const Palabra matriz[][N], Estado estado);




void renderSopa(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *fontMenu, SDL_Rect pos[], SDL_Rect posc[][N], int pausa, const Palabra matriz[][N], Estado estado)
{
		//setlocale(LC_ALL, "spanish");// para usar la �
		//set the drawing color to blue
		SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);

		//Clear the screen (to blue)
		SDL_RenderClear(renderer);

		//hace un cuadro rojo
		SDL_SetRenderDrawColor(renderer, 127, 0, 0, 255);
		SDL_Rect rect2 = { 0, 0, 640, 520 };
		SDL_RenderFillRect(renderer, &rect2);

		//hace un cuadro rojo
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_Rect rect3 = { 10, 10, 620, 500 };
		SDL_RenderFillRect(renderer, &rect3);

		SDL_Color colortexto = { 240,240,240,255};
		SDL_Rect cuadroTex;
		if(!pausa) //si esta pausado no renderiza las letras
		{
			//imprime la cuadricula
			SDL_Rect mrec, mrec2;
			SDL_Surface* cuadroMat;

			//SDL_Texture *texture;
			char let[2];
			let[1] = '\0'; //para evitar problemas
			for (int i=0; i<M; i++)
			{
				for (int j=0; j<N; j++)
				{
                    //dimesiona los cuadrados
					mrec.h=40;
					mrec.w=40;
					mrec.x=20+j*40;
					mrec.y=20+i*40;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(renderer, &mrec);

					mrec2.h=38;
					mrec2.w=38;
					mrec2.x=21 + j*40;
					mrec2.y=21 + i*40;

					if(estado.matbin[i][j] == 1) // si es parte de una palabra cambia de color el fondo
						SDL_SetRenderDrawColor(renderer, 255, 153, 153, 255);
					else
					SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);


					if(matriz[i][j].high) // sie esta highlighteado cambia de color el fondo
					{
						if(estado.matbin[i][j] == 1)
							SDL_SetRenderDrawColor(renderer, 255, 100, 110, 255);
						else
							SDL_SetRenderDrawColor(renderer, 174, 0, 10, 255);
					}
					SDL_RenderFillRect(renderer, &mrec2);

					let[0] = matriz[i][j].car; //pasa el caracter a una cadena para imprimir

					cuadroMat = TTF_RenderText_Solid(font, let, colortexto);

					SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, cuadroMat);

					posc[i][j].x = mrec.x + 20 - cuadroMat->clip_rect.w/2;
					posc[i][j].y = mrec.y + 20 - cuadroMat->clip_rect.h/2; // + cuadroMat[i]->clip_rect.h/2;
					posc[i][j].h = cuadroMat->clip_rect.h;// pone los anchos y largos de las texturas
					posc[i][j].w = cuadroMat->clip_rect.w;

					SDL_RenderCopy(renderer, texture, NULL, &posc[i][j]);

					SDL_DestroyTexture(texture);
					SDL_FreeSurface(cuadroMat);

					posc[i][j] = mrec;
				}
			}
		}

	SDL_Rect rect1 = { 640, 0, 320, 640 };

	//dibuja la cabecera de los encontrados

	char cabecera[]= "Encontrados: ", canti[5];

	sprintf(canti,"%d.", cantENCU);
	strcat(cabecera, canti);

	SDL_Surface *encontr = TTF_RenderText_Solid(font, cabecera, colortexto);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, encontr);
	cuadroTex.y = encontr->clip_rect.h/2 - 10;
	cuadroTex.w = encontr->clip_rect.w;
	cuadroTex.x = 640 + 160 - cuadroTex.w/2;
	cuadroTex.h = encontr->clip_rect.h;
	SDL_RenderCopy(renderer, texture, NULL, &cuadroTex);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(encontr);

	//dibuja los encontrados
	SDL_Color colorbin[] = {{ 0,0,0,255},{ 240,240,240,255}};
	//SDL_Rect cuadroTex;
    SDL_Rect Rencon, hecho;
    int shift = 0;

    for (int i=0; i<cantENCU && i < 40; i++)
    {

    	if(i >= 20)
			shift = 1; // si la cantidad de palabras super 20 divide en 2 columnas

    	SDL_Surface *PalEncon = TTF_RenderText_Solid(font, unicos[i].palabra, colorbin[unicos[i].valido]);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, PalEncon);

		//640 + 160  - cuadroTex.w/2 centra la palabra
		//+ (cuadroTex.w/3)*shift*2 si  tiene shift mueve tanto en x
		Rencon.x = 670 + (80)*shift*2 + 60 - PalEncon->clip_rect.w/2;// 640 = tamanho del juego , 160 = el tamanho del menu /2
		Rencon.y = PalEncon->clip_rect.h/2 +  PalEncon->clip_rect.h * (i - 20*shift) + PalEncon->clip_rect.h - 10;
		Rencon.h = PalEncon->clip_rect.h;// pone los anchos y largos de las texturas
		Rencon.w = PalEncon->clip_rect.w;

		//dimesiones del cuadrado del fondo
		hecho.w = 120;
		hecho.x = 640 + 30 + (80)*shift*2;
		hecho.y = Rencon.y;
		hecho.h = Rencon.h;

		SDL_SetRenderDrawColor(renderer, 10, 200, 10, 255); // verde fondo

		if(unicos[i].valido == 1)
			SDL_SetRenderDrawColor(renderer, 174, 0, 1, 255); //rojo gryffindor

		SDL_RenderFillRect(renderer, &hecho);

		SDL_RenderCopy(renderer, texture, NULL, &Rencon);

		SDL_DestroyTexture(texture); //limpia la textura y la superficie, para que la memoria no se llene de basura
		SDL_FreeSurface(PalEncon);
    }


    //dibuja el tiempo
	char hora[10], score[]= "Tiempo Restante ";
	int minuto, segundo;
	estado.tempo = 1200 - estado.tempo; // 1200 es 20 minutos en segundos

	segundo = estado.tempo%60; //obtiene los segundos
	minuto = estado.tempo/60; //pasa a minutos

	sprintf(hora,"%d:%d !", minuto, segundo);
	strcat(score, hora);
	SDL_Surface *scoreSurf = TTF_RenderText_Solid(fontMenu, score, colortexto);
	texture = SDL_CreateTextureFromSurface(renderer, scoreSurf);
	cuadroTex.y = 600;
	cuadroTex.w = scoreSurf->clip_rect.w;
	cuadroTex.x = 320 - cuadroTex.w/2;
	cuadroTex.h = scoreSurf->clip_rect.h;
	SDL_RenderCopy(renderer, texture, NULL, &cuadroTex);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(scoreSurf);


    //dibuja el menu

	const char* labels[] = {"Volver al menu", "Pausa (p)", "Salir (Esc)"}; // las cadenas necesarias
	SDL_Surface* menus[3];
	SDL_Color colorletra[2] = {{ 200,200,200,255},{255, 255, 255, 255}};
	SDL_Rect cuadroTexFondo;

	for(int i=0; i < 3; i++)
	{
		menus[i] = TTF_RenderText_Solid(fontMenu, labels[i], colorletra[0]);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, menus[i]);

		pos[i].x = 100 + (menus[0]->clip_rect.w/2 + 120) * i - menus[i]->clip_rect.w/2; // 640 = tamanho del juego , 160 = el tamanho del menu /2, menus[0]->clip_rect.w/2 = ancho de la palabra/2
		pos[i].y = 540  + menus[i]->clip_rect.h/2;
		pos[i].h = menus[i]->clip_rect.h; // pone los anchos y largos de las texturas
		pos[i].w = menus[i]->clip_rect.w;

		cuadroTex.w = 10 + pos[0].w;
		cuadroTex.x = 100 + (menus[0]->clip_rect.w/2 + 120) * i - cuadroTex.w/2;
		cuadroTex.y = 540 + menus[0]->clip_rect.h/2;
		cuadroTex.h = menus[0]->clip_rect.h + 10;

		cuadroTexFondo.w = cuadroTex.w + 2;
		cuadroTexFondo.x = cuadroTex.x - 4;
		cuadroTexFondo.y = cuadroTex.y - 2;
		cuadroTexFondo.h = cuadroTex.h - 4;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0,0);
		SDL_RenderFillRect(renderer, &cuadroTexFondo);

		SDL_SetRenderDrawColor(renderer, 5,50,229,255);
		SDL_RenderFillRect(renderer, &cuadroTex);// dibuja el fondo del boton

		SDL_RenderCopy(renderer, texture, NULL, &pos[i]);

		pos[i] = cuadroTex;

		SDL_DestroyTexture(texture);

		if(i) //si es el primer elemento del menu no limpia la superficie por que usamos para alinear las otras
			SDL_FreeSurface(menus[i]);
	}
	SDL_FreeSurface(menus[0]);// limpia la primera superficie


	//si esta pausado
	if (pausa)
	{
		//imprime el cuadrado del fondo
		SDL_SetRenderDrawColor(renderer, 224, 229, 229, 255);
		SDL_Rect medio = {164, 270, 312, 176};
		SDL_RenderFillRect(renderer, &medio);

		const char* labelsPausa[] = {"Reiniciar (r)", "Resumir (espacio)"};
		for(int i=0; i < 2 - estado.win; i++)
		{
			SDL_Surface* pausado = TTF_RenderText_Solid(fontMenu, labelsPausa[i], colorletra[1]);
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, pausado);

			pos[3 + i].x = 320 - pausado->clip_rect.w/2;// 640 = tamanho del juego , 160 = el tamanho del menu /2, menus[0]->clip_rect.w/2 = ancho de la palabra/2
			pos[3 + i].y = 320 - pausado->clip_rect.h/2 + 60 * i + 3;
			pos[3 + i].h = pausado->clip_rect.h;// pone los anchos y largos de las texturas
			pos[3 + i].w = pausado->clip_rect.w;

			medio.w = 50 + pos[0].w;
			medio.x = 320 - medio.w/2;
			medio.y = 320 - pausado->clip_rect.h/2 + 60 * i;
			medio.h = pausado->clip_rect.h + 10;

			SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);

			SDL_RenderFillRect(renderer, &medio);
			SDL_RenderCopy(renderer, texture, NULL, &pos[3 + i]);

			pos[3 + i].w = medio.w;
			pos[3 + i].h = medio.h;
			pos[3 + i].x = medio.x;
			pos[3 + i].y = medio.y;

			SDL_DestroyTexture(texture);//limpia la textura y la superficie, para que la memoria no se llene de basura
			SDL_FreeSurface(pausado);
		}
	}
	if(estado.win) // si gano renderiza ganaste!
	{
		const char ganar[] = "GANASTE!";
		SDL_Color colorGanar = {10, 255, 10, 255};
		SDL_Surface* ganarSurf = TTF_RenderText_Solid(font, ganar, colorGanar);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, ganarSurf);
		rect1.h = ganarSurf->clip_rect.h * 4;
		rect1.w = ganarSurf->clip_rect.w * 4;
		rect1.x = 320 - rect1.w/2;
		rect1.y = 320 - rect1.h/2 - 100;

		SDL_RenderCopy(renderer, texture, NULL, &rect1);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(ganarSurf);
	}

    //Presenta el dibujo
    SDL_RenderPresent(renderer);
}


