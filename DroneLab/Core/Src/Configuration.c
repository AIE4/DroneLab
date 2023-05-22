/*
 * Configuration.c
 *
 *  Created on: 19 May 2023
 *      Author: Mateusz Matejko
 */


#include "Configuration.h"
#include "dshot.h"

uint16_t motors[4] = {0, 0, 0, 0};

void CONFIGURATION_Start(uint8_t* buffer)
{
	while(1)
	{
		uint32_t motor0 = buffer[0] * 1000 + buffer[1] * 100 + buffer[2] * 10 + buffer[3];
		uint32_t motor1 = buffer[4] * 1000 + buffer[5] * 100 + buffer[6] * 10 + buffer[7];
		uint32_t motor2 = buffer[8] * 1000 + buffer[9] * 100 + buffer[10] * 10 + buffer[11];
		uint32_t motor3 = buffer[12] * 1000 + buffer[13] * 100 + buffer[14] * 10 + buffer[15];

		motors[0] = motor0;
		motors[1] = motor1;
		motors[2] = motor2;
		motors[3] = motor3;

		dshot_write(motors);
	}
}
