/*
 * PID_Controllers.c
 *
 *  Created on: 30 Apr 2023
 *      Author: Mateusz Matejko
 */

#include "PID_Controllers.h"
#include "Data.h"
#include "PID.h"
#include "logger.h"
#include "Config.h"

float Roll_ITerm;
float Pitch_ITerm;
float Yaw_ITerm;

float Roll_Error;
float Pitch_Error;
float Yaw_Error;

//setpoint is desired angle in radians - level mode
//time in millisecond elapsed since last PID calcullation
uint16_t PID_CONTROLLERS_Roll(float setpoint, int time)
{
	float output;
	float error = setpoint - DATA_ComplementedAngles.X;
	Roll_ITerm += PID_Roll.I * error * time * 0.001; // discrete integration, convert time to seconds

	if(Roll_ITerm > CONFIG_MaximumITerm) // to avoid integral windup set check for maximum ITerm
	{
		Roll_ITerm = CONFIG_MaximumITerm;
		LOGGER_WriteLine("Roll ITerm exceeded maximum value, set to 400", _INFO);
	}
	output = error * PID_Roll.P + Roll_ITerm + PID_Roll.D * ((error - Roll_Error))/(time * 0.001);

	return output;
}

uint16_t PID_CONTROLLERS_Pitch(float setpoint,  int time)
{
	float output;
	float error = setpoint - DATA_ComplementedAngles.X;
	Pitch_ITerm += PID_Pitch.I * error * time * 0.001; // discrete integration, convert time to seconds

	if(Pitch_ITerm > CONFIG_MaximumITerm) // to avoid integral windup set check for maximum ITerm
	{
		Roll_ITerm = CONFIG_MaximumITerm;
		LOGGER_WriteLine("Roll ITerm exceeded maximum value, set to 400", _INFO);
	}
	output = error * PID_Pitch.P + Pitch_ITerm + PID_Pitch.D * ((error - Pitch_Error))/(time * 0.001);

	return output;
}

uint16_t PID_CONTROLLERS_Yaw(float setpoint, int time)
{
	float output;
	float error = setpoint - DATA_ComplementedAngles.X;
	Yaw_ITerm += PID_Yaw.I * error * time * 0.001; // discrete integration, convert time to seconds

	if(Yaw_ITerm > CONFIG_MaximumITerm) // to avoid integral windup set check for maximum ITerm
	{
		Yaw_ITerm = CONFIG_MaximumITerm;
		LOGGER_WriteLine("Roll ITerm exceeded maximum value, set to 400", _INFO);
	}
	output = error * PID_Yaw.P + Yaw_ITerm + PID_Yaw.D * ((error - Yaw_Error))/(time * 0.001); // in yaw D term will be probably 0, but this part is kept here, existence of D term is defined in PID values configuration

	return output;
}
