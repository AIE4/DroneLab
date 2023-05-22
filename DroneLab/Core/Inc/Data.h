/*
 * Data.h
 *
 *  Created on: 1 May 2023
 *      Author: Mateusz Matejko
 */

#ifndef INC_DATA_H_
#define INC_DATA_H_

#include "XYZ_Data.h"

typedef struct
{
	uint16_t motor0;
	uint16_t motor1;
	uint16_t motor2;
	uint16_t motor3;
} Motors;

extern XYZ_Data DATA_GyroRadiansPerSecond;
extern XYZ_Data DATA_GyroRadiansPerSecondInWorldFrame;
extern XYZ_Data DATA_GyroAnglesInWorldFrame;
extern XYZ_Data DATA_GForce;
extern XYZ_Data DATA_AccelAngles;

extern XYZ_Data DATA_ComplementedAngles;
extern XYZ_Data DATA_ComplementedAngles_Offset;
extern XYZ_Data DATA_ComplementedAnglesInDegrees;

extern XYZ_Data DATA_GyroRadiansPerSecond_Offset;
extern XYZ_Data DATA_Angles_Offset;
extern XYZ_Data DATA_GForce_Offset;

extern Motors DATA_MotorValues;



#endif /* INC_DATA_H_ */
