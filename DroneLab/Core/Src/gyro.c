#include "gyro.h"

#include "iks01a2_motion_sensors.h"
#include "iks01a2_motion_sensors_ex.h"

#include "Data.h"

void GYRO_Init()
{
	IKS01A2_MOTION_SENSOR_SetOutputDataRate(IKS01A2_LSM6DSL_0, MOTION_GYRO, 1000);
	IKS01A2_MOTION_SENSOR_SetFullScale(IKS01A2_LSM6DSL_0, MOTION_GYRO, 2000);
}

void GYRO_GetValues(XYZ_Data *values)
{
	IKS01A2_MOTION_SENSOR_Axes_t data;
	IKS01A2_MOTION_SENSOR_GetAxes(IKS01A2_LSM6DSL_0, MOTION_GYRO, &data);

	//XYZ_Data result;

	//float x = ((float)data.x * 0.001 * 3.14159/180);

	//radians per second
	values->X = ((float)data.x * 0.001 * 3.14159/180) - DATA_GyroRadiansPerSecond_Offset.X;
	values->Y = ((float)data.y * 0.001 * 3.14159/180) - DATA_GyroRadiansPerSecond_Offset.Y;
	values->Z = ((float)data.z * 0.001 * 3.14159/180) - DATA_GyroRadiansPerSecond_Offset.Z;

	//degrees per second
	/*values->X = ((float)data.x * 0.001) - DATA_GyroDegreesPerSecond_Offset.X;
	values->Y = ((float)data.y * 0.001) - DATA_GyroDegreesPerSecond_Offset.Y;
	values->Z = ((float)data.z * 0.001) - DATA_GyroDegreesPerSecond_Offset.Z;*/
	//values->X -= DATA_RadiansPerSecond_Offset.X;

	//return result;
}
