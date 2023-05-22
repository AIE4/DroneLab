/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "dshot.h"
#include "logger.h"
#include "LogType.h"
#include "motion_sensors.h"
#include "XYZ_Data.h"
#include "Data.h"
#include "motor_mixer.h"
#include "time.h"
#include "Configuration.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t my_motor_value[4] = {0, 0, 0, 0};

uint8_t buffer[64];

uint32_t time = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  //dshot_init(DSHOT600);
  MOTOR_MIXER_InitDSHOT();

  float setpoints[4] = {0, 0, 0, 0};

  int i = 0;

	//XYZ_Data gyro;
	//XYZ_Data accel;

	//char gyroString[70];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
  {
	  CONFIGURATION_Start(buffer);
  }

	for(i = 0; i < 15; ++i)
		  {
			  LOGGER_WriteLine("Starting", _INFO);
			  HAL_Delay(400);
		  }

    initSensors();

    for(i = 0; i < 2000; ++i)
	  {
    	MOTOR_MIXER_WriteMotors();
    		HAL_Delay(1);
	  }

    time = systick_micros;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(buffer[17] <= 15)
	  {
		  setpoints[1] = buffer[17];
	  }
	  else
	  {
		  setpoints[1] = -(buffer[17] - 15);
	  }

	  if(buffer[18] <= 15)
	  {
		  setpoints[2] = buffer[18];
	  }
	  else
	  {
		  setpoints[2] = -(buffer[18] - 15);
	  }
	//dshot_write(my_motor_value);
	MOTOR_MIXER_WriteMotors();
	HAL_Delay(1);

	//uint8_t a = buffer[0];

	MOTION_SENSORS_UpdateData();
	MOTOR_MIXER_RunPID(setpoints, systick_micros - time);
	time = systick_micros;

	//sprintf(gyroString, "%.2f %.2f %.2f\n\r", DATA_ComplementedAngles.X, DATA_ComplementedAngles.Y, DATA_ComplementedAngles.Z);
	//sprintf(gyroString, "Gyro: %.2f %.2f %.2f Accel: %.2f %.2f %.2f Angle: %.2f %.2f %.2f AngleC: %.2f %.2f %.2f %hu %hu %hu %hu\n\r", DATA_RadiansPerSecond.X, DATA_RadiansPerSecond.Y, DATA_RadiansPerSecond.Z, DATA_GForce.X, DATA_GForce.Y, DATA_GForce.Z, DATA_AccelAngles.X, DATA_AccelAngles.Y, DATA_AccelAngles.Z,  DATA_ComplementedAngles.X, DATA_ComplementedAngles.Y, DATA_ComplementedAngles.Z, DATA_MotorValues.motor0, DATA_MotorValues.motor1, DATA_MotorValues.motor2, DATA_MotorValues.motor3);
	//CDC_Transmit_FS((uint8_t*)gyroString, strlen(gyroString));
	LOGGER_WriteData();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
