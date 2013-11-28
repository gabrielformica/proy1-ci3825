/*
 * Gabriel Formica 10-11036
 * Gabriel Gedler 10-10272
 * En esta libreria solo se provee una funcion para el calculo del tiempo
 */

#include <sys/time.h>

/*
 * Toma la hora cuando se ejecuta 
 * return: La hora
 */

int timing() {
	struct timeval t;
	
	gettimeofday ( &t, (struct timezone*)0 );
	int dt = (t.tv_sec)*1000000 + t.tv_usec;
	return dt;
}

