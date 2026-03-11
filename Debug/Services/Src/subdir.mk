################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Services/Src/EPD_4in26_test.c \
../Services/Src/Srv_battery.c \
../Services/Src/Srv_screen.c \
../Services/Src/Srv_sensors.c \
../Services/Src/Srv_time.c 

OBJS += \
./Services/Src/EPD_4in26_test.o \
./Services/Src/Srv_battery.o \
./Services/Src/Srv_screen.o \
./Services/Src/Srv_sensors.o \
./Services/Src/Srv_time.o 

C_DEPS += \
./Services/Src/EPD_4in26_test.d \
./Services/Src/Srv_battery.d \
./Services/Src/Srv_screen.d \
./Services/Src/Srv_sensors.d \
./Services/Src/Srv_time.d 


# Each subdirectory must supply rules for building sources it contributes
Services/Src/%.o Services/Src/%.su Services/Src/%.cyclo: ../Services/Src/%.c Services/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../System/Inc -I../BSP/Inc -I../Services/Inc -I../App/Inc -I../Drivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -includestdint.h -includeStation_meteo.h -includestdbool.h -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Services-2f-Src

clean-Services-2f-Src:
	-$(RM) ./Services/Src/EPD_4in26_test.cyclo ./Services/Src/EPD_4in26_test.d ./Services/Src/EPD_4in26_test.o ./Services/Src/EPD_4in26_test.su ./Services/Src/Srv_battery.cyclo ./Services/Src/Srv_battery.d ./Services/Src/Srv_battery.o ./Services/Src/Srv_battery.su ./Services/Src/Srv_screen.cyclo ./Services/Src/Srv_screen.d ./Services/Src/Srv_screen.o ./Services/Src/Srv_screen.su ./Services/Src/Srv_sensors.cyclo ./Services/Src/Srv_sensors.d ./Services/Src/Srv_sensors.o ./Services/Src/Srv_sensors.su ./Services/Src/Srv_time.cyclo ./Services/Src/Srv_time.d ./Services/Src/Srv_time.o ./Services/Src/Srv_time.su

.PHONY: clean-Services-2f-Src

