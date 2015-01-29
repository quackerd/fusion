ASM = nasm
CC = gcc
LD = ld
C_SRC_PATH = x64/src/c
ASM_SRC_PATH = x64/src/asm
OUTPUT_DIR = temp
C_FLAGS = -m64 -c -fno-builtin -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -masm=intel -Wall -Wextra
ASM_FLAGS = -f elf64 -I $(ASM_SRC_PATH)/
LD_FLAGS = -melf_x86_64
LD_SCRIPT = build/link.ld
GRUB_CFG = build/grub.cfg

#C source code
C_FILES = $(wildcard $(C_SRC_PATH)/*.c)

#ASM source code
ASM_FILES = $(wildcard $(ASM_SRC_PATH)/*.asm)

#bin files
KERNEL_BIN = $(OUTPUT_DIR)/kernel.bin

#Object files
C_OBJ_FILES = $(addprefix $(OUTPUT_DIR)/,$(notdir $(C_FILES:.c=.oc)))
ASM_OBJ_FILES = $(addprefix $(OUTPUT_DIR)/,$(notdir $(ASM_FILES:.asm=.oasm)))
ALL_OBJ_FILES = $(C_OBJ_FILES) $(ASM_OBJ_FILES)


all : init compile link buildiso clean

init:
	sudo mkdir $(OUTPUT_DIR)

compile: $(C_OBJ_FILES) $(ASM_OBJ_FILES)

link: $(KERNEL_BIN)	

clean:
	sudo rm -rf $(OUTPUT_DIR)
buildiso:
	sudo mkdir $(OUTPUT_DIR)/temp_iso
	sudo mkdir $(OUTPUT_DIR)/temp_iso/HOS
	sudo mkdir $(OUTPUT_DIR)/temp_iso/boot
	sudo mkdir $(OUTPUT_DIR)/temp_iso/boot/grub
	sudo mv $(KERNEL_BIN) $(OUTPUT_DIR)/temp_iso/HOS/kernel.bin
	sudo cp $(GRUB_CFG) $(OUTPUT_DIR)/temp_iso/boot/grub/
	sudo grub-mkrescue -o HOS.iso $(OUTPUT_DIR)/temp_iso

$(OUTPUT_DIR)/%.oc : $(C_SRC_PATH)/%.c
	sudo $(CC) $(C_FLAGS) -o $@ $^

$(OUTPUT_DIR)/%.oasm : $(ASM_SRC_PATH)/%.asm
	sudo $(ASM) $(ASM_FLAGS) -o $@ $^

$(KERNEL_BIN): $(ALL_OBJ_FILES)
	sudo $(LD) $(LD_FLAGS) -T $(LD_SCRIPT) -o $(KERNEL_BIN) $(ALL_OBJ_FILES)
