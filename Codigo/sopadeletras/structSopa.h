#define CANTP 500//cantidad maxima de palabras en el vector encontrados
#define TAM 16 //tamanho maximo de una palabras
#define M 12 // filas
#define N 15 // columnas

typedef struct palabrix { //cada letra tiene un posicion, un caracter y si esta highlighteado
	char car;
	int posx, posy;
	int high;
} Palabra;

typedef struct estadix { //estado del juego
	int win, puntos, tempo, nuevo;
	int matbin[N][N];
	int i,j; //usado en el juego de crucigrama
} Estado;

typedef struct unix {
	int valido;
	char palabra[16];
} Unico; // palabra unica
