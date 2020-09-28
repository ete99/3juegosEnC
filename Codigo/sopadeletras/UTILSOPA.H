void generarSopa(Palabra matriz[][N]);
void BuscarMatriz(Palabra matriz[][N]);
void invertir(Palabra vec[]);
void imprimirPalabra(Palabra vec[]);
void BuscarDicc(Palabra vec[]);
void BuscarPalabra(Palabra vec[]);
void CompararDicc(Palabra vec[], char palabra[]);
void palACadena(const Palabra vec[], char direccion[]);
void copiaPalabra(Palabra direccion[], Palabra fuente[]);
int estaEncontrado(Palabra seleccion[]);
int PalLen(Palabra vec[]);
void enconAunicos();
int pregunta(char select[], char inverso[]);
int palabraDesconocida(Palabra seleccion[], Estado *estado);



Palabra encontrados[CANTP][TAM]; // palabras encontradas por el algoritmo
Unico unicos[200]; // palabras encontradas pero solo una, para imprimir
int cantENC = 0; // sigue la cantidad de palabras encontradas
int cantENCU = 0;




void generarSopa(Palabra matriz[][N])
{
	setlocale(LC_ALL, "spanish");// para usar la Ñ
	srand(time(NULL));
	int i,j;

	const char palabra[]="AAAABBCCCDDEEEEFFGGHIIIJKLLMMNNÑOOOOPPPQRRSSSTTUUVWXYZ";

	for(i=0 ; i<M ; i++){
		for(j=0 ; j<N ; j++){
			matriz[i][j].car=palabra[rand()%strlen(palabra)];//elije una letra aleatoria del vector
			matriz[i][j].posx=j;
			matriz[i][j].posy=i;
		}
	}

	BuscarMatriz(matriz); //busca las palabras en el diccionario

	enconAunicos(); //pasa las palabras encontradas al vector unicos


}



//recorre de todas las direcciones el vector
void BuscarMatriz(Palabra matriz[][N])
{
	int i,j;
	Palabra vec[N+1];
	/*usar un vector para buscar palabras de un archivo diccionario, si se encunetra guardar la palabra encontrada y las posiciones de todas las letras*/

	/*recorre horizontalmente*/
	for(i=0 ;i<M ; i++){
		for(j=0 ; j<N ; j++){
			vec[j]=matriz[i][j];
		}
		vec[j].posx=-1;
		BuscarPalabra(vec);
	}

	/*recorre vecticalmente*/
	for(j = 0 ; j < N ;  j++){
		for(i = 0 ; i < M ; i++){
			vec[i]=matriz[i][j];
		}
		vec[i].posx=-1;
		BuscarPalabra(vec);
	}

	/*recorre diagonalmente*/
	//recorre el triangulo superior
	for (int FI = 2; FI < M; ++FI)
	{
		for (i = 0; i < FI; ++i)
		{
			vec[i]=matriz[M+i-FI][i];
		}
		vec[i].posx=-1;// marca el final del vector poniendo posx en -1
		BuscarPalabra(vec);
	}

	//recorre el medio diagonal
	for (int FI = 0; FI < 4; ++FI)
	{
		for (i = 0; i < M; ++i)
		{
			//matriz[i][i+FI].car='M'+FI-2;
			//printf("%d %d\n", i, i+FI);
			vec[i]=matriz[i][i+FI];

		}
		vec[i].posx=-1;
		BuscarPalabra(vec);
	}

	//recorre el triangulo inferior
	int FI, cc=1; // cc es un contador para regular cuantos elementos se leen diagonalmente
	for(FI=4; FI<14; FI++)
	{
		for (i=0; i<M-cc; i++)
		{
			//matriz[i][i+FI].car='M'+FI-2;
			//printf("%d %d\n", i, i+FI);
			vec[i]=matriz[i][i+FI];
		}
		vec[i].posx=-1;
		cc++;
		BuscarPalabra(vec);
	}

	//recorre el triangulo superior de la diagonal inversa
	for(int FI=1; FI< M - 1; FI++)
	{
		for (i=0; i<FI+1; i++)
		{
			//matriz[FI - i][i].car='a'+FI;
			vec[i] = matriz[FI - i][i];
		}
		vec[i].posx=-1;
		BuscarPalabra(vec);
	}
	//recorre el medio de la diagonal inversa
	for (int FI=0; FI<4; FI++)
	{
		for (i=0; i<M; i++)
		{
			//matriz[M -1 -i][i + FI].car='x';
			vec[i] = matriz[M -1 -i][i + FI];
		}
		vec[i].posx=-1;
		BuscarPalabra(vec);
	}

	//recorre el triangulo inferior de la diagonal inversa
	cc=1;
	for (int FI=4; FI<N-1; FI++)
	{
		for (i=0; i<M-cc; i++)
		{
			//matriz[M -1 -i][i + FI].car='a'+FI;
			vec[i] = matriz[M -1 -i][i + FI];
		}
		cc++;
		vec[i].posx=-1;
		BuscarPalabra(vec);
	}

	/*termina la busqueda*/
}



//si esta en las palabras encontradas
int estaEncontrado(Palabra seleccion[])
{
	int esta = 0;
	int Coincid[cantENC];
	int posSelecc = 0, posEncon = 0;
	for (int i=0; i<cantENC; i++)
	{
		Coincid[i] = 0; // coincid cuenta la cantidad de letras que coinciden con lo seleccionado y las palabras encontradas en la matriz
	}
	/*
	compara cada letra con cada palabra encontrada en la matriz.
	si esta la letra entonces suma uno a Coincid.
	*/
	while(seleccion[posSelecc].posx != -1)
	{
		for (int i=0; i<cantENC; i++)
		{
			posEncon = 0;
			while(encontrados[i][posEncon].posx != -1)
			{
				if(encontrados[i][posEncon].posx == seleccion[posSelecc].posx && encontrados[i][posEncon].posy == seleccion[posSelecc].posy)
				{
					Coincid[i]++;
				}
				posEncon++;
			}
		}
		posSelecc++;
	}
	/*
	si contiene todas las "letras" y si tiene la misma cantidad de letras
	*/
	for (int i=0; i < cantENC; i++)
	{
		if(Coincid[i] == PalLen(encontrados[i]) && PalLen(seleccion) == PalLen(encontrados[i]))
		{
			//copiaPalabra(seleccion, encontrados[i]);
			char encon[20];
			palACadena(encontrados[i], encon);
			for(int j = 0; j < cantENCU; j++)
			{

				if(strcmp(encon, unicos[j].palabra) == 0)
				{
					if(unicos[j].valido == 1)
					{
						unicos[j].valido = 0;// ya no se puede repetir la palabra
						return 1;
					}
					else
					{
						return -1;
					}

				}
			}
			break;
		}
	}
	return esta;
}



//recorre las palabras encontradas y pone las unicas
void enconAunicos()
{
	char buscado[20], actual[20];
	int repetido[cantENC];

	for (int i=0; i<cantENC; i++)
	{
		repetido[i] = 0;
	}

	for (int i=0; i<cantENC; i++)
	{
		palACadena(encontrados[i], buscado);
		for (int j=0; j<cantENC; j++)
		{
			palACadena(encontrados[j], actual);
			if((i != j) && (strcmp(buscado, actual) == 0)) // si no es la misma palabra y esta repetida ignora
			{
				repetido[j] = 1;
			}
		}

		if(!repetido[i])// si cantidad es 0 entonces mete a los unicos
		{
			strcpy(unicos[cantENCU].palabra, buscado);
			unicos[cantENCU].valido = 1;
			cantENCU++;
			//printf("%s\n", buscado);
		}
	}
}



//retorna la longitud de la palabra
int PalLen(Palabra vec[])//obtiene la longitud de la palabra
{
	int len = 0;
	while(vec[len].posx != -1)
	{
		len++;
	}
	return len;
}



//compara la palabra con el diccionario
void CompararDicc(Palabra vec[], char palabra[])
{
	char buscado[TAM];// una cadena a la que pasamos vec
	int i = 0;
	palACadena(vec, buscado);

	char *ptr = strstr(buscado, palabra); // busca si es un subtring
	if(ptr != NULL && cantENC < CANTP){ // si es un subtring marca sus coordenadas y pasa al vector encontrados
		int pos=(int)(ptr-buscado);
		for(i=pos; i<strlen(palabra) + pos; i++)
		{
			//coor[vec[i].posy][vec[i].posx] = 1; //marcar con encontrados las palabras
			encontrados[cantENC][i - pos] = vec[i];
		}
		encontrados[cantENC][i - pos].posx = -1;
		cantENC++;
	}
}




void BuscarDicc(Palabra vec[])//busca en el diccionario si existe la palabra
{
	FILE* fp;
    fp = fopen("Diccionario.txt", "r"); //abre el diccionario
    if(!fp)
		printf("falta el Diccionario.txt\n");
    char word[20];
    while(!feof(fp))
	{
		fscanf(fp, "%s", word);
    	CompararDicc(vec, word);
	}
	fclose(fp);
}



//busca, invierte y busca en el diccionario
void BuscarPalabra(Palabra vec[]) //busca en el diccionario, invierte y busca devuelta
{
	BuscarDicc(vec);
	invertir(vec);
	BuscarDicc(vec);
}



//invierte una palabra
void invertir(Palabra vec[])
{
	int i=0, fin;
	Palabra aux;
	while(vec[i].posx != -1)
	{
		i++;
	}
	fin=i-1;
	for(i=0; i < (int)(fin + 1)/2; i++)
	{
		aux = vec[i];
		vec[i] = vec[fin-i];
		vec[fin-i] = aux;
	}
}
//imprime una palabra


void imprimirPalabra(Palabra vec[])
{
	int k = 0;
	while(vec[k].posx != -1)
	{
		printf("%c", vec[k].car);
		k++;
	}
}
//transforma una Palabra a una cadena



void palACadena(const Palabra vec[], char direccion[])
{
	int i=0;
	while(vec[i].posx != -1)// convierte a cadena el vector estructura
	{
		direccion[i]=vec[i].car;
		i++;
	}
	direccion[i]='\0';// termina la cadena
}



//copia una palabra a la otra, solo funciona si son de igual longitud

void copiaPalabra(Palabra direccion[], Palabra fuente[])
{
	int i = 0;
	while(fuente[i].posx != -1)// convierte a cadena el vector estructura
	{
		direccion[i] = fuente[i];
		i++;
	}
	direccion[i].posx = -1;
}



int pregunta(char select[], char inverso[]) //pregunta si es una pregunta palabra de verdad
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "No" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, select },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, inverso },
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
        "        Palabra nueva", /* .title */
        "Seguro que es una palaba?\nSi esta seguro apriete su palabra\nSi no apriete \"No\"", /* .message */
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

/*
agrega una palabra desconocida por el diccionario al diccionario,
posibles errores, que elija mal una respuesta, o que marque una palabra de forma no linear.
*/

int palabraDesconocida(Palabra seleccion[], Estado *estado)
{
	char select[20], inverso[20];
	palACadena(seleccion, select);
	invertir(seleccion);
	palACadena(seleccion, inverso);
	int respuesta = pregunta(select, inverso);
	if ( respuesta == 1) // muestra el mensaje que pregunta si es o no una palabra
	{
		//si responde que si agrega al diccionario
		FILE *fp = fopen("Diccionario.txt", "a");
		if(!fp)
		printf("falta el Diccionario.txt\n");
		fprintf(fp, "%s\n", select);
		fclose(fp);
	}
	else if ( respuesta == 2 )
	{
		FILE *fp = fopen("Diccionario.txt", "a");
		if(!fp)
			printf("falta el Diccionario.txt\n");
		fprintf(fp, "%s\n", inverso);
		fclose(fp);
	}
	return respuesta;
}
