APP_PATH = ~/Programing2023/Lab2/src

all: vector

vector: $(APP_PATH)/main.o $(APP_PATH)/IntVector.o
	gcc $(APP_PATH)/main.o $(APP_PATH)/IntVector.o -o vector

main.o: $(APP_PATH)/main.c
	gcc -Wall -c main.c -MMD

IntVector.o: $(APP_PATH)/IntVector.c
	gcc -Wall -c IntVector.c -MMD

clean: 
	rm -rf $(APP_PATH)/*.o vector

-include main.d IntVector.d

.PHONY: all clean