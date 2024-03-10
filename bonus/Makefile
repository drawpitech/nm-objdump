##
## EPITECH PROJECT, 2024
## nm/objdump
## File description:
## Makefile
##

BUILD_DIR := .build

CC := gcc
AS := nasm
LD := ld

SO_NAME := libso.so
SO_SRC := $(shell find ./so -name '*.c')
SO_OBJ := $(SO_SRC:%.c=$(BUILD_DIR)/so/%.o)

DY_NAME := libdy.so
DY_SRC := $(shell find ./dy -name '*.s')
DY_OBJ := $(DY_SRC:%.s=$(BUILD_DIR)/dy/%.o)

.DEFAULT_GOAL := all
.PHONY: all
.NOTPARALLEL: all
all: $(SO_NAME) $(DY_NAME)

# ↓ libso.so
$(BUILD_DIR)/so/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -fPIC -c -o $@ $<

$(SO_NAME): $(SO_OBJ)
	$(CC) -shared -o $@ $^

# ↓ libdy.so
$(BUILD_DIR)/dy/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) -f elf64 -shared -o $@ $<

$(DY_NAME): $(DY_OBJ)
	$(LD) -shared -o $@ $^

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(SO_NAME) $(DY_NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all