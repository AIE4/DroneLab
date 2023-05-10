#pragma once

#include "LogType.h"

void LOGGER_Init();
void LOGGER_OpenFile();
void LOGGER_WriteLine(char* data, enum LogType logType);
void LOGGER_CloseFile();
char* LOGGER_PrepareString(char* data, enum LogType logType);
void LOGGER_WriteData(char* data);
