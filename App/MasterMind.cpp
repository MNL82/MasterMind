#include "MasterMind.h"

#include <iostream>

using namespace MM;

int main()
{
    std::cout << "Hello World!\n"; 

	auto MM = new MasterMind();

	char test[20];
	std::cin >> test;

	std::cout << "Imput: ";
	std::cout << test;
	std::cout << "\n";
	delete MM;
}

