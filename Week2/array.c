#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
	int a[100];
	int* b = malloc(100 * sizeof(int));
	
	
	b[50] = 42;
	
	int x = 42;
	int* y = &x;

	y[50] = 42;
	int** z = &y; //pointer to an int




	free(b);

}
