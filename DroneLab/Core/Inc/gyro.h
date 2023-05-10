#pragma once

#define USE_GYRO

#include "XYZ_Data.h"

void GYRO_Init();

void GYRO_GetValues(XYZ_Data *values);
