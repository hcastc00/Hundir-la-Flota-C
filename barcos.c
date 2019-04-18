#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBARCOS1 4
#define NUMBARCOS2 2
#define NUMBARCOS3 1
void limpiarPantalla();
int menu();
void hundirLaFlota(int opcion, int f,  int c);
void colocarBarcosManualmente(int *t, int f, int c);
void colocarBarcosAutomaticamente(int *t, int f, int c);
void inicializarTablero(int *t, int f, int c);
void imprimirTablero(int *t, int f, int c);
void imprimirTableroArchivo(int *t, int f, int c, FILE *pa);
int comprobacionEspacioParaBarco(int *t, int f, int c, int iniFila, int iniCol, int tamBarco, int orientacion);
int compruebaGanador (int *b, int f, int c);
int compruebaDisparo(int *t, int f, int c, int posFila, int posCol);
void juegoManual(int f, int c);
void juegoAutomatico(int f, int c);

int main(int argc, char *argv[]){
//Función principal. 
//	- comprueba que el número de argumentos del main es correcto. 
//		--Si no son correctos, mensaje de error y fin del programa
//		--Si son correctos:
//				--- lee las filas y las columnas del tablero
//				--- mientras la opción leída no sea 3, juega al hundir la flota 
	
	limpiarPantalla();
	if (argc<3){
		printf("No ha introducido correctamente el numero de filas y columnas del tablero.\n");
		return -1;
	}

	int filas = atoi(argv[1]);
	int columnas = atoi(argv[2]);
	
	int *barcosJ1, *barcosJ2, *disparoJ1, *disparoJ2;
	barcosJ1 = (int *)malloc(filas*columnas*sizeof(int));
	barcosJ2 = (int *)malloc(filas*columnas*sizeof(int));
	disparoJ1 = (int *)malloc(filas*columnas*sizeof(int));
	disparoJ2 = (int *)malloc(filas*columnas*sizeof(int));

	inicializarTablero(barcosJ1,filas,columnas);
	inicializarTablero(barcosJ2,filas,columnas);
	inicializarTablero(disparoJ1,filas,columnas);
	inicializarTablero(disparoJ2,filas,columnas);
	
	int seleccion = menu();

	switch(seleccion){
		case 2:
			printf("Pc VS PC\n");
			break;
		case 3:
			printf("Hasta la próxima!\n");
			return 0;
			break;
		case 4:
			limpiarPantalla();
			colocarBarcosAutomaticamente(barcosJ1, filas, columnas);
			break;
		case 5:
			limpiarPantalla();
			colocarBarcosManualmente(barcosJ2, filas, columnas);
			break;
		case 6:
			limpiarPantalla();
			menu();
			break;
	}

}

void limpiarPantalla(){
	printf("\e[1;1H\e[2J");
}

int menu(){
//Función menu.
//	- INPUTS: nada
//	- OUTPUTS: la opción leída (1, 2 ó 3)
//  - Presenta el menú por pantalla y lee una opción. Si no es 1, 2 ó 3 da un mensaje de error y vuelve a leerla hasta que sea correcta.
	int select;
		//Imprime el menu inicial
		printf("\n");
		printf("\t#============================================#\n");
		printf("\t#   [1] Jugar (ordenador vs jugador)         #\n");
		printf("\t#   [2] Jugar (ordenador vs ordenador)       #\n");
		printf("\t#   [3] Salir                                #\n");
		printf("\t#============================================#\n");
		printf("\n");

		//Lee opcion
		scanf("%d",&select);
		//Comprueba opcion
		if (select > 0 && select <= 3){
			switch(select){
			case 1:
				printf("\n");
				printf("\t#============================================#\n");
				printf("\t#   [1] Colocar barcos automáticamente       #\n");
				printf("\t#   [2] Colocar barcos manualmente           #\n");
				printf("\t#   [3] Volver                               #\n");
				printf("\t#============================================#\n");
				printf("\n");
				
				scanf("%d",&select);
				return(select + 3);
				break;
			case 2:
			case 3:	
				return select;
				break;
			}
		}	
		
		else{
			printf("\nLa opción introducida no es válida\n");
			menu();
		//Menu de juego

	}
	
}

void hundirLaFlota(int opcion, int f,  int c){
//Función hundirLaFlota
//	- INPUTS: opción (1, 2 ó 3), filas y columnas del tablero
//  - OUTPUTS: nada
//  - Según la opción leída llama a jugar manual (opción 1), jugar automático (opción 2) o muestra un mensaje de fin (opción 3)


}	
void juegoManual(int f, int c){
//Función juegoManual
// 	- INPUTS: número de filas y número de columnas del tablerro
//	- OUTPUTS: nada
//	- Juega de forma manual:
//		-- Crea los 4 tableros, los inicializa (llamando a la función inicializar tantas veces como tableros haya) y en 2 pone los barcos de forma manual o automática, según indique el usuario
//		-- Escribe por pantalla los tableros y las tiradas al inicio del juego
//		-- Por turnos, cada jugador elige una fila y columna de 1 al número de filas y de 1 al número de columnas. Se comprueba si hay barco indicando agua o tocado (se indica por pantalla).
//		-- Se comprueba si hay ganador. Si lo hay acaba la partida indicando quíén ha ganado por pantalla
//		-- EXTRA: comprobar que no se ha repetido ese disparo

}
void juegoAutomatico(int f, int c){
//Función juegoAutomatico
// 	- INPUTS: número de filas y número de columnas del tablerro
//	- OUTPUTS: nada
//	- Juega de forma automática:
//		-- Abre el archivo para escribir en él todas las salidas
//		-- Crea los 4 tableros, los inicializa (llamando a la función inicializar tantas veces como tableros haya) y en 2 pone los barcos automáticamente
//		-- Escribe en el archivo los tableros y las tiradas al inicio del juego
//		-- Por turnos, cada jugador genera una fila y columna automáticamente (se indica en el archivo). Se comprueba si hay barco indicando agua o tocado (se indica en el archivo).
//		-- Se comprueba si hay ganador. Si lo hay acaba la partida indicando quíén ha ganado en el archivo
//		-- EXTRA: comprobar que no se ha repetido ese disparo


	return;
}


void inicializarTablero(int *t, int f, int c){
//Función inicializarTablero
//INPUTS:
//	- puntero a un tablero (barcos, tiradas o lo que sea)
//	- filas
//	- columnas
//OUTPUS: nada
//Inicializa a 0 la tabla
	int i,j;
	for (i = 0; i < f*c; i++){
		*(t+i)=0;
	}
	return;
}

void imprimirTableroArchivo(int *t, int f, int c, FILE *pa){
//Función imprimirTableroArchivo
//INPUTS:
//	- puntero a un tablero (barcos, tiradas o lo que sea)
//	- filas
//	- columnas
// 	- puntero a archivo
//OUTPUTs: nada
//Imprime en el archivo la matriz pasada	
	
	return;
}

int compruebaGanador (int *b, int f, int c){
//Función compruebaGanador
//INPUTs:
//	- puntero a un tablero de barcos
//	- filas
//	- columnas
//OUTPUTS: nada
//Busca si quedan barcos por hundir. Si no, devuelve 0. 
	
}

int compruebaDisparo(int *t, int f, int c, int posFila, int posCol){
//Función compruebaDisparo
//INPUTS:
//	- tablero de barcos
//	- filas
//	- columnas
//	- tiro (fila y columna)
//OUTPUTS: 0 si agua, 1 si hay un barco de 1, 2 si hay un barco de 2, 3 si hay un barco de 3
	
}

int comprobacionEspacioParaBarco(int *t, int f, int c, int iniFila, int iniCol, int tamBarco, int orientacion){
//Función comprobacionEspacioParaBarco
//INPUTS:
//	- tablero de barcos
//	- filas
//	- columnas
//	- posición (fila)
//	- posición (columna)
//	- tamaño del barco (1, 2 ó 3)
//	- orientación (0 horizontal, 1 vertical)
//OUTPUTS: 1 si cabe, 0 si no cabe
//Comprueba si cabe un barco a partir de la posición indicada en la orientación indicada. Devuelve 0 si no cabe, 1 si sí.
	int i,hueco=0;

	//HORIZONTAL
	if (orientacion == 0){

		for (i = 0; i < tamBarco; i++){
			if (*(t+(iniFila*c)+iniCol+i)==0){
				hueco++;
			}
			printf("%d\n",hueco);
		}
	}

	//VERTICAL
	else if (orientacion==1){
		for (i = 0; i < tamBarco; i++){
			if (*(t+(iniFila+i)*c+iniCol)==0){
				hueco++;
			}
		}
	}
	
	else{
		printf("ORIENTACION INVALIDA\n");
		return -1;
	}
	
	if(hueco==tamBarco){
		return 1;
	}
	else{
		return 0;
		}
}

void colocarBarcosAutomaticamente(int *t, int f, int c){
//Función colocarBarcosAutomaticamente
//INPUTS:
//	- Tablero de barcos
//	- filas
//	- columnas	
//OUTPUTS: nada
//Coloca de forma manual 4 barcos de 1 posición, 2 de 2 posiciones y 1 de 3 posiciones en el tablero
	
}


void colocarBarcosManualmente(int *t, int f, int c){
//Función colocarBarcosManualmente
//INPUTS:
//	- Tablero de barcos
//	- filas
//	- columnas	
//OUTPUTS: nada
//Coloca de forma manual 4 barcos de 1 posición, 2 de 2 posiciones y 1 de 3 posiciones en el tablero
}