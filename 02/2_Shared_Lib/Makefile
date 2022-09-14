
shared:
	gcc -shared obj/hello_Hung.o obj/hello_world.o -o lib/shared/libhello.so

link:
	gcc obj/main.o -Llib/shared -lhello -o bin/exam

all: 
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c -fPIC src/hello_Hung.c -o obj/hello_Hung.o -I./inc
	gcc -c -fPIC src/hello_world.c -o obj/hello_world.o -I./inc

clean:
	rm -rf obj/* bin/*

