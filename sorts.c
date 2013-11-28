/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler 10-10272
 * En esta libreria se proveen funciones de ordenamientos
 */

#include <stdlib.h>
#include <stdio.h>
#include "sorts.h"

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

void merge_t(int *data, int left1, int right1, int right2) {
	int size = right2 - left1 + 1;
	int *temp = malloc(size*sizeof(int));

	int i = left1; //inicio 1
	int left2 = right1 + 1; //inicio 2
	int j = 0; //inicio de temp
	while ((i <= right1) && (left2 <= right2)) {
		if (data[i] <= data[left2]) {
			temp[j] = data[i];
			i++;
		}
		else {
			temp[j] = data[left2];
			left2++;
		}
		j++;
	}
	while (i <= right1) {
		temp[j] = data[i];
		j++;
		i++;
	}
	while (left2 <= right2) {
		temp[j] = data[left2];
		j++;
		left2++;
	}
	for (j = 0; j < size; j++) {
		data[j + left1] = temp[j];	
	}
	free(temp);
}

/*
 * Mezcla ordenadamente dos arreglos ordenados  
 * Parametros:
 *	a,b: Son los arreglos en cuestion
 *	sizea: Tamanio de a
 *	sizeb: Tamanio de b
 * Return: El arreglo ordenado
 *
 */

int *merge(int *a, int *b, int sizea, int sizeb) {
	int sizec = sizea + sizeb;	
	int *c;  
	if ((c = malloc((sizec)*sizeof(int))) == NULL) {
		perror("malloc");
		exit(1);
	}

	int i = 0; //contador de a
	int j = 0; //contador de b
	int g = 0; //contador de c
	while ((i < sizea) && (j < sizeb)) {
		if (a[i] <= b[j]) {
			c[g] = a[i];
			i++;
		}
		else {
			c[g] = b[j];
			j++;
		}
			g++;
	}
	while (i < sizea) {
		c[g] = a[i];
		g++;
		i++;
	}
	while (j < sizeb) {
		c[g] = b[j];
		g++;
		j++;
	}
	return c;
}

/*
 * Hace el swap de los elementos de un arreglo
 * Parametros:
 * 	v: El arreglo en cuestion
 *	i,j: Son los indices del arreglo sobre los que se hara swaping	
 *
 */
void swap(int *v, int i, int j) {
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*
 * Ordena las secciones de un arreglo
 * Parametros:
 * 	v: Arreglo en cuestion
 *	left,right: Es el rango al cual se le hara el quicksort a v
 *
 */
void quicksort(int *v, int left, int right) {
	if (left >= right)
		return;
	swap(v,left,(left+right)/2);
	
	int pivotdest,i; /*Posicion final donde quedara el pivote*/	
	pivotdest = left;
	for (i = left + 1; i <= right; i++) {
		if (v[i] < v[left]) {
			pivotdest++;
			swap(v,pivotdest,i); 
		}
	}
	swap(v,left,pivotdest);
	quicksort(v,left,pivotdest-1);
	quicksort(v,pivotdest+1,right);
}
