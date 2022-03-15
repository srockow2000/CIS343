#include <stdio.h>

void square(int* x) {
	printf("Square.x's value is %d\n", x);
	printf("Square.x's address is %p.\n", &x);
	
	*x = *x * *x;
	printf("Squares.x's value is now %p.\n", x);
}


int main (int argc, char** argv) {

	int x = 42;
	square(&x);
	
	printf("x's value is %d\n", x);
	printf("x's address is %p\n", &x);

	/*printf("%d\n", x);
	printf("%p\n", &x);
	printf("%p\n", &square);
	printf("%p\n", &main);

	*/
}
