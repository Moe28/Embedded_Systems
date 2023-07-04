#@copyright: Boufa

CC=arm-none-eabi
CFLAGS=-gdwarf-2 -mcpu=cortex-m4 -g
INCS=-I
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)	
As= $(wildcard *.s)		
AsOBJ= $(As:.s=.o)	
Project_name= unit3_Lab4_cortexM4
all: $(Project_name).bin

	@echo "===============Build is Done============" 
	


%.o:	%.c
	$(CC)-gcc.exe $(CFLAGS) -c $(INCS) . $< -o $@

	
	
$(Project_name).elf: 	$(OBJ) $(AsOBJ)
		$(CC)-ld.exe -T linker_script.ld $(OBJ) -o $(Project_name).elf -Map=Map_File.map
		cp $(Project_name).elf $(Project_name).axf 
		
		
		
$(Project_name).bin: 	$(Project_name).elf 
		$(CC)-objcopy.exe -O binary $(Project_name).elf $@

	
clean_all:
	rm *.o *.elf *.bin
	
clean:
	rm *.elf *.bin	