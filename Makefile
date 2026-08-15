PROJECT=main
CPU ?= cortex-m4
BOARD ?= stm32vldiscovery

BUILD_DIR = build
TARGET = $(BUILD_DIR)/$(PROJECT)

ALL_SRCS = $(shell find . -path "*/examples" -prune -o \( -iname "*.c"  -o -iname "*.cpp" -o -iname "*.s" \) | sed 's|^\./||')
SRCS = $(filter-out %/arduino.cpp %/arduino_runtime_glue.cpp %/generated_debug.cpp,$(ALL_SRCS))

OBJ_FILES = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(patsubst %.s,$(BUILD_DIR)/%.o,$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))))
			
INCLUDE1 = $(shell find . \( -iname "*.h" -o -iname "*.hpp" \) -exec dirname {} \; | sed 's/^./-I./g' | xargs )
INCLUDE_DIRS = $(sort $(dir $(shell find . -name "*.h" -o -name "*.hpp")))
INCLUDE = $(foreach dir,$(INCLUDE_DIRS),-I"$(dir)")

.PHONY : all
all : $(TARGET).elf $(BUILD_DIR)/$(PROJECT).bin
$(BUILD_DIR)/%.o : %.s
	@mkdir -p $(dir $@)
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c $^ -o $@

$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	arm-none-eabi-gcc $(INCLUDE) -mthumb -mcpu=$(CPU) -g3 -c "$<" -o "$@"

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p "$(dir $@)"
	arm-none-eabi-g++ $(INCLUDE) -mthumb -mcpu=$(CPU) -g3 -c "$<" -o "$@"

$(TARGET).elf : $(OBJ_FILES)
	arm-none-eabi-g++ -Tmap.ld -mthumb -mcpu=cortex-m4 --specs=nano.specs $^ -o $@
	arm-none-eabi-objdump -D -S $@ > $@.lst
	arm-none-eabi-readelf -a $@ > $@.debug

$(BUILD_DIR)/$(PROJECT).bin : $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@

qemu:
	qemu-system-arm -S -M $(BOARD) -cpu $(CPU) -nographic -kernel $(TARGET).elf -gdb tcp::1234

gdb-qemu:
	gdb-multiarch -q $(TARGET).elf -ex "target remote localhost:1234"

gdb:
	gdb-multiarch -q $(TARGET).elf -ex "target remote localhost:4242"

clean:
	rm -rf *.out *.elf .gdb_history *.lst *.debug $(OBJ_FILES) $(BUILD_DIR)

info :
	@echo "---SRC FILES ---"
	@echo "$(SRCS)" | sed 's/ /\n/g' | xargs -n 1
	@echo "---OBJ_FILES ---"
	@echo "$(OBJ_FILES)" | sed 's/ /\n/g' | xargs -n 1

symbols:
	arm-none-eabi-nm --size-sort --special-syms $(TARGET).elf