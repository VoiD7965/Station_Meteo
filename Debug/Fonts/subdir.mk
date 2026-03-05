################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Fonts/font12.c \
../Fonts/font12CN.c \
../Fonts/font16.c \
../Fonts/font20.c \
../Fonts/font24.c \
../Fonts/font24CN.c \
../Fonts/font8.c 

OBJS += \
./Fonts/font12.o \
./Fonts/font12CN.o \
./Fonts/font16.o \
./Fonts/font20.o \
./Fonts/font24.o \
./Fonts/font24CN.o \
./Fonts/font8.o 

C_DEPS += \
./Fonts/font12.d \
./Fonts/font12CN.d \
./Fonts/font16.d \
./Fonts/font20.d \
./Fonts/font24.d \
./Fonts/font24CN.d \
./Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Fonts/%.o Fonts/%.su Fonts/%.cyclo: ../Fonts/%.c Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../BSP/Inc -I../App/Inc -I../Service/Inc -I../Drivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Fonts

clean-Fonts:
	-$(RM) ./Fonts/font12.cyclo ./Fonts/font12.d ./Fonts/font12.o ./Fonts/font12.su ./Fonts/font12CN.cyclo ./Fonts/font12CN.d ./Fonts/font12CN.o ./Fonts/font12CN.su ./Fonts/font16.cyclo ./Fonts/font16.d ./Fonts/font16.o ./Fonts/font16.su ./Fonts/font20.cyclo ./Fonts/font20.d ./Fonts/font20.o ./Fonts/font20.su ./Fonts/font24.cyclo ./Fonts/font24.d ./Fonts/font24.o ./Fonts/font24.su ./Fonts/font24CN.cyclo ./Fonts/font24CN.d ./Fonts/font24CN.o ./Fonts/font24CN.su ./Fonts/font8.cyclo ./Fonts/font8.d ./Fonts/font8.o ./Fonts/font8.su

.PHONY: clean-Fonts

