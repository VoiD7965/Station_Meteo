################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Src/ImageData.c \
../System/Src/font12.c \
../System/Src/font12CN.c \
../System/Src/font16.c \
../System/Src/font20.c \
../System/Src/font24.c \
../System/Src/font24CN.c \
../System/Src/font72.c \
../System/Src/font8.c \
../System/Src/system.c 

OBJS += \
./System/Src/ImageData.o \
./System/Src/font12.o \
./System/Src/font12CN.o \
./System/Src/font16.o \
./System/Src/font20.o \
./System/Src/font24.o \
./System/Src/font24CN.o \
./System/Src/font72.o \
./System/Src/font8.o \
./System/Src/system.o 

C_DEPS += \
./System/Src/ImageData.d \
./System/Src/font12.d \
./System/Src/font12CN.d \
./System/Src/font16.d \
./System/Src/font20.d \
./System/Src/font24.d \
./System/Src/font24CN.d \
./System/Src/font72.d \
./System/Src/font8.d \
./System/Src/system.d 


# Each subdirectory must supply rules for building sources it contributes
System/Src/%.o System/Src/%.su System/Src/%.cyclo: ../System/Src/%.c System/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../System/Inc -I../BSP/Inc -I../Services/Inc -I../App/Inc -I../Drivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -includestdint.h -includeStation_meteo.h -includestdbool.h -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System-2f-Src

clean-System-2f-Src:
	-$(RM) ./System/Src/ImageData.cyclo ./System/Src/ImageData.d ./System/Src/ImageData.o ./System/Src/ImageData.su ./System/Src/font12.cyclo ./System/Src/font12.d ./System/Src/font12.o ./System/Src/font12.su ./System/Src/font12CN.cyclo ./System/Src/font12CN.d ./System/Src/font12CN.o ./System/Src/font12CN.su ./System/Src/font16.cyclo ./System/Src/font16.d ./System/Src/font16.o ./System/Src/font16.su ./System/Src/font20.cyclo ./System/Src/font20.d ./System/Src/font20.o ./System/Src/font20.su ./System/Src/font24.cyclo ./System/Src/font24.d ./System/Src/font24.o ./System/Src/font24.su ./System/Src/font24CN.cyclo ./System/Src/font24CN.d ./System/Src/font24CN.o ./System/Src/font24CN.su ./System/Src/font72.cyclo ./System/Src/font72.d ./System/Src/font72.o ./System/Src/font72.su ./System/Src/font8.cyclo ./System/Src/font8.d ./System/Src/font8.o ./System/Src/font8.su ./System/Src/system.cyclo ./System/Src/system.d ./System/Src/system.o ./System/Src/system.su

.PHONY: clean-System-2f-Src

