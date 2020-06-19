################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../client.o \
../server.o 

C_SRCS += \
../Client.c \
../NitinClient.c \
../NitinServer.c \
../Server.c 

OBJS += \
./Client.o \
./NitinClient.o \
./NitinServer.o \
./Server.o 

C_DEPS += \
./Client.d \
./NitinClient.d \
./NitinServer.d \
./Server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


