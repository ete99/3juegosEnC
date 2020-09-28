void renderCruci(SDL_Renderer *renderer, TTF_Font *font,TTF_Font *fontMenu, SDL_Rect pos[], SDL_Rect posc[][N], SDL_Rect pospalabras[], int pausa, const char matriz[][N], Estado estado);





void renderCruci(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *fontMenu, SDL_Rect pos[], SDL_Rect posc[][N], SDL_Rect pospalabras[], int pausa, const char matriz[][N], Estado estado)
{
		//setlocale(LC_ALL, "spanish");// para usar la Ñ
		//set the drawing color to blue
		SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);

		//Clear the screen (to blue)
		SDL_RenderClear(renderer);

		//hace un cuadro rojo
		SDL_SetRenderDrawColor(renderer, 127, 0, 0, 255);
		SDL_Rect rect2 = { 0, 0, 565, 565 };
		SDL_RenderFillRect(renderer, &rect2);

		//hace un cuadro rojo
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_Rect rect3 = { 10, 10, 545, 545 };
		SDL_RenderFillRect(renderer, &rect3);

		SDL_Color colortexto = { 240,240,240,255};
		SDL_Rect cuadroTex;

		SDL_Rect mrec, mrec2;
		SDL_Surface* cuadroMat;

		//SDL_Texture *texture;
		char let[10];
		int dim = 35;

		for (int i=0; i<N; i++)
		{
			for (int j=0; j<N; j++)
			{
				mrec.h=dim;
				mrec.w=dim;
				mrec.x=20+j*dim;
				mrec.y=20+i*dim;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &mrec);

				mrec2.h=dim-4;
				mrec2.w=dim-4;
				mrec2.x=21 + j*dim;
				mrec2.y=21 + i*dim;


				SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);//color base gris

				if(matriz[i][j] != ' ') // sie esta highlighteado cambia de color el fondo
				{
					if(estado.i == i && estado.j == j)
						SDL_SetRenderDrawColor(renderer, 255, 100, 110, 255);
					else
						SDL_SetRenderDrawColor(renderer, 174, 0, 10, 255);
				}
				SDL_RenderFillRect(renderer, &mrec2);

				let[0] = matriz[i][j]; //pasa el caracter a una cadena para imprimir
				if(let[0] == '/')
					let[0]=' ';
				let[1]='\0'; //cierra la cadena

				cuadroMat = TTF_RenderText_Solid(font, let, colortexto);

				SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, cuadroMat);

				posc[i][j].x = mrec.x + 17 - cuadroMat->clip_rect.w/2;
				posc[i][j].y = mrec.y + 17 - cuadroMat->clip_rect.h/2;
				posc[i][j].h = cuadroMat->clip_rect.h;// pone los anchos y largos de las texturas
				posc[i][j].w = cuadroMat->clip_rect.w;

				SDL_RenderCopy(renderer, texture, NULL, &posc[i][j]);

				SDL_DestroyTexture(texture);
				SDL_FreeSurface(cuadroMat);

				posc[i][j] = mrec;
			}
		}
        const char veinnum[20][3] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
			//imprimir los numeros deposicion horizontales


		for (int posa=0; posa<15; posa++)
		{
			SDL_Rect numeros;
			numeros.h=35;
			numeros.w=35;
			numeros.x=20+posa*35;
			numeros.y=0;

			SDL_Surface *surfnum = TTF_RenderText_Solid(font, veinnum[posa], colortexto);

			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surfnum);

			numeros.x = numeros.x + 20 - surfnum->clip_rect.w/2;
			numeros.y = 20 - surfnum->clip_rect.h/4*3; // + cuadroMat[i]->clip_rect.h/2;
			numeros.h = surfnum->clip_rect.h/4*3;// pone los anchos y largos de las texturas
			numeros.w = surfnum->clip_rect.w/4*3;

			SDL_RenderCopy(renderer, texture, NULL, &numeros);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surfnum);

		}

		//imprimir los numeros deposicion verticales


		for (int posa=0; posa<15; posa++)
		{
			SDL_Rect numeros;
			numeros.h=35;
			numeros.w=35;
			numeros.x=0;
			numeros.y=20+posa*35;

			SDL_Surface *surfnum = TTF_RenderText_Solid(font, veinnum[posa], colortexto);

			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surfnum);

			numeros.x = 20 - surfnum->clip_rect.w/4*3;
			numeros.y = numeros.y + 20 - surfnum->clip_rect.h/2; // + cuadroMat[i]->clip_rect.h/2;
			numeros.h = surfnum->clip_rect.h/4*3;// pone los anchos y largos de las texturas
			numeros.w = surfnum->clip_rect.w/4*3;

			SDL_RenderCopy(renderer, texture, NULL, &numeros);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surfnum);

		}



	SDL_Rect rect1 = { 640, 0, 320, 640 };

	//dibuja la cabecera de los encontrados

	char cabecera[]= "Significados (fila,column) direccion";

	SDL_Surface *encontr = TTF_RenderText_Solid(font, cabecera, colortexto);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, encontr);
	cuadroTex.y = encontr->clip_rect.h/2 - 10;
	cuadroTex.w = encontr->clip_rect.w/5*4;
	cuadroTex.x = 640 + 120 - cuadroTex.w/2;
	cuadroTex.h = encontr->clip_rect.h/5*4;
	SDL_RenderCopy(renderer, texture, NULL, &cuadroTex);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(encontr);

	//dibuja las palabras

	SDL_Color colorbi = { 240,240,240,255};
	//SDL_Rect cuadroTex;
    SDL_Rect Rencon, hecho;

    for (int i=0; i<20; i++)
    {
    	//printf("palabras[%d]= %s\n", i,palabras[i]);
    	SDL_Surface *PalEncon = TTF_RenderText_Solid(font, palabras[i], colorbi);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, PalEncon);

		hecho.w = 200;
		hecho.x = 640 + 30 + 100;
		Rencon.x = hecho.x - PalEncon->clip_rect.w/2;// 640 = tamanho del juego , 160 = el tamanho del menu /2
		Rencon.y = PalEncon->clip_rect.h/2 +  PalEncon->clip_rect.h * (i) + PalEncon->clip_rect.h - 10;
		Rencon.h = PalEncon->clip_rect.h;// pone los anchos y largos de las texturas
		Rencon.w = PalEncon->clip_rect.w;

		//dimesiones del cuadrado del fondo
		hecho.w = 200;
		hecho.x = 640 + 30;
		hecho.y = Rencon.y;
		hecho.h = Rencon.h;

		SDL_SetRenderDrawColor(renderer, 174, 0, 1, 255); //rojo gryffindor

		SDL_RenderFillRect(renderer, &hecho);

		SDL_RenderCopy(renderer, texture, NULL, &Rencon);

		SDL_DestroyTexture(texture); //limpia la textura y la superficie, para que la memoria no se llene de basura
		SDL_FreeSurface(PalEncon);

		pospalabras[i] = hecho;
    }

    //dibuja el menu

	const char* labels[] = {"Volver al menu", "Informacion", "Salir (Esc)"}; // las cadenas necesarias
	SDL_Surface* menus[3];
	SDL_Color colorletra[2] = {{ 200,200,200,255},{255, 255, 255, 255}};
	SDL_Rect cuadroTexFondo;

	for(int i=0; i < 3; i++)
	{
		menus[i] = TTF_RenderText_Solid(fontMenu, labels[i], colorletra[0]);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, menus[i]);

		pos[i].x = 100 + (menus[0]->clip_rect.w/2 + 120) * i - menus[i]->clip_rect.w/2; // 640 = tamanho del juego , 160 = el tamanho del menu /2, menus[0]->clip_rect.w/2 = ancho de la palabra/2
		pos[i].y = 580  + menus[i]->clip_rect.h/2;
		pos[i].h = menus[i]->clip_rect.h; // pone los anchos y largos de las texturas
		pos[i].w = menus[i]->clip_rect.w;

		cuadroTex.w = 10 + pos[0].w;
		cuadroTex.x = 100 + (menus[0]->clip_rect.w/2 + 120) * i - cuadroTex.w/2;
		cuadroTex.y = 580 + menus[0]->clip_rect.h/2;
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

	if(estado.win) //si gano imprime ganaste!
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


