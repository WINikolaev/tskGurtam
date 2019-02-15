#include "pch.h"
#include "cParser.h"

mistakes cParser::line_processing(const char *const data)
{
	// ��� ���������� � #
	if (*data != '#') {return WAIT;}
	// look for type
	// ����������� ��� ������������ ������ ���� ����� 10
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
	
	return ERROR;
}



mistakes cParser::parser_M(const char *const data)
{
	// we assume that more than 100 lines can`t be
	for (size_t i = 0; i < 100; i++){
		// ���� ����� �� ����� ������, �� �������� ��� �� \n � ������� ������� ��� ��� ��������
		if (data[i] == '\r' && 	data[i + 1] == '\n'){
				check_sum();	// �������� ������� �������� ���������� ����� ��� ���-�� ���� ����
				this->M.array[i]	 = '\r'; 
				this->M.array[i + 1] = '\n'; 
				return M_PACK_ACCEPTED;
		}
		this->M.array[i] = data[i];
	}
	memset(&M, 0, sizeof(M));
	return ERROR;
}