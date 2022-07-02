################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/init.c 

C_DEPS += \
./src/init.d 

OBJS += \
./src/init.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: RTEMS C Compiler'
	/home/duk3/gsoc2022/rtems/6/bin/arm-rtems6-gcc -I/home/duk3/gsoc2022/rtems/6/arm-rtems6/stm32f4/lib/include -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=auto -Os -g -Wall -c -fmessage-length=0 -pipe -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/init.d ./src/init.o

.PHONY: clean-src

