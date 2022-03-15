#include <stdio.h>
#include <stdlib.h>


typedef struct student_t {
	int g;
	char* name;
	float gpa;
} student;

void printStud(student tmp) {
	tmp.g = 3.987;
	printf("%d\t%s\t%f\n", tmp.g, tmp.name, tmp.gpa);
}

void printStud2(student* tmp) {
	printf("%d\t%s\t%f\n", tmp -> g, tmp -> name, tmp -> gpa);
}

int main (int argc, char** argv) {

	student joe;
	joe.g = 3339;
	joe.name = "Josephine";
	joe.gpa = 3.39;
/*
	printStud(joe);
	printStud2(&joe);
*/

	for (int i = 0; i < 1000000; ++i) {
		printStud2(&joe);
	}
}
