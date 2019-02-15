#pragma once
#include <iostream>

typedef struct {
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

typedef struct {
	char array[100];
}str_M;

typedef enum {
	ERROR,
	TYPE_ERROR,
	WAIT,
	M_PACK_ACCEPTED,
	SUCCESS
}mistakes;

class cParser
{
public:
	cParser() { 
		memset(&SD,0,sizeof(SD));
		memset(&M, 0, sizeof(M));
	};
	~cParser();
	mistakes line_processing(const char * const data);



	char *getM() const { return (char*)M.array; }
private:
	str_SD SD;
	str_M	M;
	mistakes check_sum() { return SUCCESS; };
	mistakes parser_SD(const char *const data);
	mistakes parser_M(const char *const data);
};

