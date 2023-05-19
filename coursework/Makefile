SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
APP_NAME = kmpmatcher
GDB = gdbtest

COMP = gcc
CFLAGS = -Wall -o
GDBFLAGS = -Wall -g3 -O0 -o

create:
	$(COMP) $(SRC_FILES) $(CFLAGS) $(APP_NAME)

gdb:
	$(COMP) $(SRC_FILES) $(GDBFLAGS) $(GDB)