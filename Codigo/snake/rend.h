#include <string.h>
void render(SDL_Renderer *renderer, Snk *snk, Cola *cola, TTF_Font *font, SDL_Rect pos[], int pausa);

void render(SDL_Renderer *renderer, Snk *snk, Cola *cola, TTF_Font *font, SDL_Rect pos[], int pausa)
{

    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 127, 0, 0, 255);

    //Clear the screen (to blue)
    SDL_RenderClear(renderer);

    //hace un cuadro verde
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect2 = { 16, 16, 608, 608 };
    SDL_RenderFillRect(renderer, &rect2);

    //imprime la cuadricula
    SDL_Rect mrec;
    for (int i=0; i<18; i++)
    {
        for (int j=0; j<18; j++)
        {
            if((i+j)%2==0)
                SDL_SetRenderDrawColor(renderer, 127, 127, 127, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            mrec.h=32; //32 es el snk->dim y el tamanho asignado aa cada cuadrado
            mrec.w=32;
            mrec.x=32+j*32;
            mrec.y=32+i*32;
            SDL_RenderFillRect(renderer, &mrec);
        }
    }

    //dibuja la manzana
    SDL_Rect manzrect = { snk->manz.x, snk->manz.y, snk->dim, snk->dim};
    SDL_SetRenderDrawColor(renderer, 62, 216, 235, 255);
    SDL_RenderFillRect(renderer, &manzrect);

    //dibuja la serpiente
    SDL_Rect rect = { snk->x, snk->y, snk->dim, snk->dim};

    //dibuja la cola
    SDL_SetRenderDrawColor(renderer, 174, 255, 174, 255);
    for(int i=0; i < cola->longitud; i++)
    {
        rect.x=cola->pos[i].x;
        rect.y=cola->pos[i].y;

        SDL_RenderFillRect(renderer, &rect);
    }

    //dibuja la cabeza
    SDL_SetRenderDrawColor(renderer, 10, 255, 10, 255);
    rect.x = snk->x;
    rect.y = snk->y;
    SDL_RenderFillRect(renderer, &rect);


	//dibuja el menu
	SDL_SetRenderDrawColor(renderer, 127, 127, 127, 0);

    SDL_Rect rect1 = { 640, 0, 320, 640 };
    SDL_RenderFillRect(renderer, &rect1);

	const char* labels[] = {"Volver al menu", "Pausa (p)", "Salir (Esc)"};
	SDL_Surface* menus[3];
	SDL_Color colorletra[2] = {{ 200,200,200,255},{255, 255, 255, 255}};
	SDL_Rect cuadroTex, cuadroTexFondo;

	for(int i=0; i < 3; i++)
	{
		menus[i] = TTF_RenderText_Solid(font, labels[i], colorletra[0]);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, menus[i]);

		pos[i].x = 640 + 160 - menus[i]->clip_rect.w/2;// 640 = tamanho del juego , 160 = el tamanho del menu /2, menus[0]->clip_rect.w/2 = ancho de la palabra/2
		pos[i].y = 75 + 100 * i + menus[i]->clip_rect.h/2;
		pos[i].h = menus[i]->clip_rect.h;// pone los anchos y largos de las texturas
		pos[i].w = menus[i]->clip_rect.w;

		cuadroTex.w = 50 + pos[0].w;
		cuadroTex.x = 640 + 160 - cuadroTex.w/2;
		cuadroTex.y = 70 + 100 * i + menus[0]->clip_rect.h/2;
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

		if(i)
			SDL_FreeSurface(menus[i]);
		SDL_DestroyTexture(texture); //limpia los datos usados
	}
	SDL_FreeSurface(menus[0]);

	for (int i = 0; i < 3; ++i)
	{
		pos[i].w = pos[0].w + 50;
		pos[i].h = pos[0].h + 10;
		pos[i].x = cuadroTex.x;
	}

    //dibuja el puntaje

	char text[10], score[]= "Puntaje: ";
	sprintf(text,"%d", snk->puntos);
	strcat(score, text);
	SDL_Surface* scoreSurf = TTF_RenderText_Solid(font, score, colorletra[0]);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, scoreSurf);
	cuadroTex.y += 200;
	cuadroTex.w = scoreSurf->clip_rect.w;
	cuadroTex.x = 640 + 160  - cuadroTex.w/2;
	SDL_RenderCopy(renderer, texture, NULL, &cuadroTex);

	SDL_FreeSurface(scoreSurf);
	SDL_DestroyTexture(texture);


	if (pausa) //si esta pausado
	{
		//imprime el cuadrado del fondo

		const char* labelsPausa[] = {"Reiniciar (r)", "Resumir (espacio)"};
		for(int i=0; i < 2 - snk->win; i++)
		{
			SDL_Surface* pausado = TTF_RenderText_Solid(font, labelsPausa[i], colorletra[1]);
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, pausado);

			pos[3 + i].x = 320 - pausado->clip_rect.w/2;// 640 = tamanho del juego , 160 = el tamanho del menu /2, menus[0]->clip_rect.w/2 = ancho de la palabra/2
			pos[3 + i].y = 320 - pausado->clip_rect.h/2 + 60 * i + 3;
			pos[3 + i].h = pausado->clip_rect.h;// pone los anchos y largos de las texturas
			pos[3 + i].w = pausado->clip_rect.w;

			SDL_Rect medio = {pos[3 + i].x - 80, pos[3 + i].y - 40, pos[3 + i].w + 160, pos[3 + i].h + 150};
			SDL_SetRenderDrawColor(renderer, 224, 229, 229, 255);

			if(i==0)
				SDL_RenderFillRect(renderer, &medio);

			medio.w = 50 + pos[0].w - 50;
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

			SDL_FreeSurface(pausado);
			SDL_DestroyTexture(texture);
		}
	}
	if(snk->win) //si gano imprime ganaste!
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

		SDL_FreeSurface(ganarSurf);
		SDL_DestroyTexture(texture);
	}

    //Presenta el dibujo
    SDL_RenderPresent(renderer);
}



