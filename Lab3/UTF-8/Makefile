SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
APP_NAME = main

COMP = gcc
CFLAGS = -Wall -g3 -O0 -o

ENCODE = encode
DECODE = decode

BIN_FILE = units.bin
TXT_FILE = points.txt
RES_FILE = result.txt

create:
	$(COMP) $(SRC_FILES) $(CFLAGS) $(APP_NAME)

enrun:
	./$(APP_NAME) $(ENCODE) $(TXT_FILE) $(BIN_FILE)

derun:
	./$(APP_NAME) $(DECODE) $(BIN_FILE) $(RES_FILE)
