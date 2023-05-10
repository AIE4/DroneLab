#include "accel.h"

#include "iks01a2_motion_sensors.h"
#include "iks01a2_motion_sensors_ex.h"
//#include "XYZ_Data.h"

void ACCEL_Init()
{
	IKS01A2_MOTION_SENSOR_SetOutputDataRate(IKS01A2_LSM6DSL_0, MOTION_ACCELERO, 208);
	IKS01A2_MOTION_SENSOR_SetFullScale(IKS01A2_LSM6DSL_0, MOTION_ACCELERO, 16);
}

void ACCEL_GetValues(XYZ_Data *values)
{
	IKS01A2_MOTION_SENSOR_Axes_t data;
	IKS01A2_MOTION_SENSOR_GetAxes(IKS01A2_LSM6DSL_0, MOTION_ACCELERO, &data);

	values->X = (float)data.x/1000.f;
	values->Y = (float)data.y/1000.f;
	values->Z = (float)data.z/1000.f;
}
