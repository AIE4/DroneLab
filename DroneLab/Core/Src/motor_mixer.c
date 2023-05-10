/*
 * motor_mixer.c
 *
 *  Created on: 9 May 2023
 *      Author: Mateusz Matejko
 */

#include "motor_mixer.h"
#include "dshot.h"
#include "PID_Controllers.h"

uint16_t motorsValues[4] = {1000, 1000, 1000, 1000}; // motor values are from 1000 to 2000 us, set 1000 as initial value
uint16_t throttle = 1000;
uint16_t roll = 0;
uint16_t pitch = 0;
uint16_t yaw = 0;

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
	throttle = 0;
	roll = PID_CONTROLLERS_Roll(setpoints[1], time);
	pitch = PID_CONTROLLERS_Pitch(setpoints[2], time);
	yaw = PID_CONTROLLERS_Yaw(setpoints[3], time);
}

void MOTOR_MIXER_InitDSHOT()
{
	dshot_init(DSHOT600);
}

void MOTOR_MIXER_Mix()
{
	motorsValues[0] = throttle - roll + pitch + yaw;
	motorsValues[1] = throttle - roll - pitch - yaw;
	motorsValues[2] = throttle + roll + pitch - yaw;
	motorsValues[3] = throttle + roll - pitch + yaw;
}

void MOTOR_MIXER_WriteMotors()
{
	dshot_write(motorsValues);
}
