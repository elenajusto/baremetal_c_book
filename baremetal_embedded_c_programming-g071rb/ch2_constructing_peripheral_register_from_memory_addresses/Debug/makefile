################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ch2_constructing_peripheral_register_from_memory_addresses
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ch2_constructing_peripheral_register_from_memory_addresses.elf \

MAP_FILES += \
ch2_constructing_peripheral_register_from_memory_addresses.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ch2_constructing_peripheral_register_from_memory_addresses.list \


# All Target
all: main-build

# Main-build Target
main-build: ch2_constructing_peripheral_register_from_memory_addresses.elf secondary-outputs

# Tool invocations
ch2_constructing_peripheral_register_from_memory_addresses.elf ch2_constructing_peripheral_register_from_memory_addresses.map: $(OBJS) $(USER_OBJS) C:\Users\elena\STM32CubeIDE\baremetal_c_book\baremetal_embedded_c_programming-g071rb\ch2_constructing_peripheral_register_from_memory_addresses\STM32G071RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ch2_constructing_peripheral_register_from_memory_addresses.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\elena\STM32CubeIDE\baremetal_c_book\baremetal_embedded_c_programming-g071rb\ch2_constructing_peripheral_register_from_memory_addresses\STM32G071RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ch2_constructing_peripheral_register_from_memory_addresses.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ch2_constructing_peripheral_register_from_memory_addresses.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ch2_constructing_peripheral_register_from_memory_addresses.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ch2_constructing_peripheral_register_from_memory_addresses.elf ch2_constructing_peripheral_register_from_memory_addresses.list ch2_constructing_peripheral_register_from_memory_addresses.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
