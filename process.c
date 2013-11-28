/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler  10-10272
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "binlib.h"
#include "timelib.h"
#include "sorts.h"

/*
 * Procedimiento que se ejecuta si el nodo raiz es una hoja. Llama a la libreria
 * leaf.c, donde realiza quicksort.
 *
 * Parametros:
 * 	input: archivo de donde se leeran los datos
 * 	output: archivo donde se escribiran los datos
 * 	x: numero total de elementos
 * 	a: borde izquierdo, desde donde se comenzara a ordenar
 * 	b: borde derecho, hasta donde ordenara
 *	time: variable que toma el tiempo que tarda en ejecutarse.
 *
 * Retorna: Void.
 */

void rootisleaf(char *input, char *output, int x, int a, int b, int time) {
	char globalnumbers[6];
	char left[6];
	char right[6];
	char time1[20];
	sprintf(globalnumbers, "%d",x); 
	sprintf(left,"%d",a);
	sprintf(right,"%d",b);
	sprintf(time1,"%d",time);
	execl("./leaf","./leaf",input,globalnumbers,
	      left,right,time1,output,NULL);
}

/*
 *  Crea un proceso hijo mediante fork
 *
 * Parametros : Ninguno.
 *
 * Retorna: El id del proceso hijo
 */

pid_t createchild() {
	pid_t pid;
	if ((pid = fork()) == -1) {
		perror("fork");
		exit(1);	
	}
	return pid;
}

/*
 * Codigo que ejecutan todos los hijos que son hoja. LLama a
 * leaf.c para realizar los procedimientos de quicksort.
 *
 * Parametros:
 *	input: archivo de donde se leera la informacion
 *	x: numero total de elementos
 *	a: borde izquierdo del arreglo a modificar
 *	b: borde derecho del arreglo a modificar
 *	time: tiempo que tarda en realizarse el procedimiento
 *
 * Retorna: Void.
 */

void leafcode(char *input, int x, int a, int b, int time) {
	char globalnumbers[6];
	char left[6];
	char right[6];
	char time1[20];
	sprintf(globalnumbers, "%d",x); 
	sprintf(left,"%d",a);
	sprintf(right,"%d",b);
	sprintf(time1,"%d",time);
	execl("./leaf","./leaf",input,globalnumbers,
	      left,right,time1,NULL);
}

/*
 * Borra los archivos que son creados por los procesos a medida
 * que son utilizados por sus padres
 *
 * Parametros:
 *	c1,c2: Id de cada uno de los procesos hijos
 *
 * Retorna: Void.
 */

void deletechildfiles(pid_t c1, pid_t c2) {
	char child1[6];
	char child2[6];
	sprintf(child1,"%d",c1);
	sprintf(child2,"%d",c2);

	execl("/bin/rm","rm",child1,child2,NULL);
}

/*
 * Checkea que el numero de elementos en el arreglo sea mayor o igual que el numero hojas
 * Parametros
 * 	n: numero de elementos del arreglo
 * 	l: numero de niveles
 *
 * Retorna: Void.
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

int main(int argc, char *argv[]) {
		
	int numbers = atoi(argv[1]);
	int levels = atoi(argv[2]);
	check(numbers,levels);  //Verifica la entrada de linea de comando 

	pid_t root = getpid();
	pid_t childpid2 = 0;
	pid_t childpid = 0;
	char str[10];
	char *input = argv[3];
	char *output = argv[4];
	int time1; //Tiempo de inicio
	int globalnumbers = numbers;
	int left = 0;
	int right = numbers - 1;
	int i,status;
	
	time1 = timing();


	if (levels == 1) { //se verifica que la unica hoja no sea la raiz
		rootisleaf(input,output,globalnumbers,left,right,time1);
	}

	for (i = 1; i < levels; i++) {	
		childpid = createchild();
		if (childpid == 0)  {
			time1 = timing();
			numbers = numbers/2;
			right = left + numbers - 1;	
			continue;
		}
		childpid2 = createchild(); 
		if (childpid2 == 0) {
			time1 = timing();
			numbers = numbers - (numbers/2);
			left = right - numbers + 1;
			continue;
		} 
		break;
	}
 	if (wait(&status) == -1 ) {    //Todas las hojas caen en esta condicion
		leafcode(input,globalnumbers,left,right,time1);
	}
	wait(&status);	//Todo padre espera por su segundo hijo

	int *a = readchild(childpid,numbers/2); 
	int *b = readchild(childpid2,numbers - (numbers/2)); 
	int *c = merge(a,b,numbers/2,numbers - (numbers/2)); //mezcla los arreglos
	int time2;	
		
	if (getpid() == root) {
		writefile(output,c,numbers);
		time2 = timing();
		printf("El proceso %d tarda: %d\n",root,time2 - time1);
		deletechildfiles(childpid,childpid2);
	}

	//procesos intermedios
	sprintf(str,"%d",getpid());
	writebin(str,c,0,numbers); //Escribe el archivo su pid de nombre 
	time2 = timing(); 
	printf("El proceso %d tarda: %d\n",getpid(),time2 - time1);
	deletechildfiles(childpid,childpid2);
	exit(0); //Este exit(0) nunca deberia ejecutarse
}
