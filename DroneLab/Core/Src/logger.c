#include "logger.h"

//#include "fatfs.h"
//#include "fatfs_sd.h"
#include "string.h"
#include "LogType.h"

/*FATFS fs;
FIL fil;
FRESULT fresult;

UINT br, bw;

FATFS *pfs;
DWORD fre_clust;
uint32_t total, freespace;*/

void LOGGER_Init()
{
	//fresult = f_mount(&fs, "", 0);

	//f_getfree("", &fre_clust, &pfs);

}

void LOGGER_OpenFile()
{
	/*fresult = f_open(&fil, "log.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	f_lseek(&fil, fil.fptr);*/
}

void LOGGER_WriteLine(char* data, enum LogType logType)
{
	//fresult = f_puts(data, &fil);
	char* result = LOGGER_PrepareString(data, logType);
	CDC_Transmit_FS(result, strlen(result));
}

void LOGGER_WriteData(char* data)
{
	char* result = LOGGER_PrepareString(data, _DATA);
	CDC_Transmit_FS(result, strlen(result));
}

void LOGGER_CloseFile()
{
	/*fresult = f_close(&fil);*/
}

char* LOGGER_PrepareString(char* data, enum LogType logType)
{
	char* startString = malloc(150);

	if(startString == NULL)
	{
		return NULL;
	}

	strcpy(startString, "[LOG]");

	switch(logType)
	{
	case _DEBUG:
		strcat(startString, "(DEBUG)");
		break;
	case _INFO:
		strcat(startString, "(INFO)");
		break;
	case _ERROR:
		strcat(startString, "(ERROR)");
		break;
	case _WARNING:
		strcat(startString, "(WARNING)");
		break;
	case _DATA:
			strcat(startString, "(DATA)");
			break;
	default:
		strcat(startString, "(\?\?\?\?)");
	}

	strcat(startString, data);
	strcat(startString, "\n\r");

	return startString;
}
