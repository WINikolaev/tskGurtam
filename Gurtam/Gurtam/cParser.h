#pragma once
#include <iostream>

#define cntr_date 8
#define cntr_time 6

typedef struct {
	//#Data DD-MM-YYYY
	union {
		uint32_t word;
		struct byte {
			uint32_t	day		: 6;
			uint32_t	month	: 5;
			uint32_t	year	: 21;
		}byte;
	}date;
	//# time HH-MM-SS
	union {
		uint32_t word;
		struct byte {
			uint32_t			: 7;
			uint32_t	hours	: 5;
			uint32_t	minutes : 10;
			uint32_t	seconds : 10;
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
	ERROR_nullpntr,
	BYTE_COUNT_ERROR,
	SUCCESS
}mistakes;


class cParser
{
public:
	cParser() { 
		memset(&SD,0,sizeof(SD));
		memset(&M, 0, sizeof(M));
		//ptr_for_part_SD = &this->SD.date.word;
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

	int   char_to_int(const char *const chr, char count);
	float char_to_float(const char * const chr, char count);
	const void *ptr_for_part_SD[10] = {
				&this->SD.date.word,
				&this->SD.time.word,
				&this->SD.latitude.lat1,
				&this->SD.latitude.lat2,
				&this->SD.longitude.lon1,
				&this->SD.longitude.lon2,
				&this->SD.other.speed,
				&this->SD.other.course,
				&this->SD.other.height,
				&this->SD.other.sats
	};

};

