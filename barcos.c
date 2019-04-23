/*
*	HUNDIR LA FLOTA
*	Práctica Estructura de Computadores 1ºIngeniria Informátoca
*	Héctor Castro Casado
*/

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
int compruebaGanador (int *t, int f, int c);
int compruebaDisparo(int *t, int f, int c, int posFila, int posCol);
void juegoManual(int f, int c);
void juegoAutomatico(int f, int c);
void salir();

int main(int argc, char *argv[]){
//Función principal. 
//	- comprueba que el número de argumentos del main es correcto. 
//		--Si no son correctos, mensaje de error y fin del programa
//		--Si son correctos:
//				--- lee las filas y las columnas del tablero
//				--- mientras la opción leída no sea 3, juega al hundir la flota 
	
	srand (time(NULL));
	limpiarPantalla();
	
	//Comprobar arguemntos
	if (argc<3){
		printf("No ha introducido correctamente el numero de filas y columnas del tablero.\n");
		return -1;
	}

	int filas = atoi(argv[1]);
	int columnas = atoi(argv[2]);

	if (filas<=5 || columnas<=5){
		printf("El tablero introducido es demasiado pequeño\n Introduzca uno de más de 5x5\n");
		return -1;
	}

	//Llamada al menu
	int seleccion = menu();

	while(seleccion!=3){
	hundirLaFlota(seleccion,filas,columnas);
	printf("\n");
	seleccion = menu();
	}	
	
	printf("Hasta la próxima!\n");
	return 0;
}

void limpiarPantalla(){
	printf("\e[1;1H\e[2J");
}

int menu(){
//Función menu.
//	- INPUTS: nada
//	- OUTPUTS: la opción leída (1, 2 ó 3)
//  - Presenta el menú por pantalla y lee una opción. Si no es 1, 2 ó 3 da un mensaje de error y vuelve a leerla hasta que sea correcta.
	int select = -1;
		//Imprime el menu inicial
		while(select<0 || select>3){
			printf("\n");
			printf("\t#============================================#\n");
			printf("\t#    [1] Jugar (ordenador vs jugador)        #\n");
			printf("\t#    [2] Jugar (ordenador vs ordenador)      #\n");
			printf("\t#    [3] Salir                               #\n");
			printf("\t#============================================#\n");
			printf("\n");
			scanf("%d",&select);
			if (select<0 || select>3){
				printf("Introduzca una opcion válida\n");
			}
		}
		return select;
}

void hundirLaFlota(int opcion, int f,  int c){
//Función hundirLaFlota
//	- INPUTS: opción (1, 2 ó 3), filas y columnas del tablero
//  - OUTPUTS: nada
//  - Según la opción leída llama a jugar manual (opción 1), jugar automático (opción 2) o muestra un mensaje de fin (opción 3)
	switch(opcion){
		case 1:
			limpiarPantalla();
			juegoManual(f,c);
			break;
		case 2:
			limpiarPantalla();
			juegoAutomatico(f,c);
			break;
	}

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
	
	int *barcosJ1, *barcosBOT, *disparoJ1;
	barcosJ1 = (int *)malloc(f*c*sizeof(int));
	barcosBOT = (int *)malloc(f*c*sizeof(int));
	disparoJ1 = (int *)malloc(f*c*sizeof(int));

	inicializarTablero(barcosJ1,f,c);
	inicializarTablero(barcosBOT,f,c);
	inicializarTablero(disparoJ1,f,c);
	
	colocarBarcosAutomaticamente(barcosBOT,f,c);
	int select = -1;
	
	//Menu de juego
	while(select<0 || select>3){
		printf("\n");
		printf("\t#============================================#\n");
		printf("\t#    [1] Colocar barcos automáticamente      #\n");
		printf("\t#    [2] Colocar barcos manualmente          #\n");
		printf("\t#    [3] Volver                              #\n");
		printf("\t#============================================#\n");
		printf("\n");
		scanf("%d",&select);
		if (select<0 || select>3){
			printf("Introduzca una opcion válida\n");
		}
	}
	
	//Colocar barcos
	switch(select){
		case 1:
			limpiarPantalla();
			colocarBarcosAutomaticamente(barcosJ1,f,c);
			break;
		case 2:
			limpiarPantalla();
			colocarBarcosManualmente(barcosJ1,f,c);
			break;
		case 3:
			return;
			break;
		default:
			printf("error\n");
			return;
	}

	//JUEGO
	printf("                             ===Intrucciones===\n");
	printf("- Los barcos se representan en los tableros con el número que de su tamaño\n");
	printf("- Cuando una casilla de un barco es impactado se representa con el el mismo valor que tenía pero negativo\n");
	printf("- Fijate antes de disparar, si ya habias bombardeado esa posición antes perderás el turno\n");
	printf("- Los disparos en agua se represntan con un 8 en tu tablero de disparos\n");
	int ganaBOT = compruebaGanador(barcosJ1,f,c);
	int ganaJ1 = compruebaGanador(barcosBOT,f,c);
	while(ganaBOT!=1 && ganaJ1!=1){
		printf("Tu tablero\n");
		imprimirTablero(barcosJ1,f,c);
		printf("\nTus disparos\n");
		imprimirTablero(disparoJ1,f,c);
		
		printf("\nSeleccione la casilla a la que quiere disparar (filas y columnas separadas por un intro)\n");
		
		int disparoF = -1;
		int disparoC = -1;
		
		while(disparoF<0 || disparoF>f){
			scanf("%d",&disparoF);
			disparoF--;
			if (disparoF<0 || disparoF>f){
				printf("\nIntroduce una posición válida\n");
			}
		}
		
		while(disparoC<0 || disparoC>c){
			scanf("%d",&disparoC);
			disparoC--;
			if (disparoC<0 || disparoC>c){
				printf("\nIntroduce una posición válida\n");
			}
		}		
		
		printf("\nDisparo a [%d,%d]: ",disparoF+1,disparoC+1);
		switch(compruebaDisparo(barcosBOT,f,c,disparoF,disparoC)){
			case 0:
				printf("Agua\n");
				*(disparoJ1+disparoF*c+disparoC) = 8;

				break;
			case 1:
				printf("Barco de 1 tocado y hundido\n");
				*(disparoJ1+disparoF*c+disparoC) = -1;
				break;				
			case 2:
				printf("Barco de 2 tocado\n");
				*(disparoJ1+disparoF*c+disparoC) = -2;
				break;
				
			case 3:
				printf("Barco de 3 tocado\n");
				*(disparoJ1+disparoF*c+disparoC) = -3;

				break;
				
			default:
				printf("El objetivo ya habia sido impactado antes\n");
				break;
			}	
		ganaJ1 = compruebaGanador(barcosBOT,f,c);

		int BOTdispF = rand()%f;
		int BOTdispC = rand()%c;
		printf("\nDisparo del BOT a [%d,%d]: ",BOTdispF+1,BOTdispC+1);
		switch(compruebaDisparo(barcosJ1,f,c,BOTdispF,BOTdispC)){
			case 0:
				printf("Agua\n");
				break;
			case 1:
				printf("Barco de 1 tocado y hundido\n");
				break;				
			case 2:
				printf("Barco de 2 tocado\n");
				break;
				
			case 3:
				printf("Barco de 3 tocado\n");
				break;
				
			default:
				printf("El objetivo ya habia sido impactado antes\n");
				break;
			}	
		
		ganaBOT = compruebaGanador(barcosJ1,f,c);
		}

	if (compruebaGanador(barcosBOT,f,c)==1){
		printf("\nGANA EL JUGADOR 1\n");
	}
		
	else{
		printf("\nGANA EL BOT\n");
	}

	free(barcosJ1);
	free(barcosBOT);
	free(disparoJ1);
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
	FILE *parchivo;
	parchivo=fopen("juego.txt","a");

	int *barcosJ1, *barcosJ2, *disparoJ1;
	barcosJ1 = (int *)malloc(f*c*sizeof(int));
	barcosJ2 = (int *)malloc(f*c*sizeof(int));

	inicializarTablero(barcosJ1,f,c);
	inicializarTablero(barcosJ2,f,c);

	colocarBarcosAutomaticamente(barcosJ1,f,c);
	colocarBarcosAutomaticamente(barcosJ2,f,c);
	fprintf(parchivo, "TABLERO DEL JUGADOR 1\n");
	imprimirTableroArchivo(barcosJ1,f,c,parchivo);
	fprintf(parchivo, "TABLERO DEL JUGADOR 2\n");
	imprimirTableroArchivo(barcosJ2,f,c,parchivo);
	
	int frand1,frand2, crand1, crand2, gana1=0, gana2=0;
	
	while(gana1==0 && gana2==0){
		frand1 = rand()%f;
		crand1 = rand()%c;
		fprintf(parchivo,"\nDisparo del Jugador 1 a [%d,%d]: ",frand1+1,crand1+1);
		switch(compruebaDisparo(barcosJ2,f,c,frand1,crand1)){
			case 0:
				fprintf(parchivo,"Agua\n");
				break;
			case 1:
				fprintf(parchivo,"Barco de 1 tocado y hundido\n");
				break;				
			case 2:
				fprintf(parchivo,"Barco de 2 tocado\n");
				break;
				
			case 3:
				fprintf(parchivo,"Barco de 3 tocado\n");
				break;
				
			default:
				fprintf(parchivo,"El objetivo ya habia sido impactado antes\n");
				break;
			}	
		
		gana1 = compruebaGanador(barcosJ2,f,c);
		if (gana1==1){
			fprintf(parchivo, "GANA EL JUGADOR 1\n");
			salir(); //<---- GRAN CHAPUZA
		}
		
		frand2 = rand()%f;
		crand2 = rand()%c;
		fprintf(parchivo,"\nDisparo del Jugador 2 a [%d,%d]: ",frand2+1,crand2+1);
		switch(compruebaDisparo(barcosJ1,f,c,frand2,crand2)){
			case 0:
				fprintf(parchivo,"Agua\n");
				break;
			case 1:
				fprintf(parchivo,"Barco de 1 tocado y hundido\n");
				break;				
			case 2:
				fprintf(parchivo,"Barco de 2 tocado\n");
				break;
				
			case 3:
				fprintf(parchivo,"Barco de 3 tocado\n");
				break;
				
			default:
				fprintf(parchivo,"el objetivo ya habia sido impactado antes\n");
				break;
			}	
		
		gana2 = compruebaGanador(barcosJ1,f,c);
		if (gana2){
			fprintf(parchivo, "GANA EL JUGADOR 2\n");
			salir(); //<---- GRAN CHAPUZA
		}
	}
	
	fclose(parchivo);
	free(barcosJ1);
	free(barcosJ2);

	/*
	if (compruebaGanador(barcosJ2,f,c)==1){
		fprintf(parchivo,"GANA EL JUGADOR 1\n");
		fprintf(parchivo,"\n");

	}
	else{
		fprintf(parchivo,"GANA EL JUGADOR 2\n");
		fprintf(parchivo,"\n");
	}
	*/
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

void imprimirTablero(int *t, int f, int c){
	printf("\n");
	for (int i = 0; i < f; i++){
		for (int j = 0; j < c; j++){
			printf("\t%d",*(t+i*c+j) );
		}
		printf("\n");
	}
	printf("\n");
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
	fprintf(pa,"\n");
	for (int i = 0; i < f; i++){
		for (int j = 0; j < c; j++){
			fprintf(pa,"\t%d",*(t+i*c+j) );
		}
		fprintf(pa,"\n");
	}
	fprintf(pa,"\n");
	
	return;
}

int compruebaGanador (int *t, int f, int c){
//Función compruebaGanador
//INPUTs:
//	- puntero a un tablero de barcos
//	- filas
//	- columnas
//OUTPUTS: nada
//Busca si quedan barcos por hundir. Si  quedan devuelve 0, si no 1. 
	int vacio = 0;
		for (int i = 0; i < f*c; i++){
			if (*(t+i)!=1 && *(t+i)!=2 && *(t+i)!=3 ){
				vacio++;
			}
	}
	
	if (vacio == f*c){
		return 1;
	}
	else{
		return 0;
	}
}

int compruebaDisparo(int *t, int f, int c, int posFila, int posCol){
//Función compruebaDisparo
//INPUTS:
//	- tablero de barcos
//	- filas
//	- columnas
//	- tiro (fila y columna)
//OUTPUTS: 0 si agua, 1 si hay un barco de 1, 2 si hay un barco de 2, 3 si hay un barco de 3
	switch(*(t+posFila*c+posCol)){
		case 0:
			return 0;

		case 1:
			*(t+posFila*c+posCol) = -1;
			return 1;
			break;
		
		case 2:
			*(t+posFila*c+posCol) = -2;
			return 2;
			break;
		
		case 3:
			*(t+posFila*c+posCol) = -3;
			return 3;
			break;
		
		default:
			return -1;
	}	
	
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
			if (*(t+iniFila*c+iniCol+i)==0 && (iniCol+i)<c){
				hueco++;
			}
		}
	}

	//VERTICAL
	else if (orientacion==1){
		for (i = 0; i < tamBarco; i++){
			if (*(t+(iniFila+i)*c+iniCol)==0 && (iniFila+i)<f){
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
	
	//Barcos de 3
	int fil, col, orientacion,colocados = 0;
	while(colocados<NUMBARCOS3){
		fil = rand()%f;
		col = rand()%c;
		orientacion = rand()%2;
		
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,3,orientacion)==1){
			colocados++;
			if (orientacion == 0){
				for (int j = 0; j < 3; j++){
					*(t+fil*c+(col+j)) = 3;
				}
			}
			else{
				for (int j = 0; j < 3; j++){
					*(t+(fil+j)*c+col) = 3;
				}
			}
		}
	}

	//Barcos de 2
	colocados = 0;
	while(colocados<NUMBARCOS2){
		fil = rand()%f;
		col = rand()%c;
		orientacion = rand()%2;
		
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,2,orientacion)==1){
			colocados++;
			if (orientacion == 0){
				for (int j = 0; j < 2; j++){
					*(t+fil*c+(col+j)) = 2;
				}
			}
			else{
				for (int j = 0; j < 2; j++){
					*(t+(fil+j)*c+col) = 2;
				}
			}
		}
	}
	//Barcos de 1
	colocados = 0;
	while (colocados<NUMBARCOS1){
		fil = rand()%f;
		col = rand()%c;
		orientacion = rand()%2;
		
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,1,orientacion)==1){
			colocados++;
			*(t+fil*c+col) = 1;
		}
	}
}


void colocarBarcosManualmente(int *t, int f, int c){
//Función colocarBarcosManualmente
//INPUTS:
//	- Tablero de barcos
//	- filas
//	- columnas	
//OUTPUTS: nada
//Coloca de forma manual 4 barcos de 1 posición, 2 de 2 posiciones y 1 de 3 posiciones en el tablero
	int fil, col, orientacion,colocados = 0;
	
	//Barcos de 3
	limpiarPantalla();
	while(colocados<NUMBARCOS3){
		printf("Quedan por colocar %d barco(s) de 3 casillas\n",NUMBARCOS3-colocados);
		printf("\nEste es tu tablero\n");
		imprimirTablero(t,f,c);
		printf("\nIntroduce la posicion en filas y columnas separadas con un intro\n");
		scanf("%d",&fil);
		fil--;
		scanf("%d",&col);
		col--;
		printf("\nIndique la orientacion (0)horizontal o (1)vertical\n"); 
		scanf("%d",&orientacion);
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,3,orientacion)==1){
			colocados++;
			if (orientacion == 0){
				for (int j = 0; j < 3; j++){
					*(t+fil*c+(col+j)) = 3;
				}
			}
			else{
				for (int j = 0; j < 3; j++){
					*(t+(fil+j)*c+col) = 3;
				}
			}
			limpiarPantalla();
			printf("\nColocado en [%d,%d]\n",fil, col );
		}
		else{
			limpiarPantalla();
			printf("\nNo es posible colocar el barco en la posicion dada\n");
		}
	}

	//Barcos de 2
	colocados = 0;
	limpiarPantalla();
	while(colocados<NUMBARCOS2){
		printf("Quedan por colocar %d barco(s) de 2 casillas\n",NUMBARCOS2-colocados);
		printf("\nEste es tu tablero\n");
		imprimirTablero(t,f,c);
		printf("Introduce la posicion en filas y columnas separadas con un intro\n");
		scanf("%d",&fil);
		fil--;
		scanf("%d",&col);
		col--;
		printf("\nIndique la orientacion (0)horizontal o (1)vertical\n"); 
		scanf("%d",&orientacion);
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,2,orientacion)==1){
			colocados++;
			if (orientacion == 0){
				for (int j = 0; j < 2; j++){
					*(t+fil*c+(col+j)) = 2;
				}
			}
			else{
				for (int j = 0; j < 2; j++){
					*(t+(fil+j)*c+col) = 2;
				}
			}
			limpiarPantalla();
			printf("\nColocado en [%d,%d]\n",fil, col );
		}
		else{
			limpiarPantalla();
			printf("\nNo es posible colocar el barco en la posicion dada\n");
		}
	}
	//Barcos de 1
	colocados = 0;
	limpiarPantalla();
	while(colocados<NUMBARCOS1){
		limpiarPantalla();
		printf("Quedan por colocar %d barco(s) de 1 casilla\n",NUMBARCOS1-colocados);
		printf("\nEste es tu tablero\n");
		imprimirTablero(t,f,c);
		printf("\nIntuduce la posicion en filas y columnas separadas con un intro\n");
		scanf("%d",&fil);
		fil--;
		scanf("%d",&col);
		col--;
		if (comprobacionEspacioParaBarco(t,f,c,fil,col,1,orientacion)==1){
			colocados++;
			*(t+fil*c+col) = 1;
			limpiarPantalla();
			printf("\nColocado en [%d,%d]\n",fil, col);
		}
		else{
			limpiarPantalla();
			printf("\nNo es posible colocar el barco en la posicion dada\n");
		}
	}
}

void salir(){
	return;
}
