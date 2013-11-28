/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler 10-10272
 * En esta libreria se proveen funciones para lectura y escritura 
 * de archivos
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "binlib.h"

/*
 * Escribe un archivo de texto plano
 * Parametros: 
 *	name: Nombre del archivo de salida
 *	x: Arreglo a imprimir (es el arreglo ordenado)
 *	length: Largo del arreglo
 *
 */
void writefile(char *name, int *x, int length) {
	FILE *fp;
	if ((fp = fopen(name,"w")) == NULL) {
		perror("fopen");
		exit(1);
	}
	int i = 0;
	for(; i < length; i++)
		fprintf(fp,"%d\n",x[i]);
	fclose(fp);
}
/*
 * Escribe un arreglo en un archivo binario
 * Parametros:
 * 	name: Es el nombre del archivo de salida
 *	x: Es el arreglo de enteros a imprimir
 *	left: Es el indice del arreglo por el cual se comenzara a imprimir
 *	length: Es el largo del arreglo
 * 
 */
void writebin(char *name,int *x, int left, int length) {
	FILE *fp;
	if ((fp = fopen(name,"w")) == NULL) {
		perror("fopen");
		exit(1);
	}
	
	if (fwrite(&x[left], sizeof(int), length, fp) == 0) {
		perror("fwrite:");
		exit(1);
	}
	fclose(fp);
}

/*
 * Lee una archivo binario
 * Parametros:
 *	name: Es el nombre del archivo a leer
 *	x: Es el arreglo donde se almacenaran los datos
 *	length: Es el largo del arreglo
 *
 */

void readbin(char *name, int *x, int length) {
	FILE *fp;

	//Se abre y se lee el archivo	
	if ((fp = fopen(name,"r")) == NULL) {
		perror("fopen");
		exit(1);
	}

	if (fread(&x[0], sizeof(int), length, fp) == 0) {
		perror("fread:");
		exit(1);
	}
	fclose(fp);
} 

/*
 * Prepara a un proceso para comenzar la lectura del archivo binario
 * Parametros:
 *	childpid: PID del proceso
 *	numbers: El tamano del arreglo en donde se almacenara la informacion
 *
 * Return:
 *	El arreglo en cuestion, con los datos leidos
 *
 */
int *readchild(pid_t childpid, int numbers) {
	char name[6];
	sprintf(name,"%d",childpid);
	int *x = malloc((numbers)*sizeof(int));
	readbin(name,x,numbers);	
	return x;
}
