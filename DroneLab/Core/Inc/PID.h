/*
 * PID.h
 *
 *  Created on: 30 Apr 2023
 *      Author: Mateusz Matejko
 */

#ifndef INC_PID_H_
#define INC_PID_H_

typedef struct
{
	float P;
	float I;
	float D;
} PID_Set;

PID_Set PID_Roll =
{
		.P = 1,
		.I = 0.1,
		.D = 0.01
};

PID_Set PID_Pitch =
{
		.P = 1,
		.I = 0.1,
		.D = 0.01
};

PID_Set PID_Yaw =
{
		.P = 1,
		.I = 0.1,
		.D = 0
};



#endif /* INC_PID_H_ */
