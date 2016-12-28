FLAGS = -lpthread -O0
CC = gcc
BUILD = obj

main: Makefile main.o smoker.o agent.o
	$(CC) $(BUILD)/main.o $(BUILD)/smoker.o $(BUILD)/agent.o -o cigs $(FLAGS)

main.o:	Makefile main.c main.h
	mkdir $(BUILD) -p && $(CC) -c main.c -o $(BUILD)/main.o $(FLAGS) 

smoker.o: Makefile smoker.c main.h
	$(CC) -c smoker.c -o $(BUILD)/smoker.o $(FLAGS) 

agent.o: Makefile agent.c main.h
	$(CC) -c  agent.c -o $(BUILD)/agent.o $(FLAGS)

