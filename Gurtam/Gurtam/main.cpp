// Gurtam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

char SD[] = "#SD#04012011;135515;5544.6025;N;03739.6834;E;35;215;110;7\r\n";
char M[] = "#M#Груз доставлен\r\n";
char something[] = "04012011; 135515; 5544.6025; N; 03739.6834; E; 35; 215; 110; 7\r\n";
const int task2 = 0x5FABFF01;
int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Задача 1" << std::endl;
	cParser *parser = new cParser;
	auto answer = parser->line_processing(SD);
	switch (answer)
	{
	case WAIT :
		std::cout << "# not found" << std::endl;
		break;
	case ERROR_nullpntr:
		std::cout << "ERROR_nullpntr" << std::endl;
		break;
	case BYTE_COUNT_ERROR:
		std::cout << "BYTE_COUNT_ERROR" << std::endl;
		break;
	case M_PACK_ACCEPTED: {
		std::cout << "M_PACK_ACCEPTED: ";
		std::cout << parser->getM() << std::endl;
		break;
	}
	case SD_PACK_ACCEPTERD:
		std::cout << "SD_PACK_ACCEPTERD: " << std::endl;
		std::cout << "day: "<< parser->SD.date.byte.day << std::endl;
		std::cout << "month: " << parser->SD.date.byte.month << std::endl;
		std::cout << "year: " << parser->SD.date.byte.year << std::endl;

		std::cout << "hours: " << parser->SD.time.byte.hours << std::endl;
		std::cout << "minutes: " << parser->SD.time.byte.minutes << std::endl;
		std::cout << "seconds: " << parser->SD.time.byte.seconds << std::endl;

		std::cout << "latitude: " << parser->SD.latitude.lat1 << parser->SD.latitude.lat2 << std::endl;
		std::cout << "longitude: " << parser->SD.longitude.lon1 << parser->SD.longitude.lon2 << std::endl;

		std::cout << "course: " << parser->SD.other.course	<< std::endl;
		std::cout << "height: " << parser->SD.other.height	<< std::endl;
		std::cout << "sats: " << parser->SD.other.sats		<< std::endl;
		std::cout << "speed: " << parser->SD.other.speed	<< std::endl;

		break;
	default:
		break;
	}


	std::cout << "\\\\\\\\\\\\\\////////////////" << std::endl;
	std::cout << "Задача 2" << std::endl;
	int first  = (task2 & 0x0000FF00) >> 8;
	std::cout << "Первый параметр: " << first << std::endl;
	int second = ((task2 ^ 128) & 128) >> 7;
	std::cout << "Второй параметр: " << second << std::endl;

	int third  = (task2 &  0x1E0000) >> 17;
	int bite, invertByte = 0;
	std::cout << "Третий параметр: ";
	for (size_t i = 0; i < 3; i++)
	{
		bite = (third >> i) & 1;
		std::cout << bite;
		invertByte = (invertByte << 1) | bite;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}

