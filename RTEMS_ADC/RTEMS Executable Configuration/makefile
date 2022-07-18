################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := RTEMS_ADC
BUILD_ARTIFACT_EXTENSION := exe
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: RTEMS_ADC.exe

# Tool invocations
RTEMS_ADC.exe: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: RTEMS Linker'
	/home/duk3/gsoc2022/rtems/6/bin/arm-rtems6-gcc -fdata-sections -ffunction-sections -I/home/duk3/gsoc2022/rtems/6/arm-rtems6/stm32f4/lib/include -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=auto -B/home/duk3/gsoc2022/rtems/6/arm-rtems6/stm32f4/lib -qrtems -Wl,--gc-sections -o "RTEMS_ADC.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) RTEMS_ADC.exe
	-@echo ' '

post-build:
	-@echo 'Generate bin file'
	-/home/duk3/gsoc2022/rtems/6/bin/arm-rtems6-objcopy -O binary RTEMS_ADC.exe RTEMS_ADC.bin
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
