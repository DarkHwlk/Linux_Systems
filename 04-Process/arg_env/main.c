#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
	int i = 0;

	/* In ra so luong command-line truyen vao */
	printf("Number of argument: %d\n", argc);

	/* In ra noi dung cua command-line */
	for(i = 0; i < argc; i++){
		printf("argv[%d]: %s\n", i, argv[i]);
	}
}
