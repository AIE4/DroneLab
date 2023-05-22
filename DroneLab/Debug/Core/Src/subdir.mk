################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Configuration.c \
../Core/Src/PID_Controllers.c \
../Core/Src/Utilities.c \
../Core/Src/accel.c \
../Core/Src/dma.c \
../Core/Src/dshot.c \
../Core/Src/gpio.c \
../Core/Src/gyro.c \
../Core/Src/logger.c \
../Core/Src/main.c \
../Core/Src/motion_sensors.c \
../Core/Src/motor_mixer.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stm32f4xx_nucleo_bus.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/Configuration.o \
./Core/Src/PID_Controllers.o \
./Core/Src/Utilities.o \
./Core/Src/accel.o \
./Core/Src/dma.o \
./Core/Src/dshot.o \
./Core/Src/gpio.o \
./Core/Src/gyro.o \
./Core/Src/logger.o \
./Core/Src/main.o \
./Core/Src/motion_sensors.o \
./Core/Src/motor_mixer.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stm32f4xx_nucleo_bus.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/Configuration.d \
./Core/Src/PID_Controllers.d \
./Core/Src/Utilities.d \
./Core/Src/accel.d \
./Core/Src/dma.d \
./Core/Src/dshot.d \
./Core/Src/gpio.d \
./Core/Src/gyro.d \
./Core/Src/logger.d \
./Core/Src/main.d \
./Core/Src/motion_sensors.d \
./Core/Src/motor_mixer.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stm32f4xx_nucleo_bus.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dsl -I../Drivers/BSP/Components/lsm303agr -I../Drivers/BSP/Components/hts221 -I../Drivers/BSP/Components/lps22hb -I../Drivers/BSP/IKS01A2 -I../Drivers/BSP/Components/Common -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Configuration.d ./Core/Src/Configuration.o ./Core/Src/Configuration.su ./Core/Src/PID_Controllers.d ./Core/Src/PID_Controllers.o ./Core/Src/PID_Controllers.su ./Core/Src/Utilities.d ./Core/Src/Utilities.o ./Core/Src/Utilities.su ./Core/Src/accel.d ./Core/Src/accel.o ./Core/Src/accel.su ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/dshot.d ./Core/Src/dshot.o ./Core/Src/dshot.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/gyro.d ./Core/Src/gyro.o ./Core/Src/gyro.su ./Core/Src/logger.d ./Core/Src/logger.o ./Core/Src/logger.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motion_sensors.d ./Core/Src/motion_sensors.o ./Core/Src/motion_sensors.su ./Core/Src/motor_mixer.d ./Core/Src/motor_mixer.o ./Core/Src/motor_mixer.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stm32f4xx_nucleo_bus.d ./Core/Src/stm32f4xx_nucleo_bus.o ./Core/Src/stm32f4xx_nucleo_bus.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

