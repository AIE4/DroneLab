
#ifndef MOTION_SENSORS_H
#define MOTION_SENSORS_H

#include "stdint.h"

int initSensors(void);
void MOTION_SENSORS_GetGyro();
void MOTION_SENSORS_GetAccel();
void MOTION_SENSORS_UpdateData();
void MOTION_SENSORS_Integrate(uint32_t time);
void MOTION_SENSORS_CalculateAccelAngles();
void ConvertGyroDataToWorldFrame();
void ApplyComplementaryFilter(uint32_t time);

#endif // MOTION_SENSORS_H
