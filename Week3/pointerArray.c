#include <stdio.h>
#include <stdlib.h>

void printMe(int* mult, size) {

	for (int i = 0; i < size; ++i) {
	       for (int j = 0; j < size; ++j) {
	       		printf("%lu\t", mult[i * size + j]);
	       }
	printf("\n");
	}
}	
	


int main(int argc, char** argv) {

	int size = atoi(argv[1]);
	int* mult = malloc(size * size * sizeof(*mult));

	//don't cast malloc -> malloc returns void star
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			mult[i * size + j] = (i+1) * (j+1);
		}
	}

	printMe(mult, size);

	free(mult);
}
