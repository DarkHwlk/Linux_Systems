#include <stdio.h>
#include <stdlib.h>

char buff[100];  //Uninitialized data segment
int number_buff[]={1, 2, 3, 4};  //Initialized data segment

void hello(int x){  //Cap phat stack frame cho ham hello()
	int result;  //Stack frame cua ham hello()
}

void main(){  //Cap phat stack frame cho ham main()
	static int key = 1;  //Initialized data segment
	static char buf[10];  //Uninitialized data segment
	char* p;  // Stack frame cua ham main()
	p = malloc(10);  //Tro toi bo nho duoc cap phat o Heap segment
}
