##
## EPITECH PROJECT, 2024
## nm/objdump
## File description:
## Makefile
##

# ↓ Binaries
NM_NAME := my_nm
OB_NAME := my_objdump

NM_TARGET = $(NM_NAME)
OB_TARGET = $(OB_NAME)
ifneq ($(TARGET),)
	NM_TARGET = $(TARGET)
	OB_TARGET = $(TARGET)
endif
ifeq ($(MAKECMDGOALS), asan)
	NM_TARGET = asan
	OB_TARGET = asan
endif

NM_BIN = src/nm/$(NM_TARGET)
OB_BIN = src/objdump/$(OB_TARGET)


.DEFAULT_GOAL := all
.PHONY: all
.NOTPARALLEL: all
all: $(NM_NAME) $(OB_NAME)

# ↓ nm
.PHONY: $(NM_BIN)
$(NM_BIN):
	@ $(MAKE) -s -C $(dir $@) $(MAKEFLAGS) $(notdir $@)

$(NM_NAME): $(NM_BIN)
	@ cp $< $@

# ↓ objdump
.PHONY: $(OB_BIN)
$(OB_BIN):
	@ $(MAKE) -s -C $(dir $@) $(MAKEFLAGS) $(notdir $@)

$(OB_NAME): $(OB_BIN)
	@ cp $< $@

# ↓ asan
.PHONY: asan
asan: all

# ↓ Cleaning
.PHONY: clean
clean:
	@ $(MAKE) -s -C $(dir $(NM_BIN)) $(MAKEFLAGS) clean
	@ $(MAKE) -s -C $(dir $(OB_BIN)) $(MAKEFLAGS) clean

.PHONY: fclean
fclean:
	@ $(MAKE) -s -C $(dir $(NM_BIN)) $(MAKEFLAGS) fclean
	@ $(MAKE) -s -C $(dir $(OB_BIN)) $(MAKEFLAGS) fclean
	@ $(RM) $(NM_NAME) $(OB_NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all
