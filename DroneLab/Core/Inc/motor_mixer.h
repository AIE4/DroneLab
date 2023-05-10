/*
 * MotorMixer.h
 *
 *  Created on: 9 May 2023
 *      Author: Mateusz Matejko
 */

#ifndef INC_MOTOR_MIXER_H_
#define INC_MOTOR_MIXER_H_

void MOTOR_MIXER_RunPID(float *setpoints, int time);
void MOTOR_MIXER_InitDSHOT();
void MOTOR_MIXER_Mix();
void MOTOR_MIXER_WriteMotors();



#endif /* INC_MOTOR_MIXER_H_ */
