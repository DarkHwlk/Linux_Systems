#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	pid_t child_pid;  //Bien chua pid 
	int counter = 2;  

	printf("Gia tri khoi tao cua counter: %d\n", counter);

	/* Tao tien trinh con */
	child_pid = fork();
	if(child_pid >=0){
		if(0 == child_pid){  //Process con
			counter++;
			printf("I am the child process, counter: %d\n", counter);
			printf("My PID is: %d, my parrent's PID is: %d\n", getpid(),getppid());
		      	//sleep(1);	
		}else{  //Process cha
			printf("Child's PID is: %d\n", child_pid);
			printf("I am the parrent process, counter: %d\n", counter);
			printf("My PID is: %d\n", getpid());
		       	while(1);
		}
	}else{  /* Tien trinh con khong duoc tao thanh cong */
		printf("fork() unsuccessfully\n");
	}

	return 0;
}
