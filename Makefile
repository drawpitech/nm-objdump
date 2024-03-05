##
## EPITECH PROJECT, 2024
## nm/objdump
## File description:
## Makefile
##

# ↓ Binaries
NM_NAME := my_nm
OB_NAME := my_objdump

NM_DIR := src/nm
NM_TARGET := my_nm
OB_DIR := src/objdump
OB_TARGET := my_objdump

.DEFAULT_GOAL := all
.PHONY: all
.NOTPARALLEL: all
all: nm objdump

# ↓ nm
.PHONY: $(NM_NAME)
$(NM_NAME):
	@ $(MAKE) -s -C $(NM_DIR) $(MAKEFLAGS) $(NM_TARGET)
	@ cp $(NM_DIR)/$(NM_TARGET) $@

.PHONY: nm
nm: $(NM_NAME)
	@ cp $^ $@

# ↓ objdump
.PHONY: $(OB_NAME)
$(OB_NAME): OB_TARGET ?= $@
$(OB_NAME):
	@ $(MAKE) -s -C $(OB_DIR) $(MAKEFLAGS) $(OB_TARGET)
	@ cp $(OB_DIR)/$(OB_TARGET) $@

.PHONY: objdump
objdump: $(OB_NAME)
	@ cp $^ $@

# ↓ Custom binaries
.PHONY: asan
asan: NM_TARGET := asan
asan: OB_TARGET := asan
asan: all

.PHONY: prof
prof: NM_TARGET := prof
prof: OB_TARGET := prof
prof: prof

# ↓ Cleaning
.PHONY: clean
clean:
	@ $(MAKE) -s -C $(NM_DIR) $(MAKEFLAGS) clean
	@ $(MAKE) -s -C $(OB_DIR) $(MAKEFLAGS) clean

.PHONY: fclean
fclean:
	@ $(MAKE) -s -C $(NM_DIR) $(MAKEFLAGS) fclean
	@ $(MAKE) -s -C $(OB_DIR) $(MAKEFLAGS) fclean
	@ $(RM) $(NM_NAME) $(OB_NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all
