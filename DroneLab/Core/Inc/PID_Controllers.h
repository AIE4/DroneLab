/*
 * PID_Controllers.h
 *
 *  Created on: 30 Apr 2023
 *      Author: Mateusz Matejko
 */
#ifndef INC_PID_CONTROLLERS_H_
#define INC_PID_CONTROLLERS_H_

#include "stdint.h"

int PID_CONTROLLERS_Roll(float setpoint, int time);
int PID_CONTROLLERS_Pitch(float setpoint, int time);
int PID_CONTROLLERS_Yaw(float setpoint, int time);



#endif /* INC_PID_CONTROLLERS_H_ */
