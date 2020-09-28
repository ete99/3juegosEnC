typedef struct
{
    int x, y;
} Pos;

typedef struct
{
    int x, y, //posicion actual
    dim, //dimesion de un cuadrado
    l,r,u,d, // direccion actual
    lpas,rpas,upas,dpas, // direccion pasada
	pasos, puntos, win, maximo; // pasos dados y puntos
    Pos manz;
} Snk;


typedef struct
{
	Pos pos[18*18];// numero de casillas
	int longitud;//longuitud de la cola
}Cola;
