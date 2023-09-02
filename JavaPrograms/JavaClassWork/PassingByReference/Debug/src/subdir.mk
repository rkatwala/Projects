################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PassingByReference\ copy.cpp \
../src/PassingByReference.cpp 

OBJS += \
./src/PassingByReference\ copy.o \
./src/PassingByReference.o 

CPP_DEPS += \
./src/PassingByReference\ copy.d \
./src/PassingByReference.d 


# Each subdirectory must supply rules for building sources it contributes
src/PassingByReference\ copy.o: ../src/PassingByReference\ copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/PassingByReference copy.d" -MT"src/PassingByReference\ copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


