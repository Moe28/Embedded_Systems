#@copyright: Boufa

CC=arm-none-eabi
CFLAGS=-gdwarf-2 -mcpu=cortex-m3
INCS=-I
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)	
As= $(wildcard *.s)		
AsOBJ= $(As:.s=.o)	
Project_name= Learn_Cortex_m3
all: $(Project_name).bin

	@echo "===============Build is Done============" 
	


%.o:	%.c
	$(CC)-gcc.exe $(CFLAGS) -c $(INCS) . $< -o $@

$(Project_name).elf: 	$(OBJ) $(AsOBJ)
		$(CC)-ld.exe -T linker_script.ld $(OBJ) -o $(Project_name).elf -Map=Map_File.map

$(Project_name).bin: 	$(Project_name).elf 
		$(CC)-objcopy.exe -O binary $(Project_name).elf $@

	
clean_all:
	rm *.o *.elf *.bin
	
clean:
	rm *.elf *.bin	