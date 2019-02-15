// Gurtam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

char SD[] = "#SD#04012011; 135515; 5544.6025; N; 03739.6834; E; 35; 215; 110; 7\r\n";
char M[] = "#M#Груз доставлен\r\n";
char something[] = "04012011; 135515; 5544.6025; N; 03739.6834; E; 35; 215; 110; 7\r\n";

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Задача 1" << std::endl;
	cParser *parser = new cParser;
	auto answer = parser->line_processing(M);
	switch (answer)
	{
	case WAIT :
		std::cout << "# not found" << std::endl;
		break;
	case M_PACK_ACCEPTED: {
		std::cout << "M_PACK_ACCEPTED: ";
		std::cout << parser->getM() << std::endl;
		break;
	}
		
	default:
		break;
	}

	system("pause");
	return 0;
}

