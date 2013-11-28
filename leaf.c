#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timelib.h"
#include "sorts.h"


int main(int arg, char *argv[]) {

		int numbers,left,right,time1;
		numbers = atoi(argv[2]);
		left = atoi(argv[3]);
		right = atoi(argv[4]);
		time1 = atoi(argv[5]); //tiempo inicial	
	
		int *data; 
		if ((data =  malloc(numbers*sizeof(int))) == NULL) {
			perror("malloc");
			exit(1);
		}
		readbin(argv[1],data,numbers); //se lee el archivo binario
		quicksort(data,left,right);

		/*
		El septimo argumento es el output, se pasa unicamente
		cuando hay un solo nivel en el arbol
		*/
		if (arg == 7) {   
			writefile(argv[6],data,numbers);	
			
		}
		else { 
			char f1[6]; //String de pid
			sprintf(f1,"%d",getpid());
			writebin(f1,data,left,numbers); //crea el archivo
		}	
		int time2 = timing(); //tiempo final
		printf("El proceso %d tarda: %d\n",getpid(),time2 -time1);
		exit(0);
}
