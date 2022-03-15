#include <stdio.h>
#include <stdlib.h>

void printer(int** mult, int w, int l) {
	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < l; ++j) {
			printf("%d\t", mult[i][j]);
		}
	printf("\n");
	}
}

int main(int argc, char** argv) {

	int size = atoi(argv[1]);
	int** mult = malloc(size  * sizeof(int*));

	for (int i = 0; i < size; i++) {
		mult[i] = malloc(size*sizeof(int));
	}


	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			mult[i][j] = (i+1) * (j+1);
		}
	}

	//mult[i] holds the address of the rows
	//the rows hold the address of the data
		
	printer(mult, size, size);

	free(mult);
}
