################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/JEMonDebug/JEMonDebug.cpp 

OBJS += \
./src/JEMonDebug/JEMonDebug.o 

CPP_DEPS += \
./src/JEMonDebug/JEMonDebug.d 


# Each subdirectory must supply rules for building sources it contributes
src/JEMonDebug/%.o: ../src/JEMonDebug/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/storage/apps/eclipse-avr/workspace/ArduinoCore-1.0/src" -I/usr/share/arduino-1.0/libraries/Ethernet -I/usr/share/arduino-1.0/libraries/SPI -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega2560 -DF_CPU=1600000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


