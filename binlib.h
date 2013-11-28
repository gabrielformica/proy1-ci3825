/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler 10-10272
 * En esta libreria se proveen funciones para lectura y escritura 
 * de archivos
 */

#ifndef BINLIB_H 
#define BINLIB_H 

/*
 * Escribe un archivo de texto plano
 * Parametros: 
 *	name: Nombre del archivo de salida
 *	x: Arreglo a imprimir (es el arreglo ordenado)
 *	length: Largo del arreglo
 *
 */

extern void writefile(char *name, int *x, int length);
/*
 * Escribe un arreglo en un archivo binario
 * Parametros:
 * 	name: Es el nombre del archivo de salida
 *	x: Es el arreglo de enteros a imprimir
 *	left: Es el indice del arreglo por el cual se comenzara a imprimir
 *	length: Es el largo del arreglo
 * 
 */


extern void writebin(char *name, int *x, int left,int length);
/*
 * Lee una archivo binario
 * Parametros:
 *	name: Es el nombre del archivo a leer
 *	x: Es el arreglo donde se almacenaran los datos
 *	length: Es el largo del arreglo
 *
 */

extern void readbin(char *name, int *x, int length);
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
extern int *readchild(pid_t childpid, int numbers);
#endif
