#include "pch.h"
#include "cParser.h"

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
	size_t state = 0x00;
	uint_least64_t value = 0x00;
	for (size_t i = 0; i < 100; i++)
	{
		value |= (uint_least64_t)(data[i] - 0x30) << 8;
		if (data[i] != ';') continue;
		size_t ptr_i = 0x00;
		// Думал это все забабахать через массив указатель на void но не вышло. 
		switch (state)
		{
		case 0:
			SD.date.word = value;
			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		default:
			break;
		}
	}
	return ERROR;
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