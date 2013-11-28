#include <stdio.h>
#include <stdlib.h>

int main(int arg, char *argv[]) {
	FILE *fp;
	int *x, numeros, max, i;
	numeros = atoi(argv[1]);
	max = atoi(argv[2]);
			
	i = 0;
	x = malloc(numeros*sizeof(int));
	srand(getpid());
	for (; i < numeros; i++) {
		int y = rand() % max;	
		if ((y % 100) > 40) {
			x[i] = y; 
		}
		else 
			x[i] = -1*y;
		printf("%d\n",x[i]);	
	}

	fp = fopen("tempbin","w");
	fwrite(&x[0],sizeof(int),numeros,fp);
	fclose(fp);
}
