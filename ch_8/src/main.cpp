#include <iostream>
#include "fun.h"

int main(int argc, char *argv[]) 
{
	// a test program
	int a = 27;
	print_input(a);
	print_input(a+1);
	print_input(3);

	const int b = 15;
	print_input(b);
	print_input(b+1);

	return 0;
}