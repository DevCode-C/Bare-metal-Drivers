CC = arm-none-eabi
MACH = cortex-m0
TARGET = temp
VPATH = Sources 
INCLUDES = -I Headers
CFLAGS = -g3 -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu99 -Wall -O0 $(INCLUDES)
LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs --specs=nano.specs -T stm32_ls.ld -Wl,-Map=$(OUTPUT_F)/$(TARGET).map
OBJS_F = OutPutFile/ObjFiles
OUTPUT_F = OutPutFile
OBJS = main.o stm32_startup.o gpio.o nvic.o uart.o

all:$(OUTPUT_F)/$(TARGET).elf

$(OUTPUT_F)/$(TARGET).elf: $(addprefix $(OBJS_F)/, $(OBJS))
	$(CC)-gcc $(LDFLAGS) -o $@ $^		

$(addprefix $(OBJS_F)/,%.o) : %.c
	@mkdir -p $(OBJS_F)
	$(CC)-gcc -MD $(CFLAGS) -o $@ $<

-include $(OBJS_F)/*.d

misra_test:
	@cppcheck --addon=misra.json --inline-suppr --std=c99 --template=gcc --force Sources/  -I Headers/ 

clean:
	@rm -rf $(OBJS_F)

flash : all
	@openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program $(OUTPUT_F)/$(TARGET).elf verify reset exit" 

open: 
	@openocd -f interface/stlink.cfg -f target/stm32f0x.cfg

debug: clean | all 
	@$(CC)-gdb $(OUTPUT_F)/$(TARGET).elf -q -iex "set auto-load safe-path /"
