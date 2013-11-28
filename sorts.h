/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler 10-10272
 * En esta libreria se proveen funciones de ordenamientos
 */

#ifndef SORTS_H 
#define SORTS_H 

/*
 * Mezcla ordenadamente dos arreglos ordenados (se usa para hilos) 
 *
 * Parametros:
 *	data: Arreglo global que usan los hilos 
 *	left1: indice donde comienza el primer arreglo	
 *	right1: indice donde termina exactamente el primer arreglo
 *	right2: indice donde termine el segundo arreglo
 *
 */

extern void merge_t(int *data, int left1, int right1, int right2);

/*
 * Hace el swap de los elementos de un arreglo
 * Parametros:
 * 	v: El arreglo en cuestion
 *	i,j: Son los indices del arreglo sobre los que se hara swaping	
 *
 */

extern void swap(int *v, int i, int j);

/*
 * Ordena las secciones de un arreglo
 * Parametros:
 * 	v: Arreglo en cuestion
 *	left,right: Es el rango al cual se le hara el quicksort a v
 *
 */

extern void quicksort(int *v, int left, int right);

/*
 * Mezcla ordenadamente dos arreglos ordenados  
 * Parametros:
 *	a,b: Son los arreglos en cuestion
 *	sizea: Tamanio de a
 *	sizeb: Tamanio de b
 * Return: El arreglo ordenado
 *
 */

extern int *merge(int *a, int *b, int sizea, int sizeb);
#endif
