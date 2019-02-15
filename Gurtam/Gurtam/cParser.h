#pragma once
#include <iostream>


uint32_t test;
typedef struct {
	std::string type = "SD";
	//#Data DD-MM-YYYY
	union {
		uint_least64_t word;
		struct byte {
			uint_least64_t	day		: 6;
			uint_least64_t	month	: 4;
			uint_least64_t	year	: 54;
		}byte;
	}date;
	//# time HH-MM-SS
	union {
		uint32_t word;
		struct byte {
			uint32_t			:15;
			uint32_t	hours	: 5;
			uint32_t	minutes : 6;
			uint32_t	seconds : 6;
		}byte;
	}time;
	//# latitude/logitude
	/*maybe need alignment*/
	struct latitude
	{
		float	lat1;
		char	lat2;
	}latitude;
	struct longitude
	{
		float	lon1;
		char	lon2;
	}longitude;

	struct other {
		uint16_t speed;
		uint16_t course;
		uint32_t height;
		uint32_t sats;
	}other;
}str_SD;

class cParser
{
public:
	cParser();
	~cParser();
	str_SD SD;
};

