SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
APP_NAME = main

COMP = gcc
CFLAGS = -Wall -O0 -g3 -o

create:
	$(COMP) $(SRC_FILES) $(CFLAGS) $(APP_NAME)

run: 
	./$(APP_NAME) 