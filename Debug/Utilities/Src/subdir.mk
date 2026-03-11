################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Src/ImageData.c \
../Utilities/Src/font12.c \
../Utilities/Src/font12CN.c \
../Utilities/Src/font16.c \
../Utilities/Src/font20.c \
../Utilities/Src/font24.c \
../Utilities/Src/font24CN.c \
../Utilities/Src/font72.c \
../Utilities/Src/font8.c \
../Utilities/Src/system.c 

OBJS += \
./Utilities/Src/ImageData.o \
./Utilities/Src/font12.o \
./Utilities/Src/font12CN.o \
./Utilities/Src/font16.o \
./Utilities/Src/font20.o \
./Utilities/Src/font24.o \
./Utilities/Src/font24CN.o \
./Utilities/Src/font72.o \
./Utilities/Src/font8.o \
./Utilities/Src/system.o 

C_DEPS += \
./Utilities/Src/ImageData.d \
./Utilities/Src/font12.d \
./Utilities/Src/font12CN.d \
./Utilities/Src/font16.d \
./Utilities/Src/font20.d \
./Utilities/Src/font24.d \
./Utilities/Src/font24CN.d \
./Utilities/Src/font72.d \
./Utilities/Src/font8.d \
./Utilities/Src/system.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Src/%.o Utilities/Src/%.su Utilities/Src/%.cyclo: ../Utilities/Src/%.c Utilities/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Utilities/Inc -I../BSP/Inc -I../Services/Inc -I../App/Inc -I../Drivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -includestdint.h -includeStation_meteo.h -includestdbool.h -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Src

clean-Utilities-2f-Src:
	-$(RM) ./Utilities/Src/ImageData.cyclo ./Utilities/Src/ImageData.d ./Utilities/Src/ImageData.o ./Utilities/Src/ImageData.su ./Utilities/Src/font12.cyclo ./Utilities/Src/font12.d ./Utilities/Src/font12.o ./Utilities/Src/font12.su ./Utilities/Src/font12CN.cyclo ./Utilities/Src/font12CN.d ./Utilities/Src/font12CN.o ./Utilities/Src/font12CN.su ./Utilities/Src/font16.cyclo ./Utilities/Src/font16.d ./Utilities/Src/font16.o ./Utilities/Src/font16.su ./Utilities/Src/font20.cyclo ./Utilities/Src/font20.d ./Utilities/Src/font20.o ./Utilities/Src/font20.su ./Utilities/Src/font24.cyclo ./Utilities/Src/font24.d ./Utilities/Src/font24.o ./Utilities/Src/font24.su ./Utilities/Src/font24CN.cyclo ./Utilities/Src/font24CN.d ./Utilities/Src/font24CN.o ./Utilities/Src/font24CN.su ./Utilities/Src/font72.cyclo ./Utilities/Src/font72.d ./Utilities/Src/font72.o ./Utilities/Src/font72.su ./Utilities/Src/font8.cyclo ./Utilities/Src/font8.d ./Utilities/Src/font8.o ./Utilities/Src/font8.su ./Utilities/Src/system.cyclo ./Utilities/Src/system.d ./Utilities/Src/system.o ./Utilities/Src/system.su

.PHONY: clean-Utilities-2f-Src

