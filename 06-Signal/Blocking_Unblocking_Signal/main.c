#define _POSIX_SOURCE  //Macro de co the su dung duoc ham signal cua Unix system
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

/* Khai bao signal handle */
void sig_handler1(int num){  // num la signal number
	printf("\nIm signal handler1: %d\n", num);
	exit(EXIT_SUCCESS);  //Ket thuc tien trinh
}

int main(){
	sigset_t new_set, old_set;

	if(signal(SIGINT, sig_handler1) == SIG_ERR){
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	sigemptyset(&new_set);
	sigemptyset(&old_set);
	
	/* Set user mask */
	printf("new_set is %x\n",new_set);
	sigaddset(&new_set, SIGINT);

	if(sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0){
		if(sigismember(&new_set, SIGINT) == 1){
			printf("SIGINT exist\n");
			sigdelset(&new_set, SIGINT);
			sigprocmask(SIG_SETMASK, &new_set, &old_set);
		       	printf("SIGINT is removed from mask\n");
		} else if(sigismember(&new_set, SIGINT) == 0){
			printf("SIGINT does not exist\n");
			sigaddset(&new_set, SIGINT);
			sigprocmask(SIG_SETMASK, &new_set, &old_set); 
			printf("SIGINT is added in mask\n");
		}
	}

	while(1);

	return 0;
}
