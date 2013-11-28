/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler  10-10272
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "timelib.h"
#include "sorts.h"
#include "binlib.h"


typedef struct quicksort_data quicksort_data;
typedef struct merge_data merge_data;

struct quicksort_data {		//usado para pasar como attr del hilo
	int *v;			//Arreglo a modificar
	int left;		//Borde izquierdo
	int right;		//Borde derecho
};

struct merge_data {		//usado para pasar como attr del hilo
	int right2;
	int right1;
	int left1;
};

void check();
void *thread_merge();
void *thread_quicksort();
void changinglevel();

int *data; //Arreglo global que compartiran los hilos

int main(int argc, char *argv[]) {
	int time1 = timing();
	int numbers = atoi(argv[1]);
	int levels = atoi(argv[2]);
	check(numbers,levels);
	if ((data = malloc(numbers*sizeof(int))) == NULL) {
		perror("malloc");
		exit(1);
	}
	readbin(argv[3],data,numbers);

	int x = 1;   //Numeros de nodos que tiene cierto nivel
	int i = 1;
	for (; i < levels; i++) //numero de nodos del ultimo nivel
		x = x*2;

	/*Creacion de las hojas y quicksort */

	int range = numbers/x;  //rango de elementos que cada hoja en el arreglo va a modificar

	pthread_t *threads;			//Donde se guarda el id de cada hilo hoja
	if ((threads = malloc(x*sizeof(pthread_t))) == NULL) {
		perror("malloc");
		exit(1);
	}
	quicksort_data quicksort_array[x];	//Arreglo de info para pasar los argumentos del quicksort

	for (i = 0; i < x; i++) { //se crean todas las hojas
		quicksort_array[i].left = i*range;
		quicksort_array[i].right = ((i+1)*range)-1;
		if (i == x - 1) {
			quicksort_array[i].right = numbers-1;
		}
		pthread_create(&threads[i],NULL,thread_quicksort,(void *)&quicksort_array[i]);
	}
	for (i = 0; i < x; i++) {
		pthread_join(threads[i],NULL); //Espera a que todas las hojas se completen
	}

	free(threads);
	/*Fin de la creacion de las hojas y quicksort*/
	/*Creacion de los padres y merge */
        merge_data *merge_array;                //Arreglo para pasar los argumentos del merge
	int range2;
        if ((merge_array = malloc(x*sizeof(merge_data))) == NULL) {
		perror("malloc");
		exit(1);
	}

        while (x > 2) {                        //Cuando x es uno, significa que llegue al nodo raiz
		changinglevel(&x,&range,&range2);
		if ((threads = malloc(x*sizeof(pthread_t))) == NULL) {
			perror("malloc");
			exit(1);
		}
		int sizea = range2;
		int sizeb = range2;
		for (i = 0; i < x; i++) {
			if (i == x - 1) {
				sizeb = numbers - (i*range) - sizea;
			}
			merge_array[i].left1 = i*range;
			merge_array[i].right1 = i*range + sizea -1;
			merge_array[i].right2 = merge_array[i].right1 + sizeb;
			pthread_create(&threads[i],NULL,thread_merge,(void *)&merge_array[i]);

            	}

                for (i = 0; i < x; i++) { //Se hacen los join
                        pthread_join(threads[i], NULL);
                }
		free(threads);


	}
	if (levels > 1) {
		free(merge_array);
		merge_data merge_aux;
		merge_aux.left1 = 0;
		merge_aux.right1 = (range2*2) -1;
		merge_aux.right2 = numbers - 1;
		if (levels == 2) 
			merge_aux.right1 = numbers/2 -1;
		merge_t(data,merge_aux.left1,merge_aux.right1,merge_aux.right2);
	}
	writefile(argv[4],data,numbers);
	int time2 = timing();
	printf("Tiempo de ejecucion: %d ms \n",time2-time1);
}

/*
 * Proceso intermedio para llamar a la firma de pthread_create(caso merge), y realizar tanto merge como update
 *
 * Parametros:
 * 	merge_info: structure con la informacion necesaria para correr merge y update
 *
 * Retorna: Void.
 */

void *thread_merge(merge_data *merge_info) {
	merge_data temp;
	temp.right1 = merge_info->right1;
	temp.left1 = merge_info->left1;
	temp.right2 = merge_info->right2;
	merge_t(data,temp.left1,temp.right1,temp.right2);
	pthread_exit(NULL);
}

/*
 * Proceso intermedio para llamar a la firma de pthread_create (caso quicksort), y realizar quicksort
 *
 * Parametros:
 *	quicksort_info: structure con la informacion necesaria para realizar quicksort
 *
 * Retorna: Void.
 */

void *thread_quicksort(quicksort_data *quicksort_info){
	quicksort(data,quicksort_info->left,quicksort_info->right);
	pthread_exit(NULL);
}

/*
 * Reestructura el nivel del arbol en el que se esta trabajando
 *
 * Parametros:
 * 	nodes: numero de nodos del nivel
 *	l: nivel actual del arbol
 * 	newrange: rango de elementos que debe actualizar cada nodo
 * 	oldrange: rango de elementos que actualizo cada nodo del nivel inferior
 *
 * Retorna: Void.
 */

void changinglevel(int *nodes, int *newrange, int *oldrange) {
	*nodes = (*nodes)/2;
	*oldrange = *newrange;
	*newrange = 2*(*newrange);
}

/*
 * Funcion que verifica condiciones de entrada
 * Parametros:
 * 	n: Es el numero de elementos que se quieren ordenar
 *	l: Son los niveles que se quieren crear
 */

void check(int n, int l) {
	if (l == 0) {
		perror("El arbol no puede tener 0 niveles");
		exit(1);
	}
	int i = 1; //cuenta el nivel maximo
	int x = 1; //auxiliar
	for(; 1 ; i++) {
		if (x > n)
			break;
		x = x*2;
	}
	if (x > n) 
		i--;
	if (i < l) {
		perror("El arbol no puede tener tantos niveles");
		exit(1);
	}
}

