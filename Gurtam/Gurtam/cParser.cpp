#include "pch.h"
#include "cParser.h"
#include <cstdlib>
mistakes cParser::line_processing(const char *const data)
{
	if (data == nullptr) { return ERROR_nullpntr; }

	// Все начинается с #
	if (*data != '#') {return WAIT;}
	// look for type
	// Предположим что максимальный размер типа равен 10
	char buffer[10]{0};
	// max array
	for (size_t i = 1; i < sizeof(buffer); i++)
	{
		// looking for a second pointer
		if (data[i] != '#') continue;
		
		if (!strncmp(data, "#SD#", i))	{ return this->parser_SD(&data[++i]);}
		if (!strncmp(data, "#M#", i))	{ return this->parser_M(&data[++i]); }
		return TYPE_ERROR;
	}
	return ERROR;
}

mistakes cParser::parser_SD(const char *const data)
{
	// можно попробовать запихивать это сразу в word 32 битный. 
	//SD.date.byte.day = part_parsser(data, 2);
	// it`s First iteration = 8 byte
	size_t count_byte = 0x00;
	size_t cntr_it	= 0x00;
	char _data[50]{0};

	for (size_t i = 0x00; i < 100; i++) // Чтобы не получился бесконечный цикл
	{
		if(data[cntr_it++] != ';') continue;
		// Потому что в пакете на 9 байте
		if (cntr_it != 9) { return BYTE_COUNT_ERROR; }

		this->SD.date.byte.day = char_to_int(&data[count_byte], 2);
		if (this->SD.date.byte.day > 31 || this->SD.date.byte.day < 0) { return ERROR; }

		SD.date.byte.month = char_to_int(&data[count_byte+2], 2);
		if (SD.date.byte.month > 12 || SD.date.byte.month < 0) { return ERROR; }

		SD.date.byte.year = char_to_int(&data[count_byte+4], 4);
		break;
	}
	// time
	count_byte = cntr_it;
	for (size_t i = 0x00; i < 100; i++) // Чтобы не получился бесконечный цикл
	{
		if (data[cntr_it++] != ';') continue;
		if (cntr_it != 16) { return BYTE_COUNT_ERROR; }


		this->SD.time.byte.hours = char_to_int(&data[count_byte], 2);
		if (this->SD.time.byte.hours > 24 || this->SD.time.byte.hours < 0) { return ERROR; }

		this->SD.time.byte.minutes = char_to_int(&data[count_byte + 2], 2);
		if (this->SD.time.byte.minutes > 60 || this->SD.time.byte.minutes < 0) { return ERROR; }

		this->SD.time.byte.seconds = char_to_int(&data[count_byte + 4], 2);
		if (this->SD.time.byte.seconds > 60 || this->SD.time.byte.seconds < 0) { return ERROR; }
		break;
	}
	// N
	count_byte = cntr_it;
	
	for (size_t i = 0; i < 100; i++)
	{
		_data[i] = data[i + count_byte];
		if (data[cntr_it++] != ';') {continue;}
		if (cntr_it != 16 + 10) { return BYTE_COUNT_ERROR; }
		this->SD.latitude.lat1 = char_to_float(_data, i);
		this->SD.latitude.lat2 = data[cntr_it++];
		break;
	}
	count_byte = ++cntr_it;
	memset(_data,0, sizeof(_data));

	for (size_t i = 0; i < 100; i++)
	{
		_data[i] = data[i + count_byte];
		if (data[cntr_it++] != ';') {continue;}
		if (cntr_it != 28 + 11) { return BYTE_COUNT_ERROR; }

		this->SD.longitude.lon1 = char_to_float(_data, i);
		this->SD.longitude.lon2 = data[cntr_it++];
		break;
	}
	count_byte = ++cntr_it;
	memset(_data, 0, sizeof(_data));
	for (size_t i = 0; i < 100; i++)
	{
		if (data[cntr_it++] != ';') { continue; }
		this->SD.other.speed = char_to_int(&data[count_byte], i);
		break;
	}
	count_byte = cntr_it;
	for (size_t i = 0; i < 100; i++)
	{
		if (data[cntr_it++] != ';') { continue; }
		this->SD.other.course = char_to_int(&data[count_byte], i);
		break;
	}
	count_byte = cntr_it;
	for (size_t i = 0; i < 100; i++)
	{
		if (data[cntr_it++] != ';') { continue; }
		this->SD.other.height = char_to_int(&data[count_byte], i);
		break;
	}
	count_byte = cntr_it;
	for (size_t i = 0; i < 100; i++)
	{
		if (data[cntr_it++] != '\r') { continue; }
		this->SD.other.sats = char_to_int(&data[count_byte], i);
		break;
	}

	return SD_PACK_ACCEPTERD;
}



mistakes cParser::parser_M(const char *const data)
{
	// we assume that more than 100 lines can`t be
	for (size_t i = 0; i < 100; i++){
		// Если дошли до конца строки, то проверям еще на \n и выходим написав что все принятно
		if (data[i] == '\r' && 	data[i + 1] == '\n'){
				check_sum();	// условная функция проверки контольной суммы или что-то типо того
				this->M.array[i]	 = '\r'; 
				this->M.array[i + 1] = '\n'; 
				return M_PACK_ACCEPTED;
		}
		this->M.array[i] = data[i];
	}
	memset(&M, 0, sizeof(M));
	return ERROR;
}

int cParser::char_to_int(const char * const chr, char count)
{
	int k = pow(10, count - 1);
	int result = 0x00;
	for (size_t i = 0; i < count; i++)
	{
		result += k * (chr[i] - '0');
		k /= 10;
	}
	return result;
}

float cParser::char_to_float(const char * const chr, char count)
{
	float result = 0x00;
	double k = 0x00;
	for (size_t i = 0; i < count; i++)
	{
		if (chr[i] != '.') continue;
		k = pow(10, i - 1);
		break;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (chr[i] == '.') continue;
		if (chr[i] == ';') break;
		result += k * (chr[i] - '0');
		k /= 10;
	}
	
	return result;
}
