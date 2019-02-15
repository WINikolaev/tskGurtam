// Gurtam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>

int main()
{
	cParser *parser = new cParser;

	std::cout << sizeof(parser->SD.other) << std::endl;
	system("pause");
	return 0;
}

