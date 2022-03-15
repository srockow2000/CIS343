#include <stdio.h>


void print(int *mult, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printf("%d\t", *(mult + size * i + j));
		}
		printf("\n");
	}
}
	
int main(int argc, char** argv) {

	int size = 12;
	int mult[size][size];

	printf("The size of mult is %lu\n", sizeof(mult));

	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			mult[i][j] = (i+1) *(j + 1);
		}
	}
print(mult, size);


}
