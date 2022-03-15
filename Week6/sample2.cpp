#include <iostream>


void changeMe(int x) {
	x = x* x;
}

void changeMe2(int* x) {
	*x = *x * *x;
}

void changeMe3(int& x) {
	x = x * x;
}


int main(int argc, char** argv) {
	int x= 42;
	changeMe(x);
	std::cout << x << std::endl;
		changeMe3(x);
	std::cout<< x << std::endl;

	int& frank = x;
	changeMe3(frank);
	std::cout<< x << std::endl;
}
