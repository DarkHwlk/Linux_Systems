#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

/* Khai bao signal handle */
void sig_handler1(int num){  // num la signal number
	printf("\nIm signal SIGINT: %d\n", num);
	exit(EXIT_SUCCESS);  //Ket thuc tien trinh
}

void sig_handler2(int num){
	printf("\nIm signal SIGTERM: %d\n", num);
}

void sig_handler3(int num){
	
	if(num == SIGUSR1){
		printf("\nIm signal SIGUSR1: %d\n", num);
	}else if(num == SIGUSR2){
		printf("\nIm signal SIGUSR2: %d\n", num);
		exit(EXIT_SUCCESS);  //Ket thuc tien trinh
	}

}

int main(){
	if(signal(SIGINT, sig_handler1) == SIG_ERR){
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGTERM, sig_handler2) == SIG_ERR){
		fprintf(stderr, "Cannot handle SIGTERM\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGUSR1, sig_handler3) == SIG_ERR){
		fprintf(stderr, "Cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGUSR2, sig_handler3) == SIG_ERR){
		fprintf(stderr, "Cannot handle SIGUSR2\n");
		exit(EXIT_FAILURE);
	}

	printf("process ID: %d\n", getpid());
	while(1){
		/* Do nothing */
		printf(".....\n");
		sleep(2); 
	}

	return 0;
}
