#include "motion_sensors.h"
#include "stm32f4xx_it.h"
#include "gyro.h"
#include "accel.h"
#include "logger.h"
#include "Data.h"
#include "XYZ_Data.h"
#include "Time.h"
#include <stdlib.h>
#include "Config.h"

#include "iks01a2_motion_sensors.h"
#include "iks01a2_motion_sensors_ex.h"

uint32_t updateTime;

XYZ_Data DATA_GyroRadiansPerSecond;
XYZ_Data DATA_GyroRadiansPerSecondInWorldFrame;
XYZ_Data DATA_GyroAnglesInWorldFrame;
XYZ_Data DATA_GForce;
XYZ_Data DATA_AccelAngles;

XYZ_Data DATA_ComplementedAngles;
XYZ_Data DATA_ComplementedAnglesInDegrees;

XYZ_Data DATA_GyroRadiansPerSecond_Offset;
XYZ_Data DATA_Angles_Offset;
XYZ_Data DATA_GForce_Offset;
XYZ_Data DATA_ComplementedAngles_Offset;

float ** RotationalMatrix;


int initSensors()
{
#if defined(USE_GYRO) && defined(USE_ACCEL)

	if(IKS01A2_MOTION_SENSOR_Init(IKS01A2_LSM6DSL_0, MOTION_GYRO | MOTION_ACCELERO) == HAL_OK)
	{
		GYRO_Init();
		ACCEL_Init();
		LOGGER_WriteLine("Gyro and Accel initiated", _INFO);
	}
	else
	{
		LOGGER_WriteLine("Gyro and Accel initialization failed", _ERROR);
		return -1;
	}

#elif defined(USE_GYRO)

	LOGGER_WriteLine("Couldn't find accel file", _ERROR);
	if(IKS01A2_MOTION_SENSOR_Init(IKS01A2_LSM6DSL_0, MOTION_GYRO == HAL_OK))
	{
		LOGGER_WriteLine("Gyro initiated", _INFO);
	}
	else
	{
		LOGGER_WriteLine("Gyro and Accel initialization failed", _ERROR);
		return -1;
	}

#elif defined(USE_ACCEL)

	LOGGER_WriteLine("Couldn't find gyro file", _ERROR);
	if(IKS01A2_MOTION_SENSOR_Init(IKS01A2_LSM6DSL_0, MOTION_ACCELERO == HAL_OK))
	{
		LOGGER_WriteLine("Accel initiated", _INFO);
		return 0;
	}
	else
	{
		LOGGER_WriteLine("Accel initialization failed", _ERROR);
		return -1;
	}

#else
	LOGGER_WriteLine("Couldn't find gyro and accel file", _ERROR);

#endif

	uint8_t i = 0;

	//Set start time to current micros
	updateTime = systick_micros;


	//Initialize gyro readings data
	DATA_GyroRadiansPerSecond_Offset.X = 0;
	DATA_GyroRadiansPerSecond_Offset.Y = 0;
	DATA_GyroRadiansPerSecond_Offset.Z = 0;

	//Initialize Euler angles
	DATA_GyroAnglesInWorldFrame.X = 0; //phi
	DATA_GyroAnglesInWorldFrame.Y = 0; //theta
	DATA_GyroAnglesInWorldFrame.Z = 0; //psi

	//Initialize complemented angles values
	DATA_ComplementedAngles.X = 0;
	DATA_ComplementedAngles.Y = 0;
	DATA_ComplementedAngles.Z = 0;

	DATA_ComplementedAnglesInDegrees.X = 0;
	DATA_ComplementedAnglesInDegrees.Y = 0;
	DATA_ComplementedAnglesInDegrees.Z = 0;

	DATA_GForce.X = 0;
	DATA_GForce.Y = 0;
	DATA_GForce.Y = 0;

	//Run data reading few times, to get read of first noisy data
	for(i = 0; i < 15; i ++)
	{
		MOTION_SENSORS_UpdateData();
		HAL_Delay(40);
	}

	//Set start gyro values as offsets
	DATA_GyroRadiansPerSecond_Offset.X = DATA_GyroRadiansPerSecond.X;
	DATA_GyroRadiansPerSecond_Offset.Y = DATA_GyroRadiansPerSecond.Y;
	DATA_GyroRadiansPerSecond_Offset.Z = DATA_GyroRadiansPerSecond.Z;

	DATA_GForce_Offset.X = DATA_GForce.X;
	DATA_GForce_Offset.Y = DATA_GForce.Y;
	DATA_GForce_Offset.Z = DATA_GForce.Z;

	return 0;
}

/*
Description:
Gets gyro data and sets it's values to the given pointer
*/
void MOTION_SENSORS_GetGyro(XYZ_Data *values)
{
	GYRO_GetValues(values);
}

/*
Description:
Gets accel data and sets it's values to the given pointer
*/
void MOTION_SENSORS_GetAccel(XYZ_Data *values)
{
	ACCEL_GetValues(values);
}

/*
Description:
Updates data values stored in Data.h (DATA_RadiansPerSecond, DATA_GyroRadiansPerSecondInWorldFrame, DATA_GForce, DATA_AccelAngles, DATA_ComplementedAngles)
*/
void MOTION_SENSORS_UpdateData()
{
	MOTION_SENSORS_GetGyro(&DATA_GyroRadiansPerSecond);
	ConvertGyroDataToWorldFrame();
	MOTION_SENSORS_GetAccel(&DATA_GForce);
	MOTION_SENSORS_CalculateAccelAngles();
	MOTION_SENSORS_Integrate(systick_micros - updateTime);
	ApplyComplementaryFilter(systick_micros - updateTime);
	updateTime = systick_micros;
	ConvertComplemetedAnglesToDegrees();
}

/*
Description:
Integrates gyro to data to create angles from gyro readings
*/
void MOTION_SENSORS_Integrate(uint32_t time)
{
	DATA_GyroAnglesInWorldFrame.X += DATA_GyroRadiansPerSecondInWorldFrame.X * time * 0.001;
	DATA_GyroAnglesInWorldFrame.Y += DATA_GyroRadiansPerSecondInWorldFrame.Y * time * 0.001;
	DATA_GyroAnglesInWorldFrame.Z += DATA_GyroRadiansPerSecondInWorldFrame.Z * time * 0.001;
}

/*
Description:
Calculates and sets angles from accelerometer readings (only X and Y)
*/
void MOTION_SENSORS_CalculateAccelAngles()
{
	DATA_AccelAngles.X = atanf(DATA_GForce.Y / DATA_GForce.Z);
	DATA_AccelAngles.Y = atanf(DATA_GForce.X / DATA_GForce.Z);
}

/*
Description:
Creates rotational Matrix for given euler angles

Params:
Euler angles theta and phi

Returns:
pointer to 2D matrix containing rotational matrix
*/
float ** GetRotationalMatrix(float theta, float phi)
{
	/*
	[1, tan(theta) * sin(phi), tan(theta) * cos(phi)]

	[0,        cos(phi),             -sin(phi)      ]

	[0,  sin(phi)/cos(theta),   cos(phi)/cos(theta) ]
	*/

	RotationalMatrix = (float**)malloc(3 * sizeof(float*));

	for (int i = 0; i < 3; i++) {
		RotationalMatrix[i] = (float*)malloc(3 * sizeof(float));
	}

	RotationalMatrix[0][0] = 1;
	RotationalMatrix[0][1] = tan(theta) * sin(phi);
	RotationalMatrix[0][2] = tan(theta) * cos(phi);
	RotationalMatrix[1][0] = 0;
	RotationalMatrix[1][1] = cos(phi);
	RotationalMatrix[1][2] = -sin(phi);
	RotationalMatrix[2][0] = 0;
	RotationalMatrix[2][1] = sin(phi)/cos(theta);
	RotationalMatrix[2][2] = cos(phi)/cos(theta);

	return RotationalMatrix;
}

/*
Description:
Converts gyro readings to world fraem using rotatinal matrix and updates the values
*/
void ConvertGyroDataToWorldFrame()
{
	float ** rotationalMatrix = GetRotationalMatrix(DATA_GyroAnglesInWorldFrame.Y, DATA_GyroAnglesInWorldFrame.X);

	DATA_GyroRadiansPerSecondInWorldFrame.X = rotationalMatrix[0][0] * DATA_GyroRadiansPerSecond.X + rotationalMatrix[0][1] * DATA_GyroRadiansPerSecond.Y + rotationalMatrix[0][2] * DATA_GyroRadiansPerSecond.Z;
	DATA_GyroRadiansPerSecondInWorldFrame.Y = rotationalMatrix[1][0] * DATA_GyroRadiansPerSecond.X + rotationalMatrix[1][1] * DATA_GyroRadiansPerSecond.Y + rotationalMatrix[1][2] * DATA_GyroRadiansPerSecond.Z;
	DATA_GyroRadiansPerSecondInWorldFrame.Z = rotationalMatrix[2][0] * DATA_GyroRadiansPerSecond.X + rotationalMatrix[2][1] * DATA_GyroRadiansPerSecond.Y + rotationalMatrix[2][2] * DATA_GyroRadiansPerSecond.Z;

	free(RotationalMatrix[0]);
	free(RotationalMatrix[1]);
	free(RotationalMatrix[2]);
	free(RotationalMatrix);
	free(rotationalMatrix);
}

/*
Description:
Creates angles using complementary filter from gyro and accel radings and updates the values
*/
void ApplyComplementaryFilter(uint32_t time)
{
	DATA_ComplementedAngles.X = CONFIG_COMPLEMENTARY_FILTER_GyroPart * 0.01 * (DATA_ComplementedAngles.X + time * 0.001 * DATA_GyroRadiansPerSecondInWorldFrame.X) + CONFIG_COMPLEMENTARY_FILTER_AccelPart * 0.01 * DATA_AccelAngles.X;
	DATA_ComplementedAngles.Y = CONFIG_COMPLEMENTARY_FILTER_GyroPart * 0.01 * (DATA_ComplementedAngles.Y + time * 0.001 * DATA_GyroRadiansPerSecondInWorldFrame.Y) + CONFIG_COMPLEMENTARY_FILTER_AccelPart * 0.01 * -DATA_AccelAngles.Y;
	DATA_ComplementedAngles.Z = DATA_GyroAnglesInWorldFrame.Z;
}

/*
Description:
Converts complemented angles from radians to degrees and updates the values
*/
void ConvertComplemetedAnglesToDegrees()
{
	DATA_ComplementedAnglesInDegrees.X = DATA_ComplementedAngles.X * 180/3.14159;
	DATA_ComplementedAnglesInDegrees.Y = DATA_ComplementedAngles.Y * 180/3.14159;
	DATA_ComplementedAnglesInDegrees.Z = DATA_ComplementedAngles.Z * 180/3.14159;
}

void MOTION_SENSORS_Calibrate()
{
	//Initialize gyro readings data
	DATA_GyroRadiansPerSecond_Offset.X = 0;
	DATA_GyroRadiansPerSecond_Offset.Y = 0;
	DATA_GyroRadiansPerSecond_Offset.Z = 0;

	//Set start gyro values as offsets
	DATA_GyroRadiansPerSecond_Offset.X = DATA_GyroRadiansPerSecond.X;
	DATA_GyroRadiansPerSecond_Offset.Y = DATA_GyroRadiansPerSecond.Y;
	DATA_GyroRadiansPerSecond_Offset.Z = DATA_GyroRadiansPerSecond.Z;

	//Initialize Euler angles
	DATA_GyroAnglesInWorldFrame.X = 0; //phi
	DATA_GyroAnglesInWorldFrame.Y = 0; //theta
	DATA_GyroAnglesInWorldFrame.Z = 0; //psi

	//Initialize complemented angles values
	DATA_ComplementedAngles.X = 0;
	DATA_ComplementedAngles.Y = 0;
	DATA_ComplementedAngles.Z = 0;

	DATA_ComplementedAnglesInDegrees.X = 0;
	DATA_ComplementedAnglesInDegrees.Y = 0;
	DATA_ComplementedAnglesInDegrees.Z = 0;
}
