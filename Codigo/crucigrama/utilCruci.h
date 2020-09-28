void significado(char select[]);
int entraSimple(int i, int j, int direccion, int izq, int der);
int nochoca(int i, int j, const char crucigrama[][15], char palabra[], int direccion, int izq, int der);
void randVec(int* aux, int tam);
int esNum(char car);
int esletra(char pal[]);






void significado(char select[])//imprime el significado de la palabra
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "Ok" },
        //{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, select },
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
        "        Significado", /* .title */
        select, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {    //manda el mensaje
        SDL_Log("error en el mensaje de texto");
        //return 1;
    }
}






void popup()//imprime la informacion necesaria
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "Ok" },
        //{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, select },
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
        "informacion", /* .title */
        "Apreta enter para mandar el crucigrama cuando completetes todo \nA la derecha estan las posiciones de la primera letra, la direccion y el significado (si apretas) de las palabras \npara insertar una letra apretar con el mouse el lugar y escribir\nTAB para reiniciar el crucigrama\nSeleccionar la letra con las flechas o con el cursor la posicion", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {    //manda el mensaje
        SDL_Log("error en el mensaje de texto");
        //return 1;
    }
}







void winpopup()//imprime que gano
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "Ok..." },
        //{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, select },
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
        "Gano", /* .title */
        "Ganaste!!!", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {    //manda el mensaje
        SDL_Log("error en el mensaje de texto");
        //return 1;
    }
}






int cmpfunc (const void * a, const void * b) //para el quicksort
{
   return ( *(int*)a - *(int*)b );
}





int compare (const void * a, const void * b) { //Parametro de ordenamiento de qsort, de mayor long de palabra a menor
    size_t fa = strlen((const char *)a);
    size_t fb = strlen((const char *)b);
    return (fb > fa) - (fb < fa);
}





int entraSimple(int i, int j, int direccion, int izq, int der)// posicion x, y de donde se chocan, direccion de la palabra con la que se coloca
{
	if(direccion == 0) // si esta horizontal se pone vertical la otra palabra
	{
		if( ((i - izq) >= 0)  &&  ((i + der) < 15))
		{
			return 1;
		}
		else
			return 0;
	}else{
		if( (j - izq >= 0)  &&  (j + der < 15))
			return 1;
		else
			return 0;
	}

}





int nochoca(int i, int j, const char crucigrama[][15], char palabra[],int direccion, int izq, int der)//palabra a meter = mat[index][inter.index2]
{
	int contador=0,a;
	int Si,Sj;// starti startj
	if(direccion == 0) // si esta horizontal se pone vertical la otra palabra
	{
		Si = i - izq; // posicion inicial si se pone vertical la palabra
		for(a = Si ; contador < strlen(palabra); contador++, a++) //desde el inicio de la palabra al final
		{
			if(crucigrama[a][j]!=' ')
			{
				if(crucigrama[a][j] != palabra[contador]) // si el caracter que esta en la matriz no es igual al de la palabra retorna que no se puede poner
				{
					return 0;
				}
			}
		}
	}
	else //esta horizontal
	{

		//Si = i; // posicion inicial si se pone vertical la palabra
		Sj = j - izq;
		for(a = Sj ; contador < strlen(palabra); contador++, a++)
		{
			if(crucigrama[i][a]!=' ')
			{
				if(crucigrama[i][a] != palabra[contador])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}





void generarPalabras(char matpal[20][16] ,char matsign[20][200])// lee del diccionario
{

	FILE* fp = fopen("Diccionario-significados.txt", "r"); // abre el diccionario
	if(!fp)
		printf("falta el Diccionario-significados.txt\n");
	char NDicc[20], actual, numero[6], leido[20], signif[210];
	int posNum, posLei, posAux=0, posSig, aux[20];
	fscanf(fp, "%s", NDicc); // la primera linea es el numero de elementos del deccionario
	int error = 1;
	while(error) // aveces hay errores en la lectura del archivo
	{
		error = 0;
		randVec(aux, atoi(NDicc)); // genera 20 numeros aleatorios entre 1 y el numero de elementos
		qsort(aux, 20, sizeof(int), cmpfunc);// ordena el vector para buscar del deccionario

		while(!feof(fp) && posAux < 20 && !error)  //leer como esta en el diccionario numero-palabra-significado
		{
			posNum = posLei = posSig = 0;
			signif[0] = '\0';leido[0] = '\0';
			actual = getc(fp);
			while(actual != '-' && esNum(actual) && posNum < 5 )//lee el numero
			{
				numero[posNum] = actual;
				//printf("%c", actual);
				actual = getc(fp);
				posNum++;
			}
			numero[posNum]='\0';//

			if(atoi(numero) == aux[posAux])// si es la palabra buscada
			{
				actual = getc(fp);
				while(actual != '-' && actual != '\n' && posLei < 17)//lee la palabra
				{
					leido[posLei] = actual;
					actual = getc(fp);
					posLei++;
				}
				leido[posLei] = '\0';
				if(posLei > 16)
					error = 1;
				actual = getc(fp);
				while(actual != '-' && actual != '\n' && posSig < 201 && !error)//lee la palabra
				{
					signif[posSig] = actual;
					actual = getc(fp);
					posSig++;
				}
				signif[posSig] = '\0';leido[posLei] = '\0';
				if(posSig > 200)
					error = 1;
				strcpy(matpal[posAux], leido);
				strcpy(matsign[posAux], signif);
				posAux++; // para buscar el siguiente numero

				if(esletra(leido))
					error=1;

			}
			if (error)
				rewind(fp);
		}
	}
}




int esletra(char pal[])
{
	char letras[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	int es = 0;
	for (int i=0; i<strlen(pal); i++)
	{
		es= 0;
		for (int j=0; j<strlen(letras); j++)
		{
			if(pal[i] == letras[j])
			{
				es = 1;
			}
		}
		if (!es)
			return 0;
	}
	return 1;
}




int esletrachar(char pal)
{
	char letras[] = "qwertyuiopasdfghjklzxcvbnm";
	int es = 0;
	for (int j= 0; j<strlen(letras); j++)
	{
		if(pal == letras[j])
		{
			es = 1;
		}
	}
	return es;
}




void randVec(int* aux, int tam) //genera un vector aleatorio
{
	aux[0] = rand()%tam+1;// tam es el numero de palabras en google6.txt
	for(int i=1; i<20; i++)
	{
		aux[i]=(rand()%tam)+1;
		for(int j = 0; j<i; j++)
		{
			if(aux[j] == aux[i])
			{
				i--;
				break;
			}
		}
	}
}




int esNum(char car)//cheackea si es un numero
{
	char nums[]= {'1','2','3','4','5','6','7','8','9','0'};
	int si = 0;
	for(int i=0; i<10; i++)
	{
		if(car == nums[i])
		{
			si = 1;
			break;
		}
	}
	return si;
}



void imprimir(char cruci[][15])
{
	for(int i=0 ; i<15 ; i++){
		for(int j=0 ; j<15 ; j++){
			printf("%c",cruci[i][j]);
		}
		printf("\n");
	}
}



void imprimirBien(char cruci[][15])
{
	int i,j;
	printf("   ");
	for (i=0; i<15; i++)
		printf("%2d ", i);
		printf("\n");
	for (i=0; i<16; i++)
	{
		for (j=0; j<16; j++)
		{
			if(j == 0)
			{
				printf("%2d ", i-1);
			}

			if(i && j)
				printf("%2c ", cruci[i-1][j-1]);
		}
		printf("\n");
	}
	printf("\n");
}




void situarCruci(Situada pal, char crucigrama[][15])//pasa una palabra al crucigrama
{
	int contador=0,a;
	int Si,Sj;// starti startj
	int i,j;

	i = pal.i;
	j = pal.j;
	Si = i;
	Sj = j;

	if(pal.direc) // si esta horizontal se pone vertical la otra palabra
	{
		Si = i; //- izq; // posicion inicial si se pone vertical la palabra
		//Sj = j;
		for(a = Si ; contador < strlen(pal.palabra); contador++, a++)
		{
				//printf("%c\n", pal.palabra[contador]);
				crucigrama[a][j] = pal.palabra[contador];
		}
	}
	else //esta horizontal
	{
		//Si = i; // posicion inicial si se pone vertical la palabra
		Sj = j;// - izq;
		for(a = Sj ; contador < strlen(pal.palabra); contador++, a++)
		{
				crucigrama[i][a] = pal.palabra[contador];

		}
	}
}




void append(char* s, char c)	//Agrega la letra en comun a la string de letras comunes
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}


