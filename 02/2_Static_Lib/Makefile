
static:
	ar rcs lib/static/libhello.a obj/hello_Hung.o obj/hello_world.o

link:
	gcc obj/main.o -Llib/static -lhello -o bin/exam

all: 
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/hello_Hung.c -o obj/hello_Hung.o -I./inc
	gcc -c src/hello_world.c -o obj/hello_world.o -I./inc

clean:
	rm -rf obj/* bin/*

