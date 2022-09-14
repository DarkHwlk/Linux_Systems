.PHONY: all clean

CC := gcc

all:
	$(CC) -o producer producer.c
	$(CC) -o consumer consumer.c

clean: 
	rm -rf producer consumer myfifo
