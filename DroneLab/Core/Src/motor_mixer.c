/*
 * motor_mixer.c
 *
 *  Created on: 9 May 2023
 *      Author: Mateusz Matejko
 */

#include "motor_mixer.h"
#include "dshot.h"
#include "PID_Controllers.h"
#include "Data.h"

uint16_t motorsValues[4] = {0, 0, 0, 0}; // motor values are from 1000 to 2000 us, set 1000 as initial value
int throttle = 1100;
int roll = 0;
int pitch = 0;
int yaw = 0;

Motors DATA_MotorValues;

/*
 motors numbers

 	  ^
      |

 (4)    (2)
   \    /
    \  /
     \/
     /\
    /  \
   /    \
 (3)    (1)

 motorValue[0] - motor1
 motorValue[1] - motor2
 motorValue[2] - motor3
 motorValue[3] - motor4

 control values are + for:
 roll - rigth
 pitch - forward
 yaw - CW

 propellers on the drone spin outside
*/

void MOTOR_MIXER_RunPID(float *setpoints, int time)
{
	throttle = 1100;
	roll = PID_CONTROLLERS_Roll(setpoints[1], time);
	pitch = PID_CONTROLLERS_Pitch(setpoints[2], time);
	yaw = PID_CONTROLLERS_Yaw(setpoints[3], time);
	MOTOR_MIXER_Mix();
}

void MOTOR_MIXER_InitDSHOT()
{
	dshot_init(DSHOT150);
	motorsValues[0] = 0;
	motorsValues[1] = 0;
	motorsValues[2] = 0;
	motorsValues[3] = 0;
	dshot_write(motorsValues);
}

void MOTOR_MIXER_Mix()
{
	int i = 0;
	motorsValues[0] = throttle - roll + pitch;// + yaw;
	motorsValues[1] = throttle - roll - pitch;// - yaw;
	motorsValues[2] = throttle + roll + pitch;// - yaw;
	motorsValues[3] = throttle + roll - pitch;// + yaw;

	for(i = 0; i < 4; i++)
	{
		if(motorsValues[i] < 1000)
		{
			motorsValues[i] = 1000;
		}
	}

	DATA_MotorValues.motor0 = motorsValues[0];
	DATA_MotorValues.motor1 = motorsValues[1];
	DATA_MotorValues.motor2 = motorsValues[2];
	DATA_MotorValues.motor3 = motorsValues[3];
}

void MOTOR_MIXER_WriteMotors()
{
	dshot_write(motorsValues);
}
