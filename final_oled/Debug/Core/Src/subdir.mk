################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/button.c \
../Core/Src/dac.c \
../Core/Src/default_data.c \
../Core/Src/default_data1.c \
../Core/Src/default_data3.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/oled.c \
../Core/Src/speaker.c \
../Core/Src/spi.c \
../Core/Src/ssd1306_tests.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_state.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/utils.c 

OBJS += \
./Core/Src/button.o \
./Core/Src/dac.o \
./Core/Src/default_data.o \
./Core/Src/default_data1.o \
./Core/Src/default_data3.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/oled.o \
./Core/Src/speaker.o \
./Core/Src/spi.o \
./Core/Src/ssd1306_tests.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_state.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/utils.o 

C_DEPS += \
./Core/Src/button.d \
./Core/Src/dac.d \
./Core/Src/default_data.d \
./Core/Src/default_data1.d \
./Core/Src/default_data3.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/oled.d \
./Core/Src/speaker.d \
./Core/Src/spi.d \
./Core/Src/ssd1306_tests.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_state.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R5xx -c -I../Core/Inc -I"/Users/chrislann/STM32CubeIDE/workspace_1.19.0/final_oled/Drivers/OLED" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/dac.cyclo ./Core/Src/dac.d ./Core/Src/dac.o ./Core/Src/dac.su ./Core/Src/default_data.cyclo ./Core/Src/default_data.d ./Core/Src/default_data.o ./Core/Src/default_data.su ./Core/Src/default_data1.cyclo ./Core/Src/default_data1.d ./Core/Src/default_data1.o ./Core/Src/default_data1.su ./Core/Src/default_data3.cyclo ./Core/Src/default_data3.d ./Core/Src/default_data3.o ./Core/Src/default_data3.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/oled.cyclo ./Core/Src/oled.d ./Core/Src/oled.o ./Core/Src/oled.su ./Core/Src/speaker.cyclo ./Core/Src/speaker.d ./Core/Src/speaker.o ./Core/Src/speaker.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/ssd1306_tests.cyclo ./Core/Src/ssd1306_tests.d ./Core/Src/ssd1306_tests.o ./Core/Src/ssd1306_tests.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_state.cyclo ./Core/Src/system_state.d ./Core/Src/system_state.o ./Core/Src/system_state.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/utils.cyclo ./Core/Src/utils.d ./Core/Src/utils.o ./Core/Src/utils.su

.PHONY: clean-Core-2f-Src

