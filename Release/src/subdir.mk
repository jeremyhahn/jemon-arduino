################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/JEMonAPI.cpp \
../src/JEMonChannel.cpp \
../src/JEMonDebug.cpp \
../src/main.cpp 

OBJS += \
./src/JEMonAPI.o \
./src/JEMonChannel.o \
./src/JEMonDebug.o \
./src/main.o 

CPP_DEPS += \
./src/JEMonAPI.d \
./src/JEMonChannel.d \
./src/JEMonDebug.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


