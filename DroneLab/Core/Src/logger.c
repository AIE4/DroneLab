#include "logger.h"

//#include "fatfs.h"
//#include "fatfs_sd.h"
#include "string.h"
#include "LogType.h"
#include "Data.h"

/*FATFS fs;
FIL fil;
FRESULT fresult;

UINT br, bw;

FATFS *pfs;
DWORD fre_clust;
uint32_t total, freespace;*/

char result[150];

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
	LOGGER_PrepareString(data, logType);
	CDC_Transmit_FS(result, strlen(result));
	//free(result);
}

void LOGGER_WriteData()
{
	//char data_[100];
	LOGGER_PrepareData();
	//LOGGER_PrepareString(data_, _DATA);
	CDC_Transmit_FS(result, strlen(result));
	//free(data_);
}

void LOGGER_CloseFile()
{
	/*fresult = f_close(&fil);*/
}

void LOGGER_PrepareString(char* data, enum LogType logType)
{
	//result = malloc(150);

	memset(result, 0, 150);

	if(result == NULL)
	{
		return NULL;
	}

	strcpy(result, "[LOG]");

	switch(logType)
	{
	case _DEBUG:
		strcat(result, "(DEBUG)");
		break;
	case _INFO:
		strcat(result, "(INFO)");
		break;
	case _ERROR:
		strcat(result, "(ERROR)");
		break;
	case _WARNING:
		strcat(result, "(WARNING)");
		break;
	case _DATA:
			strcat(result, "(DATA)");
			break;
	default:
		strcat(result, "(\?\?\?\?)");
	}

	strcat(result, data);
	strcat(result, "\n\r");

	//char* result = strdup(startString);
	//free(startString);

	//return result;
}

void LOGGER_PrepareData()
{
	memset(result, 0, 150);

	sprintf(result, "[LOG](DATA)%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %hu %hu %hu %hu\n\r", DATA_GyroRadiansPerSecond.X, DATA_GyroRadiansPerSecond.Y, DATA_GyroRadiansPerSecond.Z, DATA_GForce.X, DATA_GForce.Y, DATA_GForce.Z, DATA_GyroAnglesInWorldFrame.X, DATA_GyroAnglesInWorldFrame.Y, DATA_GyroAnglesInWorldFrame.Z, DATA_ComplementedAngles.X, DATA_ComplementedAngles.Y, DATA_ComplementedAngles.Z, DATA_MotorValues.motor0, DATA_MotorValues.motor1, DATA_MotorValues.motor2, DATA_MotorValues.motor3);
}
