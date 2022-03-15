#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int * a = malloc(10 * sizeof(int));
	*(a+0) = 42;
	*(a+1) = *a + *a;
	int b = *a + 1;
	printf("%i\n\n", b);
}
