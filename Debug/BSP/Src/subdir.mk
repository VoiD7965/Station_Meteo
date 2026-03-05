################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Src/DEV_Config.c \
../BSP/Src/GUI_Paint.c 

OBJS += \
./BSP/Src/DEV_Config.o \
./BSP/Src/GUI_Paint.o 

C_DEPS += \
./BSP/Src/DEV_Config.d \
./BSP/Src/GUI_Paint.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Src/%.o BSP/Src/%.su BSP/Src/%.cyclo: ../BSP/Src/%.c BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Utilities/Inc -I../BSP/Inc -I../App/Inc -I../Services/Inc -I../Drivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Src

clean-BSP-2f-Src:
	-$(RM) ./BSP/Src/DEV_Config.cyclo ./BSP/Src/DEV_Config.d ./BSP/Src/DEV_Config.o ./BSP/Src/DEV_Config.su ./BSP/Src/GUI_Paint.cyclo ./BSP/Src/GUI_Paint.d ./BSP/Src/GUI_Paint.o ./BSP/Src/GUI_Paint.su

.PHONY: clean-BSP-2f-Src

