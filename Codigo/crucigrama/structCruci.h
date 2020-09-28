typedef struct{
    int direc; //0 para horizontal,1 para vertical
    char palabra[16];
    int used;
    int j;	//Pos inicial en x de la palabra	x=columnas
    int i;	//Pos inicial en y de la palabra 	y=filas
}Situada;
