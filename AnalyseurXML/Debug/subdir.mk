################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp \
../xmlElement.cpp \
../xmlNode.cpp \
../xmlText.cpp 

C_SRCS += \
../lex.yy.c \
../xml.tab.c 

OBJS += \
./lex.yy.o \
./main.o \
./xml.tab.o \
./xmlElement.o \
./xmlNode.o \
./xmlText.o 

C_DEPS += \
./lex.yy.d \
./xml.tab.d 

CPP_DEPS += \
./main.d \
./xmlElement.d \
./xmlNode.d \
./xmlText.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


